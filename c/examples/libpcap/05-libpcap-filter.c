#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>


void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,const u_char*
        packet)
{
    static int count = 1;
    fprintf(stdout,"%d, ",count);
    fflush(stdout);
    count++;
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
    struct bpf_program fp;     
    bpf_u_int32 maskp;         
    bpf_u_int32 netp;          


    if(argc != 2){ fprintf(stdout,"Usage: %s \"filter program\"\n"
            ,argv[0]);return 0;}

   
    dev = pcap_lookupdev(errbuf);
	dev = "tap0";
    if(dev == NULL)
    { fprintf(stderr,"%s\n",errbuf); exit(1); }

   
    pcap_lookupnet(dev,&netp,&maskp,errbuf);

   
    descr = pcap_open_live(dev,BUFSIZ,1,-1,errbuf);
    if(descr == NULL)
    { printf("pcap_open_live(): %s\n",errbuf); exit(1); }

   
    if(pcap_compile(descr,&fp,argv[1],0,netp) == -1)
    { fprintf(stderr,"Error calling pcap_compile\n"); exit(1); }

   
    if(pcap_setfilter(descr,&fp) == -1)
    { fprintf(stderr,"Error setting filter\n"); exit(1); }

   
    pcap_loop(descr,-1,my_callback,NULL);

    return 0;
}