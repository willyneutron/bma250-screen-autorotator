/*
      Screen autorrotator based  on BMA250 Bosch accelerometer

      This program is designed to run from systemd and poll BMA250 accelerometer
      for position info. Depending of this data, screen will be rotated using xrandr.

      Copyright (c) 2018 Guillermo Climent, https://github.com/willyneutron

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "i2c_bma250.h"
#include "xrandr_rotate.h"

#ifdef XDEVICE
    #include "xinput_rotate.h"
#endif

// Search for BMA250 in this I2C bus. Check i2cdetect -y -r <device>
#ifndef BMA250_I2C_BUS
#define BMA250_I2C_BUS 2
#endif

// I2C addr of the BMA250 inside BMA250_I2C_BUS
#ifndef BMA250_I2C_ADDR
#define BMA250_I2C_ADDR 0x18
#endif

// Polling time in usecs
#ifndef POLLING_USECS
#define POLLING_USECS 500 * 1000
#endif

// Threshold for 0 value in the accel axis
#ifndef ACCEL_VALUE_THRESHOLD
#define ACCEL_VALUE_THRESHOLD 10
#endif

volatile sig_atomic_t stopRequested = 0;

void term(int signum)
{
    #ifdef DEBUG
        printf("SIGTERM catched. Exiting...\n");
    #endif

    stopRequested = 1;
}

int main(int argc, char *argv[]) {
    int x, y, z;
    int i2cHandle;
    char filename[20];

    XrandrData xrandrData;
    int current_rotation = 0, new_rotation = 0;

    // Configure SIGTERM catch
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    #ifdef DEBUG
        printf("Open I2C bus... ");
    #endif

    snprintf(filename, 19, "/dev/i2c-%d", BMA250_I2C_BUS);
    i2cHandle = open(filename, O_RDWR);
    if (i2cHandle < 0) {
        fprintf(stderr, "Error while opening device %s: %d error\n",filename,errno);
        exit(1);
    }

    #ifdef DEBUG
        printf("OK !\nInitializing BMA250... ");
    #endif

    if (!BMA250_init(i2cHandle, BMA250_I2C_ADDR)){
        fprintf(stderr, "Error while initializing BMA250\n");
        exit(1);
    }

    #ifdef DEBUG
        printf("OK !\n");
    #endif

    #ifdef DEBUG
        printf("Initializing Xrandr... ");
    #endif

    if (!initXrandrData(&xrandrData)){
        fprintf(stderr, "Error initializing Xrandr\n");
	exit(1);
    }

    #ifdef DEBUG
        printf("OK !\n");
    #endif

    while(!stopRequested) {
        usleep(POLLING_USECS);
        BMA250_readAccel(i2cHandle, BMA250_I2C_ADDR, &x, &y, &z);

        #ifdef DEBUG
            printf("Readed x:%d y:%d z:%d\n", x, y, z);
        #endif

        if (x > -ACCEL_VALUE_THRESHOLD && x < ACCEL_VALUE_THRESHOLD){
            if (y > 0){
                new_rotation = 3;
            }else{
                new_rotation = 1;
            }
        }else if (y > -ACCEL_VALUE_THRESHOLD && y < ACCEL_VALUE_THRESHOLD){
            if (x > 0){
                new_rotation = 0;
            }else{
                new_rotation = 2;
            }
        }

        if (new_rotation != current_rotation){

            #ifdef DEBUG
                printf("Rotating to %d\n", new_rotation);
            #endif

            #ifdef XDEVICE
                xinputRotate(xrandrData.dpy, new_rotation);
            #endif

            xrandrRotate(&xrandrData, new_rotation);
            current_rotation = new_rotation;
        }
    }

    close(i2cHandle);

    return 0;
}
