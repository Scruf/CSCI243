#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int main(char argc, char *argv[]){
        if(argc==1) {
                printf("No file was specified");
                exit(1);
        }

        else{
                FILE *file;
                file = fopen(argv[1],"rb");
                size_t buffer_size = 2048;
                char *buffer;
                int number_of_packets;
                fread(&number_of_packets, sizeof(int),1,file);
                if(number_of_packets==0) {
                        printf("No packets were found\n");
                        exit(1);
                }
                else{
                        printf("==== File %s  contains %d Packets.\n",argv[1],number_of_packets);
                }
                for(int i=1; i<=number_of_packets; i++) {
                        printf("===>Packet %d\n",i);
                        unsigned int packet_length;
                        fread(&packet_length,sizeof(int),1,file);

                        buffer = (char*)malloc(packet_length);
                        int buffer_size = sizeof(buffer);
                        fread(buffer,sizeof(char),packet_length,file);
                        //shifts bytes right by 4 to find version
                        unsigned char version = buffer[0] >> 4;
                        printf("Version:\t\t%#hhx (%d)\n", version, version);

                        //separate ihl from the first byte
                        char ihl = buffer[0] & 0x0F;
                        printf("IHL (Header Length):\t\t0x%hhx (%d)\n",ihl,ihl);
                        //prints the type of service
                        unsigned char type_of_service = buffer[1];
                        if(type_of_service == 0)
                                printf("Type of Service (TOS):\t\t0x%#hhx (%d)\n",type_of_service,type_of_service);
                        else
                                printf("Type of Service (TOS):\t\t%#hhx (%d)\n",type_of_service,type_of_service);
                        //get the total length by adding third and fourth bytes
                        unsigned char total_length = buffer[2]+buffer[3];
                        printf("Total Length\t\t%#hhx (%d)\n",total_length,total_length);
                        //gets the identification number by adding fourtth and fifth bytes
                        unsigned int id = buffer[4]+buffer[5];
                        printf("Identification:\t\t0x%X (%hu)\n",id,id);
                        //finmd and prints the flag
                        unsigned char flag=buffer[6];
                        printf("IP Flags:\t\t%#hhx (%d)\n",flag,flag);
                        //gets the fragment offset by shifting left to the right and adding seventh bytes
                        unsigned char fragment_offset =(buffer[6] << 3) + buffer[7];
                        printf("Fragment Offset:\t\t%#hhx (%d)\n",fragment_offset,fragment_offset);
                        //gets time to live from eights byte
                        unsigned char time_to_live = buffer[8];
                        printf("Time to Live (TTL):\t\t%#hhx (%d)\n",time_to_live,time_to_live);
                        //gets the protocol from the nineth byte
                        unsigned char protocol = buffer[9];
                        if(protocol==1)
                                printf("Protocol:\t\tICMP %#hhx (%d)\n",protocol,protocol);
                        else
                                printf("Protocol:\t\tTCP %#hhx (%d)\n",protocol,protocol);
                        //gets the check sum by adding the tens and elevens bytes
                        unsigned int check_sum = buffer[10]+buffer[11];
                        printf("Header Checksum:\t\t0x%X (%hu)\n",check_sum,check_sum);
                        //gets the first part of network address
                        int network_source_address=buffer[12];
                        //gets the second part of the network address
                        int network_source_address_ = buffer[13];
                        //gets the first part of the host addresss
                        int host_address = buffer[14];
                        //gets the second part of host address
                        int host_address_=buffer[15];
                        if(network_source_address<0)
                                network_source_address*=-1;
                        if(network_source_address_<0)
                                network_source_address_*=-1;
                        if(host_address<0)
                                host_address*=-1;
                        if(host_address_<0)
                                host_address_*=-1;
                        printf("Source Address:\t\t%d.%d.%d.%d\n",network_source_address,network_source_address_,host_address,host_address_);
                        network_source_address = buffer[16];
                        network_source_address_= buffer[17];
                        host_address=buffer[18];
                        host_address_=buffer[19];
                        if(network_source_address<0)
                                network_source_address*=-1;
                        if(network_source_address_<0)
                                network_source_address_*=-1;
                        if(host_address<0)
                                host_address*=-1;
                        if(host_address_<0)
                                host_address_*=-1;
                        printf("Destination Address:\t\t%d.%d.%d.%d\n",network_source_address,network_source_address_,host_address,host_address_);
                        //reset buffer size to zero
                        buffer_size=0;
                        //clears the buffer
                        free(buffer);
                }
                //close the file
                fclose(file);

                return 0;

        }
}
