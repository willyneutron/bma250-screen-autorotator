/*
     Screen autorrotator based  on BMA250 Bosch accelerometer

     This module is in charge of using xrandr functions to rotate screen when needed.

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

#ifndef XRANDR_ROTATE_H
#define XRANDR_ROTATE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <X11/extensions/Xrandr.h>

// Struct to store all data needed to perform a screen rotation
typedef struct _xrandrData{
    int screen;
    Window root;
    Display *dpy;
    XRRScreenConfiguration *sc;
} XrandrData;

/**
 * @brief initXrandrData
 *
 * Inits Xrandr structures needed for screen rotation.
 *
 * @param data  Structure where store information.
 * @return      1 if no error encountered, 0 otherwhise.
 */
int initXrandrData(XrandrData *data);

/**
 * @brief rotate
 *
 * Rotates the screen.
 *
 * @param data      Initialized xrandr data structure.
 * @param rotation  1,2,3 or 4. Each of these values represents a possible orientation
 *                  of the screen.
 */
void rotate (XrandrData *data, int rotation);

#endif
