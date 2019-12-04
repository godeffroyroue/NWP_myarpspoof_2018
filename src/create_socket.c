/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** create_socket
*/

#include "myspoof.h"

void init_socket(t_spoof *_spoof)
{
    uint8_t mac[8] = {0};
    socklen_t size = sizeof(struct sockaddr_ll);
    unsigned char broadcast[ETHER_ADDR_LEN] = {0xff, 0xff, 0xff, 0xff,
    0xff, 0xff};

    if (_spoof->printBroadcast == false && _spoof->printSpoof == false) {
        if ((_spoof->sock_fd = socket(AF_PACKET,
        SOCK_RAW, htons(ETH_P_ARP))) == -1)
            handle_error("creation socket");
    }
    _spoof->d_arp.sll_family = AF_PACKET;
    _spoof->d_arp.sll_halen = ETHER_ADDR_LEN;
    _spoof->d_arp.sll_protocol = htons(ETH_P_ARP);
    _spoof->d_arp.sll_ifindex = if_nametoindex(_spoof->iface);
    memcpy(_spoof->d_arp.sll_addr, broadcast, ETHER_ADDR_LEN);
    memcpy(&_spoof->s_arp, &_spoof->d_arp, sizeof(struct sockaddr_ll));
    memcpy(_spoof->s_arp.sll_addr, mac, ETHER_ADDR_LEN);
    inet_aton(_spoof->dest_ip, &_spoof->d_ip);
    inet_aton(_spoof->source_ip, &_spoof->s_ip);
    init_secsocket(_spoof, size);
}

void init_secsocket(t_spoof *_spoof, socklen_t size)
{
    if (_spoof->printBroadcast == false && _spoof->printSpoof == false) {
        if (bind(_spoof->sock_fd, (struct sockaddr*)&_spoof->s_arp,
        size) == -1)
            handle_error("Bind");
    }
    if (_spoof->printSpoof == true) {
        sscanf(_spoof->printMac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &_spoof->mac_addr[0], &_spoof->mac_addr[1], &_spoof->mac_addr[2],
        &_spoof->mac_addr[3], &_spoof->mac_addr[4], &_spoof->mac_addr[5]);
        memcpy(_spoof->d_arp.sll_addr, _spoof->mac_addr, ETHER_ADDR_LEN);
    }
}
