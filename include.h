/*
** EPITECH PROJECT, 2019
** include
** File description:
** header
*/

# ifndef INCLUDE_H_
# define INCLUDE_H_

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/ip.h>
# include <netinet/in.h>
# include <net/if.h>
# include <sys/ioctl.h>
# include <ifaddrs.h>
# include <linux/if_packet.h>
# include <net/ethernet.h> 

# define ETH_P_ARP  0x0806   /*Address Resolution packet*/
# define ETH_P_IP   0x0800   /* Internet Protocol packet*/
# define ETH_HDRLEN 14

typedef struct info {
    char *src_ip;
    char *dest_ip;
    char *iface;
    uint8_t *macaddr;
    uint8_t my_mac[6];
    bool printbroad;
    bool printspoof;
} info_t;

typedef struct arp_header {
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t opcode;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
} arp_header_t;

typedef struct arp_rcv {
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t opcode;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
} arp_rcv_t;

typedef struct sock {
    int sockfd;
    struct in_addr src_ip;
    struct in_addr dest_ip;
    struct sockaddr_ll src;
    struct sockaddr_ll dest;
    size_t size;
    uint8_t packet[ETH_DATA_LEN];
} s_t;

int create_socket(info_t, s_t *s);
int check_ip(char *, char *);
int check_interface(char *av);
int check_mac_addr(char *);
void print_packet(uint8_t *eth_hdr, s_t *s);
arp_header_t *init_arp_packet(s_t *s);
uint8_t *init_eth_header(s_t *s, arp_header_t *arp_hdr);
s_t *init_socket(s_t *sock, info_t info);
int arp_spoof(info_t info, s_t *sock, arp_header_t *arp_hdr, uint8_t *eth_hdr);
int receive_message(s_t *sock, uint8_t *received);
void my_free(s_t *sock, arp_header_t *arp, uint8_t *eth);
int check_arp_header(arp_rcv_t *arp_rcv, s_t *sock);

# endif //INCLUDE_H_
