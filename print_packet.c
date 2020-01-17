/*
** EPITECH PROJECT, 2019
** print broadcast
** File description:
** coding
*/

# include "include.h"

void print_packet(uint8_t *eth_hdr, s_t *s)
{
    size_t i = 0;

    for (i = 0; i < s->size - 1; i++) {
        printf("%02x", eth_hdr[i]);
        printf(" ");
    }
    printf("%02x\n", eth_hdr[i]);
}
