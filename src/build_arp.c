/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** build_hdudp
*/

#include "myspoof.h"

void build_arp(t_spoof *_spoof)
{
    struct ether_arp *arp = (struct ether_arp*)(_spoof->packet +
    sizeof(struct ethhdr));

    arp->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    arp->ea_hdr.ar_pro = htons(ETH_P_IP);
    arp->ea_hdr.ar_hln = ETHER_ADDR_LEN;
    arp->ea_hdr.ar_pln = sizeof(in_addr_t);
    arp->ea_hdr.ar_op = htons(ARPOP_REQUEST);
    memcpy(arp->arp_sha, _spoof->s_arp.sll_addr, 6);
    memcpy(arp->arp_tha, _spoof->d_arp.sll_addr, 6);
    memcpy(arp->arp_spa, &(_spoof->s_ip.s_addr), 4);
    memcpy(arp->arp_tpa, &(_spoof->d_ip.s_addr), 4);
}

void build_arp_reply(t_spoof *_spoof)
{
    struct ether_arp *arp = (struct ether_arp*)(_spoof->packet +
    sizeof(struct ethhdr));

    arp->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    arp->ea_hdr.ar_pro = htons(ETH_P_IP);
    arp->ea_hdr.ar_hln = ETHER_ADDR_LEN;
    arp->ea_hdr.ar_pln = sizeof(in_addr_t);
    arp->ea_hdr.ar_op = htons(ARPOP_REPLY);
    memcpy(arp->arp_sha, _spoof->s_arp.sll_addr, 6);
    memcpy(arp->arp_tha, _spoof->d_arp.sll_addr, 6);
    memcpy(arp->arp_spa, &(_spoof->s_ip.s_addr), 4);
    memcpy(arp->arp_tpa, &(_spoof->d_ip.s_addr), 4);
}