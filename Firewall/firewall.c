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
// static bool ReadPacket(unsigned char* buf, int bufLength, int* len);


/// The main function. Creates a filter, configures it, launches the
/// filtering thread, handles user input, and cleans up resources when
/// exiting.  The intention is to run this program with a command line
/// argument specifying the configuration file to use.
/// @param argc Number of command line arguments
/// @param argv Command line arguments
/// @return EXIT_SUCCESS or EXIT_FAILURE
int main(int argc, char* argv[])
{
  if(argc < 2)
  {
     printf("usage: ./firewall configFileName\n");
     return EXIT_FAILURE;
  }
  char input[20];
  IpPktFilter filter = CreateFilter();
  pthread_t filter_thread;
  short command = 0;

  if(!ConfigureFilter(filter, argv[1]))
  {
     return EXIT_FAILURE;
  }
  if(pthread_create(&filter_thread, NULL, FilterThread,(void*) filter) != 0)
  {
     printf("error");
  }
  DisplayMenu();
  while(Mode){
    if(fgets(input, 20, stdin)){};
    command = strtol(input, NULL, 10);
    printf("> ");
    switch(command){

      case 1:
        Mode = MODE_BLOCK_ALL;
        printf("Blocking all packets");
      break;
      case 2:
        Mode = MODE_ALLOW_ALL;
        printf("1 Allowing all packets\n");
      break;
      case 3:
        Mode = MODE_FILTER;
        printf("Filtering Packets\n");
      break;
      case 0:
        Mode =  0;
        printf ("Exiting]n");
      break;
      default:
      break;

    }
  }
  DestroyFilter(filter);


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
   int len;
   unsigned char packet[BUFFER_LENGTH];


   if(!OpenPipes() )
   {

	   return NULL;
   }
	   while(!feof(InPipe))
	   {
			if(fread(&len, sizeof(unsigned int), 1, InPipe) == 0)
				return NULL;

		      if(fread(packet, 1, len, InPipe) == 0)
				return NULL;


		   if(Mode == MODE_FILTER)
		   {
			   if(FilterPacket(args,packet))
			   {
				   fwrite(&len, sizeof(unsigned int), 1, OutPipe);
				   fwrite(packet, sizeof(char), len, OutPipe);
				   fflush(OutPipe);
			   }
		   }
		    if(Mode == MODE_BLOCK_ALL)
		      continue;
		    if(Mode == MODE_ALLOW_ALL)
		   {
				fwrite(&len, sizeof(unsigned int), 1, OutPipe);
				fwrite(packet, sizeof(char), len, OutPipe);
				fflush(OutPipe);
		   }
	   }

   fclose(OutPipe);
   fclose(InPipe);

   pthread_exit(NULL);
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


// /// Read an entire IP packet from the input pipe
// /// @param buf Destination buffer for storing the packet
// /// @param bufLength The length of the supplied destination buffer
// /// @param len The length of the packet
// /// @return True if a packet was successfully read
// static bool ReadPacket(unsigned char* buf, int bufLength, int* len)
// {
//
//   unsigned int packet_length;
//   packet_length = fread(&bufLength,sizeof(int),1,InPipe);
//   *len = bufLength;
//
//   //read the length of the packet
//
//   if(packet_length < 1){
//      printf("Packet length not found\n");
//      return false;
//   }
//
//   *len = bufLength;
//
//
//    if(fread(buf, sizeof(char), bufLength, InPipe)){};
//
//   return packet_length < 1 ? false : true;
// }
