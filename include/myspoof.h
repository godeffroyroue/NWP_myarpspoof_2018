/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** mychap
*/

#pragma once

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <bits/ioctls.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <errno.h> 
#include <stdbool.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <netinet/if_ether.h>

#define SIZE_PAQUET sizeof(struct ethhdr) + sizeof(struct ether_arp)
#define handle_error(msg) \
do { dprintf(2, RED "[ERROR] %s\n", RESET msg); exit(84); } while (0)

typedef struct t_spoof
{
    char *source_ip;
    uint8_t src_mac_found[ETHER_ADDR_LEN];
    uint8_t mac_found[6];
    char *dest_ip;
    char *iface;
    bool printSpoof;
    bool printBroadcast;
    char *printMac;
    struct sockaddr_ll device;
    struct addrinfo hints;
    int sock_fd;
    struct in_addr s_ip;
    struct in_addr d_ip;
    struct sockaddr_ll s_arp;
    struct sockaddr_ll d_arp;
    uint8_t buffer[6];
    uint8_t mac_addr[ETHER_ADDR_LEN];
    uint8_t packet[ETH_DATA_LEN];
} t_spoof;


void send_broadcast(t_spoof *_spoof);
void init_socket(t_spoof *_spoof);
void build_arp(t_spoof *_spoof);
void build_eth(t_spoof *_spoof);
void send_arp_paquet(t_spoof *_spoof);
void print_packet(t_spoof *_spoof);
void build_arp_reply(t_spoof *_spoof);
void send_spoof(t_spoof *_spoof);
void init_secsocket(t_spoof *_spoof, socklen_t size);