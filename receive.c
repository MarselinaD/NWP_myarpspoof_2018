/*
** EPITECH PROJECT, 2019
** receive
** File description:
** coding
*/

# include "include.h"

int check_buff(uint8_t buff[1518], s_t *sock)
{
    if (memcmp(buff, sock->src.sll_addr, 6))
        return (-1);
    return (0);
}

int receive_message(s_t *sock, uint8_t *received)
{
    socklen_t len = sizeof(struct sockaddr_ll);
    uint8_t buff[1518];

    do {
        recvfrom(sock->sockfd, buff, sizeof(buff), 0,  \
        (struct sockaddr *)&(sock->dest), &len);
    } while (check_buff(buff, sock) == -1);
    for (int i = 0; i < 6; i++)
        received[i] = buff[6+i];
    memcpy(sock->dest.sll_addr, received, ETH_ALEN);
    return (0);
}
