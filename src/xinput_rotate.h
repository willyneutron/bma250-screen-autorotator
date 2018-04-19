/*
     Screen autorrotator based  on BMA250 Bosch accelerometer

     This module is in charge of rotating a pointing device when needed.

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

#ifndef XINPUT_ROTATE_H
#define XINPUT_ROTATE_H

#include <stdio.h>
#include <stdlib.h>

#include <X11/extensions/XInput2.h>

/**
 * @brief xinput_rotate
 *
 * Rotates the screen.
 *
 * @param dpy       Xrandr initialized display.
 * @param rotation  1,2,3 or 4. Each of these values represents a possible orientation
 *                  of the screen.
 */
void xinputRotate (Display *dpy, int rotation);

#endif
