#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <byteswap.h>

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
                        unsigned char version = buffer[0] >> 4;
                        printf("Version:\t\t%#hhx (%d)\n", version, version);

                        //separate ihl from the first byte
                        char ihl = buffer[0] & 0x0F;
                        printf("IHL (Header Length):\t\t0x%hhx (%d)\n",ihl,ihl);
                        unsigned char type_of_service = buffer[1];
                        if(type_of_service == 0)
                          printf("Type of Service (TOS):\t\t0x%#hhx (%d)\n",type_of_service,type_of_service);
                        else
                          printf("Type of Service (TOS):\t\t%#hhx (%d)\n",type_of_service,type_of_service);
                        unsigned char total_length = buffer[2]+buffer[3];
                        printf("Total Length\t\t%#hhx (%d)\n",total_length,total_length);
                        unsigned int id = buffer[4]+buffer[5];
                        printf("Identification:\t\t0x%X (%hu)\n",id,id);
                        unsigned char flag=buffer[6];
                        printf("IP Flags:\t\t%#hhx (%d)\n",flag,flag);
                        unsigned char fragment_offset =(buffer[6] << 3) + buffer[7];
                        printf("Fragment Offset:\t\t%#hhx (%d)\n",fragment_offset,fragment_offset);
                        unsigned char time_to_live = buffer[8];
                        printf("Time to Live (TTL):\t\t%#hhx (%d)\n",time_to_live,time_to_live);
                        unsigned char protocol = buffer[9];
                        if(protocol==1)
                          printf("Protocol:\t\tICMP %#hhx (%d)\n",protocol,protocol);
                        else
                          printf("Protocol:\t\tTCP %#hhx (%d)\n",protocol,protocol);
                        unsigned int check_sum = buffer[10]+buffer[11];
                        printf("Header Checksum:\t\t0x%X (%hu)\n",check_sum,check_sum);
                        printf("Source Address:\t\t%d.%d.%d.%d\n",buffer[12],buffer[13],buffer[14],buffer[15]);
                        printf("Destination Address:\t\t%d.%d.%d.%d\n",buffer[16],buffer[17],buffer[18],buffer[19]);
                        buffer_size=0;
                        free(buffer);
                }


                fclose(file);



        }
}
