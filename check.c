/*
** EPITECH PROJECT, 2019
** check
** File description:
** coding
*/

# include "include.h"

int check_address(char *s)
{
    int i = 0;
    int count = 0;

    while (s[i]) {
        if (s[i] < '0' || s[i] > '9') {
            if (s[i] != '.')
                return (-1);
            else {
                count = 0;
            }
        }
        else
            count++;
        if (count > 3)
            return (-1);
        i++;
    }
    return (0);
}

int check_ip(char *src_ip, char *dest_ip)
{
    if (check_address(src_ip) == -1 || check_address(dest_ip) == -1)
        return (fprintf(stderr, "Error: Bad ip!\n"), -1);
    return (0);
}

int check_interface(char *iface)
{
    (void)iface;
    return (0);
}
