#include <iostream>
#include <cstring>      // For memset
#include <sys/socket.h> // For socket functions
#include <netinet/ip.h> // For iphdr struct
#include <arpa/inet.h>  // For inet_ntoa
#include <unistd.h>     // For close()

int main() {
    std::cout << "MiniWall Firewall Started!" << std::endl;
    return 0;
}
