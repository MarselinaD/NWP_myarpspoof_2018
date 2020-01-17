/*
** EPITECH PROJECT, 2019
** main
** File description:
** coding
*/

# include "include.h"

void print_usage(void)
{
    fprintf(stderr, "Usage: ./myARPspoof source_ip destination_ip interface ");
    fprintf(stderr, "[--printBroadcast] [--printSpoof  Mac addr]\n");
}

info_t init_info(info_t info)
{
    info.src_ip = NULL;
    info.dest_ip = NULL;
    info.iface = NULL;
    info.printbroad = false;
    info.printspoof = false;
    return (info);
}

info_t fill_args(info_t info, char *src, char *dest, char *iface)
{
    info.src_ip = strdup(src);
    info.dest_ip = strdup(dest);
    info.iface = strdup(iface);
    return (info);
}

uint8_t *converter(char *str)
{
    uint8_t *buff = malloc(6);
    int i = 0;
    char byte[3];

    for (int  a = 0; a < 6; a++) {
        strncpy(byte, &str[i], 2);
        byte[2] = '\0';
        buff[a] = strtol(byte, NULL, 16);
        i = i + 3;
    }
    return (buff);
}

int check_argv(int ac, char **av, info_t info)
{
    s_t *sock;

    if (check_ip(av[1], av[2]) == -1 || check_interface(av[3]) == -1)
        return (-1);
    info = fill_args(info, av[1], av[2], av[3]);
    if (ac == 5) {
        if (strcmp(av[4], "--printBroadcast") != 0)
            return (-1);
        info.printbroad = true;
    }
    else if (ac == 6) {
        if (strcmp(av[4], "--printSpoof") != 0)
            return (-1);
        info.macaddr = converter(av[5]);
        info.printspoof = true;
    }
    sock = malloc(sizeof(s_t));
    if (create_socket(info, sock) == -1)
        return (-1);
    return (0);
}

int main(int ac, char **av)
{
    info_t info;

    info = init_info(info);
    if (ac < 4 || ac > 6)
        return (print_usage(), 84);
    else if (check_argv(ac, av, info) == -1)
        return (84);
    return (0);
}
