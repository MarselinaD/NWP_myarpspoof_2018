/*
** EPITECH PROJECT, 2019
** coding
** File description:
** free
*/

# include "include.h"

void my_free(s_t *sock, arp_header_t *arp, uint8_t *eth)
{
    free(sock);
    free(arp);
    free(eth);
}
