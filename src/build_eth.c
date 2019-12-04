/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** build_hdip
*/

#include "myspoof.h"

void build_eth(t_spoof *_spoof)
{
    struct ethhdr *eth = (struct ethhdr*)(_spoof->packet);

    memcpy(eth->h_source, _spoof->s_arp.sll_addr, 6);
    memcpy(eth->h_dest, _spoof->d_arp.sll_addr, 6);
    eth->h_proto = htons(ETH_P_ARP);
}
