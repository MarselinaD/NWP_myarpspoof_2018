/*
** EPITECH PROJECT, 2019
** arpspoof
** File description:
** coding
*/

# include "include.h"

uint8_t *get_my_macaddr(char *iface, uint8_t *buff)
{
    int fd;
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(ifr));
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
        return (NULL);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
    if (0 == ioctl(fd, SIOCGIFHWADDR, &ifr)) {
        buff = (uint8_t *)ifr.ifr_hwaddr.sa_data;
    }
    else
        return (NULL);
    close(fd);
    return (buff);
}

int create_socket(info_t info, s_t *sock)
{
    uint8_t *my_macaddr = NULL;
    arp_header_t *arp_hdr;
    uint8_t *eth_hdr;

    if ((my_macaddr = get_my_macaddr(info.iface, my_macaddr)) == NULL)
        return (free(sock), fprintf(stderr, "Failed to get mac address\n"), -1);
    memcpy(info.my_mac, my_macaddr, 6);
    if ((sock = init_socket(sock, info)) == NULL)
        return (free(sock), fprintf(stderr, "Socket failed to init\n"), -1);
    arp_hdr = init_arp_packet(sock);
    eth_hdr = init_eth_header(sock, arp_hdr);
    if (info.printbroad == true || info.printspoof == true) {
        print_packet(eth_hdr, sock);
        exit (0);
    }
    if (arp_spoof(info, sock, arp_hdr, eth_hdr) == -1)
        return (fprintf(stderr, "i enter at arp spoof and fail\n"), -1);
    return (0);
}
