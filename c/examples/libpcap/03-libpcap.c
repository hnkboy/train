#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <time.h>

void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,const u_char*
        packet)
{
	struct ether_header *eptr; 
    static int count = 1;
    fprintf(stdout,"[%d]:  ",count);

    fflush(stdout);
    count++;
	
    printf("Grabbed packet of length %d\n",pkthdr->len);
    printf("Recieved at ..... %s",ctime((const time_t*)&(pkthdr->ts.tv_sec)));
    printf("Ethernet address length is %d\n",ETHER_HDR_LEN);	
	
	
	eptr = (struct ether_header *) packet;
	if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
	{
		printf("Ethernet type hex:%x dec:%d is an IP packet\n",
				ntohs(eptr->ether_type),
				ntohs(eptr->ether_type));
	}else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
	{
		printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
				ntohs(eptr->ether_type),
				ntohs(eptr->ether_type));
	}else {
		printf("Ethernet type %x not IP \n", ntohs(eptr->ether_type));
	}	
	
	fflush(stdout);
}

int main(int argc,char **argv)
{
    int i;
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr;
    const u_char *packet;
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