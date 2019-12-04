/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** print_packet
*/

#include "myspoof.h"

void print_packet(t_spoof *_spoof)
{
    for (size_t i = 0; i < SIZE_PAQUET; i++) {
        printf("%02x", _spoof->packet[i]);
        if (i != SIZE_PAQUET - 1)
            printf(" ");
    }
    printf("\n");
}