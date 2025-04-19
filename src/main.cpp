#include <iostream>
#include <cstring>      // For memset
#include <sys/socket.h> // For socket functions
#include <netinet/ip.h> // For iphdr struct
#include <arpa/inet.h>  // For inet_ntoa
#include <unistd.h>     // For close()

int main() {

    int sock_raw;
    struct sockaddr_in source, dest;
    socklen_t saddr_size;
    unsigned char *buffer = new unsigned char[65536];
    
    // Create a raw socket
    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock_raw < 0) {
        std::cerr << "Socket Error" << std::endl;
        return 1;
    }

    std::cout << "[+] MiniWall Started - Listening for TCP Packets..." << std::endl;

    while (true) {
        saddr_size = sizeof(source);
        // Receive a packet
        int data_size = recvfrom(sock_raw, buffer, 65536, 0, (struct sockaddr*)&source, &saddr_size);
        if (data_size < 0) {
            std::cerr << "Recvfrom error" << std::endl;
            return 1;
        }

        struct iphdr *ip = (struct iphdr*)buffer;

        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = ip->saddr;

        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = ip->daddr;

        std::cout << "[+] Packet: " 
                  << inet_ntoa(source.sin_addr) 
                  << " --> " 
                  << inet_ntoa(dest.sin_addr) 
                  << std::endl;
    }

    close(sock_raw);
    delete[] buffer;
    return 0;
}
