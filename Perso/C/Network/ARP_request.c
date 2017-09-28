#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/if.h>

void endl(){
  printf("\n");
}

int main(int argc, char * argv[]){

  int error;
  int sock = socket(AF_PACKET, SOCK_DGRAM, 0x61);

  if(getuid()){
    printf("You're not root pussy\n");
    return 1;
  }

  if(argc != 2){
    printf("Usage : ./ARP_request IFACE\n");
    return 1;
  }

  struct sockaddr_ll * addr = malloc(sizeof(struct sockaddr_ll)); memset(addr, 0, sizeof(struct sockaddr_ll));
  struct ifreq * req = malloc(sizeof(struct ifreq)); memset(req, 0, sizeof(struct ifreq));

  strncpy(req->ifr_name, argv[1], strlen(argv[1]));

  if(ioctl(sock, SIOCGIFINDEX) == -1){
    perror("[SIOCGIFINDEX] ioctl error");
    return 1;
  }
  
  unsigned char mac_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  addr->sll_family   = AF_PACKET;
  addr->sll_protocol = 0x0608;
  addr->sll_ifindex  = req->ifr_ifindex;
  addr->sll_halen    = 6;
  memcpy(addr->sll_addr, mac_addr, addr->sll_halen);

  unsigned char buffer[28] =
  {0x00, 0x01, 0x08, 0x00,
   0x06, 0x04, 0x00, 0x01,
   0x88, 0x78, 0x73, 0x9c,
   0x78, 0xdb, 0xc0, 0xa8,
   0x01, 0x5b, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0xc0, 0xa8, 0x01, 0x01};


  int size = sendto(sock, &buffer, 28, 0, (const struct sockaddr *) (addr), sizeof(const struct sockaddr_ll));

  if(size != -1){
    printf("\nSent : %i bytes\n", size);
  } else {
    perror("Error");
  }

  free(addr);

}
