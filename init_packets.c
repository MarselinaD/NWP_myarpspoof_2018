/*
** EPITECH PROJECT, 2019
** init
** File description:
** coding
*/

# include "include.h"

arp_header_t *init_arp_packet(s_t *sock)
{
    arp_header_t *arp_header;

    arp_header = malloc(sizeof(arp_header_t));
    arp_header->htype = htons(1);
    arp_header->ptype = htons(ETH_P_IP);
    arp_header->hlen = 6;
    arp_header->plen = 4;
    arp_header->opcode = htons(1);
    memcpy(arp_header->sender_mac, &sock->src.sll_addr, 6);
    memcpy(arp_header->sender_ip, &sock->src_ip.s_addr, 4);
    memcpy(arp_header->target_mac, &sock->dest.sll_addr, 6);
    memcpy(arp_header->target_ip, &sock->dest_ip.s_addr, 4);
    return (arp_header);
}

uint8_t *init_eth_header(s_t *sock, arp_header_t *arp_hdr)
{
    uint8_t *eth_hdr = NULL;

    eth_hdr = malloc(sizeof(arp_header_t) + 14);
    memcpy(eth_hdr, &sock->dest.sll_addr, 6 * sizeof(uint8_t));
    memcpy(eth_hdr + 6, &sock->src.sll_addr, 6 * sizeof(uint8_t));
    eth_hdr[12] = ETH_P_ARP / 256;
    eth_hdr[13] = ETH_P_ARP % 256;
    sock->size = 6 + 6 + 2 + sizeof(arp_header_t);
    memcpy(eth_hdr + 14, arp_hdr, sizeof(arp_header_t) * sizeof(uint8_t));
    return (eth_hdr);
}

int get_iface_index(char *iface, int iface_indx)
{
    int fd;
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(ifr));
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
        return (-1);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
    if (0 == ioctl(fd, SIOCGIFINDEX, &ifr)) {
        iface_indx = ifr.ifr_ifindex;
    }
    else
        return (-1);
    close(fd);
    return (iface_indx);
}

s_t *init_socket(s_t *sock, info_t info)
{
    int index = 0;
    unsigned char broad[ETHER_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    sock->dest.sll_family = AF_PACKET;
    sock->dest.sll_halen = ETHER_ADDR_LEN;
    sock->dest.sll_protocol = htons(ETH_P_ARP);
    sock->dest.sll_hatype = htons(1);
    if ((index = get_iface_index(info.iface, index)) == -1)
        return (NULL);
    sock->dest.sll_ifindex = index;
    if (info.printspoof == true) {
        memcpy(sock->dest.sll_addr, info.macaddr, 6);
    }
    else
        memcpy(sock->dest.sll_addr, broad, ETHER_ADDR_LEN);
    memcpy(sock->src.sll_addr, info.my_mac, ETHER_ADDR_LEN);
    inet_aton(info.dest_ip, &sock->dest_ip);
    inet_aton(info.src_ip, &sock->src_ip);
    return (sock);
}
