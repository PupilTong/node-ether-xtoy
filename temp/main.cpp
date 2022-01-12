#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <uv.h>
#include <stdio.h>

#include <cerrno>
#include <string>
int main(){
    auto eth_addr = ether_aton("ab:0b:1c:d:3e:ef");
    char * addr = reinterpret_cast<char*>(eth_addr);
    for(size_t i=0; i<sizeof(ether_addr); i++){
        printf("%d ", addr[i]);
    }
    printf("\n");
    char * addrStr = ether_ntoa(eth_addr);
    printf("%s",addrStr);

}