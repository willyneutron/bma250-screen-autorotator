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

#include "xrandr_rotate.h"

int initXrandrData(XrandrData *data){
    // Open default display
    data->dpy = XOpenDisplay (NULL);

    if (data->dpy){
        // Get screen info. Store it in order to do this init only once
        data->screen = DefaultScreen(data->dpy);
        data->root = RootWindow (data->dpy, data->screen);
        data->sc = XRRGetScreenInfo (data->dpy, data->root);
        if (data->sc){
            return 1;
        }else{
            fprintf(stderr, "Error getting screen info\n");
        }
    }else{
        fprintf(stderr, "Error getting default display\n");
    }

    return 0;
}


void rotate (XrandrData *data, int rotation)
{
    Status s;
    time_t rawtime;
    SizeID current_size;
    Rotation current_rotation;

    // Prepare rotation code and get current rotation
    rotation = 1 << rotation;
    current_size = XRRConfigCurrentConfiguration (data->sc, &current_rotation);

    // Apply new rotation
    time ( &rawtime );
    s = XRRSetScreenConfig (data->dpy, data->sc, data->root,
                            current_size, rotation, rawtime);
    if (s == RRSetConfigFailed){
        fprintf(stderr, "Error applying new screen config\n");
    }
}
