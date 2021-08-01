/* 
 * This file is part of the super_easy_can_tx (https://github.com/davidevansg/super_easy_can_tx).
 * Copyright (c) 2020 David Evans.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*********** Includes *************/
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>

#include <string.h>
#include <sys/ioctl.h>
#include <sys/timerfd.h>

#ifndef __DEFS_H_
#define __DEFS_H_

#define SUCCESS          (0)
#define FAILURE          (1)

#define IF_VCAN0		"vcan0"

#endif

/*********** Static Functions ***********/
static void MakeAndSendFrame(void);
static void PrintCANFrame(struct can_frame *fra);
static uint8_t CANIfcInit(void);
/*********** Static Variables ***********/
static int can_fd;
/*********** Global Variables ***********/

/************************************************************
 * Function Name MakeAndSendCANFrame
 *
 * Purpose: Declare a CAN frame, give it an ID and DLC,
 *              and send it! Maybe print it, if you're
 *              interested
 *
 * \param[in] void
 *
 * \return
 *      void
 ***********************************************************
 */
static void MakeAndSendCANFrame1(void)
{
    struct can_frame fra;
    uint8_t size = 8;
    fra.can_id = 0x100;
    fra.can_dlc = 8;

    
    fra.data[0] = "h";
    fra.data[1] = "e";
    fra.data[2] = "l";
    fra.data[3] = "l";
    fra.data[4] = "o";
    fra.data[5] = "p";
    fra.data[6] = "e";
    fra.data[7] = "e";

    size = send(can_fd, &fra, sizeof(struct can_frame), MSG_DONTWAIT);
    if(size != sizeof(struct can_frame))
    {
        printf("Problem writing frame\nIs your CAN interface 'up'\n");
        return;
    }
    else
    {
        // Sending success, let's print what was sent
        PrintCANFrame(&fra);
    }
}


static void MakeAndSendCANFrame(void)
{
    struct can_frame fra;
    uint8_t size = 8;
    fra.can_id = 0x100;
    fra.can_dlc = 8;

    
    fra.data[0] = "t";
    fra.data[1] = "t";
    fra.data[2] = "t";
    fra.data[3] = "t";
    fra.data[4] = "t";
    fra.data[5] = "t";
    fra.data[6] = "t";
    fra.data[7] = "e";

    size = send(can_fd, &fra, sizeof(struct can_frame), MSG_DONTWAIT);
    if(size != sizeof(struct can_frame))
    {
        printf("Problem writing frame\nIs your CAN interface 'up'\n");
        return;
    }
    else
    {
        // Sending success, let's print what was sent
        PrintCANFrame(&fra);
    }
}
/************************************************************
 * Function Name PrintCANFrame
 *
 * Purpose: Prints the contents of a given CAN frame.
 *
 * \param[in] *fra
 *      A pointer to can_frame structure (see /linux/can.h)
 *
 * \return void
 *
 ***********************************************************
 */
static void PrintCANFrame(struct can_frame *fra)
{
    if(fra != NULL)
    {
        printf("ID = %04x ", (*fra).can_id);
        printf("DLC = [%02x] - ", (*fra).can_dlc);
        for(int i = 0; i < (*fra).can_dlc; i++)
        {
            printf("B%d|%02x ", i, (*fra).data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("fra null\n");
    }
}

/************************************************************
 * Function Name 
 *
 * Purpose: Initialises the CAN interface and sets up
 *          the correpsonding options
 *
 * \param[in] void
 *
 * \return
 *      SUCCESS if successfully created, otherwise
 *      FAILURE
 ***********************************************************
 */
static uint8_t CANIfcInit(void)
{
    struct ifreq ifr;
    struct sockaddr_can addr;

    /* Create a socket */
    can_fd = socket(AF_CAN, SOCK_RAW, CAN_RAW);
    if (can_fd < 0)
    {
        printf("Cannot create socket, quitting\n");
        return FAILURE;
    }
    strcpy(ifr.ifr_name, IF_VCAN0);

    /* Associate socket with interface (e.g. "vcan0" */
    if(ioctl(can_fd, SIOCGIFINDEX, &ifr) < 0)
    {
        printf("Cannot link socket with interface - does the interface exist?\n");
        return FAILURE;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("Unable to bind socket, quitting\n");
        return FAILURE;
    }

    return SUCCESS;
}

/************************************************************
 * Function Name main
 *
 * Purpose: main entry point for the application
 *
 * \param[in] void
 *
 * \return
 *      0 - when done.
 ***********************************************************
 */
 int escolha;
int main(int argc, char *argv[])
{
    /* setup the CAN interface */
    if (CANIfcInit() == SUCCESS)
    {
    while(1)
    {
    printf("escolha a função: 1 ou 2");
    scanf("%d", &escolha);
    if(escolha==1)
    {
    MakeAndSendCANFrame();
    }
    if(escolha==2)
    {
    MakeAndSendCANFrame1();
    }
    }
    }

    /* Finished, close the file descriptor */
    if(can_fd > 0)
    {
        close(can_fd);
    }

    printf("quiting...\n");
    return 0;
}
