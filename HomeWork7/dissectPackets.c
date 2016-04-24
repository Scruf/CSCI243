#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<byteswap.h>

int main(char argc, char *argv[]){
  if(argc==1){
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
      if(number_of_packets==0){
	printf("No packets were found\n");
	exit(1);
      }
      else{
	printf("==== File %s  contains %d Packets.\n",argv[1],number_of_packets);
      }
      for(int i=1;i<=number_of_packets;i++){
	printf("===>Packet %d\n",i);
	int packet_length;
	fread(&packet_length,sizeof(int),1,file);
	printf("Packet length is %d\n ",packet_length);
	buffer = (char*)malloc(packet_length);
	int buffer_size = sizeof(buffer);
	fread(buffer,sizeof(char),packet_length,file);
	char version = buffer[0]>>4;
	printf("Its supposed to be a version %#hhx (%d)",version,version);
	buffer_size=0;
	free(buffer);
      }
      
      
      fclose(file);
   
      
    
  }
}
