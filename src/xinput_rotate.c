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

#include "xinput_rotate.h"

// Transformation matrices
// More information about these values here:
// https://wiki.ubuntu.com/X/InputCoordinateTransformation
float transformations_matrix [4][9] =
{
    { 1, 0, 0, 0, 1, 0, 0, 0, 1},
    { 0,-1, 1, 1, 0, 0, 0, 0, 1},
    {-1, 0, 1, 0,-1, 1, 0, 0, 1},
    { 0, 1, 0,-1, 0, 1, 0, 0, 1}
};

void xinputRotate (Display *dpy, int rotation)
{
    int             deviceId = 0;
    int             format;
    Atom            type;
    Atom            property;
    unsigned char   *old_data;
    unsigned long   act_nitems, bytes_after;

    union {
        unsigned char *c;
        int16_t *s;
        int32_t *l;
    } data;

    // Load transformation
    data.c = calloc(9, sizeof(int32_t));
    for (int i = 0; i < 9; i++)
    {
        *(float *)(data.l + i) = transformations_matrix[rotation][i];
    }

    #ifdef XDEVICE
        deviceId = XDEVICE;
    #endif

   if (dpy){
       if (deviceId){
           // Get property and its former value
           property = XInternAtom(dpy, "Coordinate Transformation Matrix", False);
           if (XIGetProperty(dpy, deviceId, property, 0, 0, False,
                             AnyPropertyType, &type, &format, &act_nitems,
                             &bytes_after, &old_data) == Success) {

               // Apply changes to transformation matrix
               XIChangeProperty(
                   dpy, deviceId, property,
                   type, format, PropModeReplace,
                   data.c, 9);

           }else{
               fprintf(stderr, "Failed to get coordinate transformation property\n");
           }
       }else{
           fprintf(stderr, "Error getting device info. Check XDEVICE.\n");
       }
   }else{
       fprintf(stderr, "Display is not valid.\n");
   }

   free(data.c);
}
