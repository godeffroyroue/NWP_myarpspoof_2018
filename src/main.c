/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** main
*/

#include "myspoof.h"

void parsing_options(t_spoof *_spoof, int ac, char **av)
{
    if (ac > 4) {
        if (strcmp(av[4], "--printSpoof") == 0) {
                _spoof->printSpoof = true;
                _spoof->printMac = strdup(av[5]);
        }
        else if (strcmp(av[4], "--printBroadcast") == 0)
            _spoof->printBroadcast = true;
    }
}

void parsing_arg(t_spoof *_spoof, int ac, char **av)
{
    if (ac < 4)
        handle_error("You do not have enough arguments.");
    if (gethostbyname(av[1]) == NULL)
        handle_error("Bad \"sender\" argument.");
    else
        _spoof->source_ip = strdup(av[1]);
    if (gethostbyname(av[2]) == NULL)
        handle_error("Bad \"target\" argument.");
    else
        _spoof->dest_ip = strdup(av[2]);
    if (av[3] == NULL)
        handle_error("Bad \"iface\" argument.");
    else
        _spoof->iface = strdup(av[3]);
    parsing_options(_spoof, ac, av);
}

void init_spoof_struct(t_spoof *_spoof)
{
    _spoof->source_ip = NULL;
    _spoof->dest_ip = NULL;
    _spoof->iface = NULL;
    _spoof->printSpoof = false;
    _spoof->printBroadcast = false;
    _spoof->printMac = NULL;
}

int main(int ac, char **av)
{
    struct t_spoof _spoof;

    init_spoof_struct(&_spoof);
    parsing_arg(&_spoof, ac, av);
    send_broadcast(&_spoof);
    return (0);
}