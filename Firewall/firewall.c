/// \file firewall.c
/// \brief Reads IP packets from a named pipe, examines each packet,
/// and writes allowed packets to an output named pipe.
/// Author: Chris Dickens (RIT CS)
/// Author: Jacob R Hooker - jrh7130
///
/// This file contains proprietary information. Distribution is limited
/// to Rochester Institute of Technology faculty, students currently enrolled
/// in CSCI243: The Mechanics of Programming, graders, and student lab
/// instructors. Further distribution requires written approval from the
/// Rochester Institute of Technology Computer Science department. The
/// content of this file is protected as an unpublished work.
///
/// Copyright 2015 Rochester Institute of Technology
///
///

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "filter.h"

static int BUFFER_LENGTH = 2048;
/// Type used to control the mode of the firewall
typedef enum FilterMode_e
{
   MODE_BLOCK_ALL,
   MODE_ALLOW_ALL,
   MODE_FILTER
} FilterMode;


/// The input named pipe, "ToFirewall"
static FILE* InPipe = NULL;


/// The output named pipe, "FromFirewall"
static FILE* OutPipe = NULL;


/// Controls the mode of the firewall
volatile FilterMode Mode = MODE_FILTER;


/// The main function that performs the actual packet read, filter, and write.
/// The return value and parameter must match those expected by pthread_create.
/// @param args A pointer to a filter
/// @return Always NULL
static void* FilterThread(void* args);


/// Displays the menu of commands that the user can choose from.
static void DisplayMenu(void);


/// Opens the input and output named files.
/// @return True if successful
static bool OpenPipes(void);


/// Reads a packet from the input name pipe.
/// @param buf Destination buffer to write the packet into
/// @param bufLength The length of the supplied destination buffer
/// @param len The length of the packet
/// @return True if successful
static bool ReadPacket(unsigned char* buf, int bufLength, int* len);


/// The main function. Creates a filter, configures it, launches the
/// filtering thread, handles user input, and cleans up resources when
/// exiting.  The intention is to run this program with a command line
/// argument specifying the configuration file to use.
/// @param argc Number of command line arguments
/// @param argv Command line arguments
/// @return EXIT_SUCCESS or EXIT_FAILURE
int main(int argc, char* argv[])
{
   // TODO: implement function
   IpPktFilter packet_filter = CreateFilter();
   short command;

   if (argc<2){
     printf("Usage: firewall <config_file>");
     return EXIT_FAILURE;
   }else{
     bool flag = ConfigureFilter(packet_filter,argv[1]);
     if (flag==false)
      return EXIT_FAILURE;

   }
   pthread_t threads[1];
  pthread_create(&threads[0],NULL,FilterThread,(void*)packet_filter);
   DisplayMenu();
   for(;;){
     fflush(stdout);
     command = getc(stdin);
     if(command!='\n'){
       switch(command){
         case 49:
            Mode = MODE_BLOCK_ALL;
          break;
          case 50:
            Mode = MODE_ALLOW_ALL;
            break;
          case 51:
            Mode = MODE_FILTER;
            break;
          case 48:
            pthread_cancel(threads[0]);
            DestroyFilter(packet_filter);
            return EXIT_SUCCESS;
          default:
          break;
       }
       DisplayMenu();
     }
   }
   DestroyFilter(packet_filter);
   return EXIT_SUCCESS;
}


/// Runs as a thread and handles each packet. It is responsible
/// for reading each packet in its entirety from the input pipe,
/// filtering it, and then writing it to the output pipe. The
/// single void* parameter matches what is expected by pthread.
/// @param args An IpPktFilter
/// @return Always NULL
static void* FilterThread(void* args)
{
   // TODO: implement function
   int length;
   unsigned char buffer[BUFFER_LENGTH];
   IpPktFilter pktFilter = args;
   int *packet_length;
   packet_length = &length;
   OpenPipes();
   for(;;){
     bool flag = ReadPacket(buffer,BUFFER_LENGTH,packet_length);
     if(flag==false){
       return NULL;
     }
     ReadPacket(buffer,BUFFER_LENGTH,packet_length);
     switch(Mode){
       case MODE_BLOCK_ALL:
       case MODE_ALLOW_ALL:
        fwrite(&length,sizeof(int),1,OutPipe);
        fflush(OutPipe);
        fwrite(buffer,sizeof(char),length,OutPipe);
        fflush(OutPipe);
        break;
      case MODE_FILTER:
        if(!FilterPacket(pktFilter,buffer)){
          fwrite(&length,sizeof(int),1,OutPipe);
          fflush(OutPipe);
          fwrite(buffer,sizeof(char),length,OutPipe);
          fflush(OutPipe);
        }
      default:
      break;
     }
   }
   return NULL;
}



/// Print a menu and a prompt to stdout
static void DisplayMenu(void)
{
   printf("\n1. Block All\n");
   printf("2. Allow All\n");
   printf("3. Filter\n");
   printf("0. Exit\n");
   printf("> ");
}


/// Open the input and output named pipes that are used for reading
/// and writing packets.
/// @return True if successful
static bool OpenPipes(void)
{

   InPipe = fopen("ToFirewall", "rb");
   if(InPipe == NULL)
   {
      perror("ERROR, failed to open pipe ToFirewall:");
      return false;
   }

   OutPipe = fopen("FromFirewall", "wb");
   if(OutPipe == NULL)
   {
      perror("ERROR, failed to open pipe FromFirewall:");
      return false;
   }

   return true;
}


/// Read an entire IP packet from the input pipe
/// @param buf Destination buffer for storing the packet
/// @param bufLength The length of the supplied destination buffer
/// @param len The length of the packet
/// @return True if a packet was successfully read
static bool ReadPacket(unsigned char* buf, int bufLength, int* len)
{

  unsigned int packet_length;
  packet_length = fread(&bufLength,sizeof(int),1,InPipe);
  *len = bufLength;

  //read the length of the packet

  if(packet_length < 1){
     printf("Packet length not found\n");
     return false;
  }

  *len = bufLength;


   if(fread(buf, sizeof(char), bufLength, InPipe)){};

  return packet_length < 1 ? false : true;
}
