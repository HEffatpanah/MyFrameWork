#include <stdlib.h>
#include <stdio.h>

#include <pcap.h>


int main(int argc, char **argv)
{
    u_char packet[100];
    int i;
    pcap_t *handle;
    char error_buffer[PCAP_ERRBUF_SIZE];
    char *device = (char *) "enp1s0f0";
    int snapshot_len = 1028;
    int promiscuous = 0;
    int timeout = 1000;

    handle = pcap_open_live(device, snapshot_len, promiscuous, timeout, error_buffer);
    if (handle == NULL) {
        printf("Could not open interface wlan0 for packet injection: %s", error_buffer);
        return 2;
    }

    /* Supposing to be on ethernet, set mac destination to 1:1:1:1:1:1 */
    packet[0]=0x20;
    packet[1]=0x1a;
    packet[2]=0x06;
    packet[3]=0xd2;
    packet[4]=0x0e;
    packet[5]=0xf5;

    /* set mac source to 2:2:2:2:2:2 */
    packet[6]=0x20;
    packet[7]=0x1a;
    packet[8]=0x06;
    packet[9]=0xd2;
    packet[10]=0x0e;
    packet[11]=0xf5;
    packet[12]=0xe8;
    packet[13]=0x01;

    /* Fill the rest of the packet */
    for(i=14;i<100;i++)
    {
        packet[i]= (u_char) (i % 256);
    }

    /* Send down the packet */
    int a=pcap_sendpacket(handle,packet, 100 /* size */);
    if (a != 0)
    {
        fprintf(stderr,"\nError sending the packet: \n");
        return 0;
    }

    return 0;
}
