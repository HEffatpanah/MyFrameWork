#include <iostream>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <cmath>

#define ethernet_header_length 0
using namespace std;
void my_packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet){

    printf("recive packet\n");
    struct ether_header *eth_header;
    eth_header = (struct ether_header *) packet;
}

int main(int argc, char **argv) {
    pcap_t *handle;
    char error_buffer[PCAP_ERRBUF_SIZE];
    char *device = (char *) "enp1s0f0";
    int snapshot_len = 1028;
    int promiscuous = 0;
    int timeout = 1000;
    
    handle = pcap_open_live(device, snapshot_len, promiscuous, timeout, error_buffer);
    while(1){
	pcap_loop(handle, 1, my_packet_handler, NULL);
    }
    pcap_close(handle);
    return 0;
}
