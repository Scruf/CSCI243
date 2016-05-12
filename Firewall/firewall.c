/// \file firewall.c
/// \brief Reads IP packets from a named pipe, examines each packet,
/// and writes allowed packets to an output named pipe.
/// Author: Chris Dickens (RIT CS)
///
///
/// This file contains proprietary information. Distribution is limited
/// to Rochester Institute of Technology faculty, students currently enrolled
/// in CSCI243: The Mechanics of Programming, graders, and student lab
/// instructors. Further distribution requires written approval from the
/// Rochester Institute of Technology Computer Science department. The
/// content of this file is protected as an unpublished work.
///
/// Copyright 2015 Rochester Institute of Technology
///Zahir Javaid
///CS243

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "filter.h"


/// Type used to control the mode of the firewall
typedef enum FilterMode_e
{
        MODE_BLOCK_ALL = 1,
        MODE_ALLOW_ALL = 2,
        MODE_FILTER = 3
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


/// The main function. Creates a filter, configures it, launches the
/// filtering thread, handles user input, and cleans up resources when
/// exiting.  The intention is to run this program with a command line
/// argument specifying the configuration file to use.
/// @param argc Number of command line arguments
/// @param argv Command line arguments
/// @return EXIT_SUCCESS or EXIT_FAILURE
int main(int argc, char* argv[])
{
        char user_input[20];
        IpPktFilter filter = CreateFilter();
        pthread_t mythread;
        short command = 0;
        if(argc != 2)
        {
                printf("usage: ./firewall configFileName\n");
                return EXIT_FAILURE;
        }
        if(!ConfigureFilter(filter, argv[1]))
        {
                return EXIT_FAILURE;
        }
        if(pthread_create(&mythread, NULL, FilterThread,(void*) filter) != 0)
        {
                printf("error");
        }
        DisplayMenu();
        while(Mode) {

                if(fgets(user_input, 20, stdin)) {};
                command = strtol(user_input, NULL, 10);
                printf("> ");
                switch(command) {
                case 1:
                        Mode = MODE_BLOCK_ALL;
                        printf("1. Blocking all packets\n");
                        break;
                case 2:
                        Mode = MODE_ALLOW_ALL;
                        printf ("2. Allowing all packets\n");
                        break;
                case 3:
                        Mode = MODE_FILTER;
                        printf("3. Filtering Packets\n");
                        break;
                case 0:
                        Mode = 0;
                        printf("Exiting");
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
        unsigned char newpacket[2048];


        if(!OpenPipes())
        {

                return NULL;
        }
        while(!feof(InPipe))
        {
                if(fread(&len, sizeof(unsigned int), 1, InPipe) == 0)
                        return NULL;


                if(fread(newpacket, 1, len, InPipe) == 0)
                        return NULL;
                switch(Mode) {
                case 1:
                        continue;
                        break;
                case 2:

                        fwrite(&len, sizeof(unsigned int), 1, OutPipe);
                        fwrite(newpacket, sizeof(char), len, OutPipe);
                        fflush(OutPipe);

                case 3:
                        if(FilterPacket(args,newpacket))
                        {
                                fwrite(&len, sizeof(unsigned int), 1, OutPipe);
                                fwrite(newpacket, sizeof(char), len, OutPipe);
                                fflush(OutPipe);
                        }
                        break;
                default:
                        break;
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
