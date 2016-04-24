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
                        int packet_length;
                        fread(&packet_length,sizeof(int),1,file);
                        printf("Packet length is %d\n ",packet_length);
                        buffer = (char*)malloc(packet_length);
                        int buffer_size = sizeof(buffer);
                        fread(buffer,sizeof(char),packet_length,file);
                        char version = buffer[0] >> 4;
                        printf("Version:\t\t%#hhx (%d)\n", version, version);
                        buffer_size=0;
                        //separate ihl from the first byte
                        char ihl = buffer[0] & 0x0F;
                        printf("IHL (Header Length):\t\t0x%hhx (%d)\n",ihl,ihl);
                        char type_of_service = buffer[1];
                        if(type_of_service == 0)
                          printf("Type of Service (TOS):\t\t0x%#hhx (%d)\n",type_of_service,type_of_service);
                        else
                          printf("Type of Service (TOS):\t\t%#hhx (%d)\n",type_of_service,type_of_service);
                        free(buffer);
                }


                fclose(file);



        }
}
