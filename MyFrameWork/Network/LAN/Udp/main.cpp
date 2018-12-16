#include <netinet/in.h>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
using namespace std;

const int PDW_SOURCE_PORT = 5001;
char DEST_PORT[] = "5001";
char DEST_IP[16] = "localhost";

int pdw_sock;
sockaddr_in pdw_addrListen = {};
sockaddr_storage pdw_addrDest = {};

bool openUDPSocket(int &sock,int src_port,char * dest_port,sockaddr_in *addrListen,sockaddr_storage & sockaddrStorage);
int resolvehelper(const char* hostname,__socket_type type, int family, const char* service, sockaddr_storage* pAddr);

bool sendToGui(int * sock,u_char * packet,int len,sockaddr_storage & sockaddrStorage);

void readPacket(int *sock,void * callBack(u_char * packet,int len));
void *my_packet_handler(u_char *packet,int len);

int main(int argc,char **argv) {
    openUDPSocket(pdw_sock, PDW_SOURCE_PORT, DEST_PORT, &pdw_addrListen, pdw_addrDest);
    int send_bytes = sendToGui(&pdw_sock, (u_char*)"Hello",5, pdw_addrDest);
    if (!send_bytes) {
        fprintf(stderr, "\nError sending the packet: \n");
    }
    readPacket(&pdw_sock, &my_packet_handler);
    return 0;
}
//=======================================================================================================
bool openUDPSocket(int &sock, int src_port, char *dest_port, sockaddr_in *addrListen, sockaddr_storage &sockaddrStorage) {
    *addrListen = {};
    int result = 0;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
//    result=setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, "lo", 4);
    addrListen->sin_family = AF_INET;
    addrListen->sin_port= htons(src_port);
    result = bind(sock, (sockaddr *) addrListen, sizeof(*addrListen));
    if (result == -1) {
        int lasterror = errno;
        cout << "error: " << lasterror;
        return false;
    }
    result = resolvehelper(DEST_IP, SOCK_DGRAM,AF_INET, dest_port, &sockaddrStorage);
    if (result != 0) {
        int lasterror = errno;
        cout << "error: " << lasterror;
        return false;
    }
    return true;
}
//=======================================================================================================
int resolvehelper(const char* hostname,__socket_type type, int family, const char* service, sockaddr_storage* pAddr)
{
    int result;
    addrinfo* result_list = nullptr;
    addrinfo hints = {};
    hints.ai_family = family;
    hints.ai_socktype = type; // without this flag, getaddrinfo will return 3x the number of addresses (one for each socket type).
    result = getaddrinfo(hostname, service, &hints, &result_list);
    if (result == 0)
    {
        //ASSERT(result_list->ai_addrlen <= sizeof(sockaddr_in));
        memcpy(pAddr, result_list->ai_addr, result_list->ai_addrlen);
        freeaddrinfo(result_list);
    }

    return result;
}
//=======================================================================================================
bool sendToGui(int *sock,u_char * packet,int len,sockaddr_storage & sockaddrStorage) {
    return (sendto(*sock, packet,len, 0, (sockaddr *) &sockaddrStorage, sizeof(sockaddrStorage)))!=0;
}
//=======================================================================================================
void readPacket(int *sock,void * callBack(u_char * packet,int len)) {
    u_char packet[1500];
    bool recv=false;
//    while(true){
        int res=read(*sock,packet, sizeof(packet));
        packet[res]=0;
        string str((char*)packet);
        if(res>0){
            callBack(packet,res);
        }
        if(res<0)
            cout<<"can not read"<<endl;
//        packet[0]=NULL;
//        fflush(stdout);
//    }
}
//=======================================================================================================
//When a packet is received, this function is called
void *my_packet_handler(u_char *packet,int len) {
    try {
        string str((char *) packet);
        cout<<str<<endl;
    }
    catch(...) {

    }
}
