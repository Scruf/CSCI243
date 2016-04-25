#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <byteswap.h>

/*
===========================================================================
 Name        : dissectPackets.c
 Author      : Egor Kozitski
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
 /*
  @param id =>Identification
  @param checksum=>Checksum of entire IP header
  @param version=>Version of IP Protocol
  @param ihl=>Internet Header Length
  @param type_of_service=>type of service
  @param flag=>IP flag
  @param fragment_offset=>Fragment offset from start of IP datagram
  @param time_to_live=>Upper limit of time for a datagram to exisits in network
  @param protocol=>IP protool id
 */
struct packet {
  unsigned int id;
  unsigned int checksum;
  unsigned char *version;
  unsigned char *ihl;
  unsigned char *type_of_service;
  unsigned char *total_length;
  unsigned char *flag;
  unsigned char *fragment_offset;
  unsigned char *time_to_live;
  unsigned char *protocol;

};

typedef struct packet *Packet;
FILE *file;
#define SIZE_BUFFER : 2048;


int main(char argc, char *argv[]){
  return 0;
}
