#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <time.h>
pcap_t* descr;

#define foreach_mac_address_offset              \
_(0)                                            \
_(1)                                            \
_(2)                                            \
_(3)                                            \
_(4)                                            \
_(5)

#define UDP_DST_PORT_VXLAN_GPE	4790
void my_callback(u_char *useless, const struct pcap_pkthdr* pkthdr,const u_char*
        packet)
{
	struct ether_header *eptr;
    static int count = 1;
    struct iphdr *ip_header;

	struct tcphdr *tcp_header=NULL;
	struct udphdr *udp_header=NULL;
    fprintf(stdout,"[%d]:  ",count);

    fflush(stdout);
    count++;

    printf("Grabbed packet of length %d\n",pkthdr->len);
    printf("Recieved at ..... %s",ctime((const time_t*)&(pkthdr->ts.tv_sec)));
    printf("Ethernet address length is %d\n",ETHER_HDR_LEN);


	eptr = (struct ether_header *) packet;
	if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
	{
		ip_header = (struct iphdr *)(packet + sizeof(struct ether_header));
		printf("Ethernet type hex:%x dec:%d is an IP packet\n",
				ntohs(eptr->ether_type),
				ntohs(eptr->ether_type));

		if(ip_header->protocol == IPPROTO_TCP)
		{
			tcp_header = (struct tcphdr *)((u_char *)ip_header + (u_int)(ip_header->ihl << 2));
		    printf("IP type hex:%x dec:%d is an TCP packet\n",
				    ip_header->protocol,
				    ip_header->protocol);
			if(NULL != tcp_header)
			{
				printf("TCP sport:%d, dport:%d\n",
				ntohs(tcp_header->source),
				ntohs(tcp_header->dest));
			}
		}
		else if (ip_header->protocol == IPPROTO_UDP)
		{
			udp_header = (struct udphdr *)((u_char *)ip_header + (u_int)(ip_header->ihl << 2));
		    printf("IP type hex:%x dec:%d is an UDP packet\n",
				    ip_header->protocol,
				    ip_header->protocol);
			if(NULL != udp_header)
			{
				printf("DDP sport:%d, dport:%d\n",
				ntohs(udp_header->source),
				ntohs(udp_header->dest));
			}
		}
	}else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
	{
		printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
				ntohs(eptr->ether_type),
				ntohs(eptr->ether_type));

	}else {
		printf("Ethernet type %x not IP \n", ntohs(eptr->ether_type));
	}



	if((NULL != udp_header) && (UDP_DST_PORT_VXLAN_GPE == ntohs(udp_header->dest)))
	{

/* 		if (NULL != ip_header)
		{
			u_int temp;
			ip_header = (struct iphdr *)(packet + sizeof(struct ether_header));
			temp = ip_header->saddr;
			ip_header->saddr = ip_header->daddr;
			ip_header->daddr = temp;
		} */
/* 		if(NULL != tcp_header)
		{
			u_short port_temp;
			port_temp = tcp_header->dest;
			tcp_header->dest = tcp_header->source;
			tcp_header->source = port_temp;
		} */
	    u_int ipv4_addr;
		u_short port_temp;
        u_char temp[ETHER_ADDR_LEN];

#define _(a) temp[a] = eptr->ether_dhost[a];
		foreach_mac_address_offset;
#undef _
#define _(a) eptr->ether_dhost[a] = eptr->ether_shost[a];
		foreach_mac_address_offset;
#undef _
#define _(a) eptr->ether_shost[a] = temp[a];
		foreach_mac_address_offset;
#undef _

		ip_header = (struct iphdr *)(packet + sizeof(struct ether_header));
		ipv4_addr = ip_header->saddr;
		ip_header->saddr = ip_header->daddr;
		ip_header->daddr = ipv4_addr;

		port_temp = udp_header->dest;
		udp_header->dest = udp_header->source;
		udp_header->source = port_temp;
		pcap_sendpacket(descr, packet , pkthdr->len);

	}
	fflush(stdout);
}

int main(int argc,char **argv)
{
    int i;
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];

    struct pcap_pkthdr hdr;
    struct ether_header *eptr;

    if(argc != 3){ fprintf(stdout,"Usage: %s interface numpackets\n",argv[0]);return 0;}


    dev = pcap_lookupdev(errbuf);
    if(dev == NULL)
    { printf("%s\n",errbuf); exit(1); }
    dev = argv[1];
    descr = pcap_open_live(dev,BUFSIZ,0,-1,errbuf);
    if(descr == NULL)
    { printf("pcap_open_live(): %s\n",errbuf); exit(1); }



    pcap_loop(descr,atoi(argv[2]),my_callback,NULL);

    fprintf(stdout,"\nDone processing packets... wheew!\n");
    return 0;
}