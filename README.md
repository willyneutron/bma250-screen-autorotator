#Screen autorotator based on BMA250 Bosch accelerometer

This script is designed to poll BMA250 accelerometer for position info.
Depending of this data, screen will be rotated using xrandr.

I hope this application will be useful to provide a more complete experience in some chinese
tablets based in Intel microprocessors when running Linux.

This program was developed for and tested in a Chuwi Hi 10 Pro, running Lubuntu 17.10 with
4.13.0-25 kernel installed.

## Compilation and installation
First of all dependencies must be installed:
```bash
sudo apt-get install libxrandr-dev i2c-tools
```
 
Then, it can be compiled and installed as normal:
```bash
autoreconf -vfi
./configure
make
sudo make install
```
Executing the aplication will need root permissions, because it needs to read from /dev/i2c-* file.

## Special configurations
In the case of Chiwi Hi10 Pro, BMA250 accelerometer is located in the bus /dev/i2c-2 listening in
address 0x18. In order to make easier the use of this software in other devices, you can configure
some parameters by defining some macros at compilation time:

```bash
    ./configure CFLAGS='-D<macro>=<value>'

```

 - ```BMA250_I2C_BUS```: This macro defines which /dev/i2c-%d file will be open. Default value es 2.
 - ```BMA250_I2C_ADDR```: This macro defines which address is assigned to the device inside i2c bus.
By default, 0x18 address is set.
 - ```POLLING_USECS```: Waiting time (in usecs) between accelerometer data reads. Default value is
set to 500 * 1000.
 - ```DEBUG```: You can compile with this flag and get some useful debug information in stdout.

## Installation in LXDE (Lubuntu)
In order to lauch autorrotator on startup, it can be included in ```/etc/lightdm/lightdm.conf.d/80-display-setup.conf```:

```
[SeatDefaults]
display-setup-script=autorotator_bg.sh
```

```autorotator_bg.sh``` is only a bash script that executes autorotator in the background to let lightdm complete
display initialization when called as display setup script. You can copy it in ```/usr/local/bin```. Do not forget
to set it as executable with ```chmod +x```:

```bash
#!/bin/bash
autorotator &
```

In some cases, LXDE DPI settings go crazy, and tipography renders really small. You can edit ```.Xresources```
in you home directory to override DPI settings:

```
Xft.dpi: 140
```

## References
If you want to use BMA250, this guys have very good examples and more information:

https://github.com/ControlEverythingCommunity/BMA250

I have to thank user falconer in askUbuntu for information about how to run this script at lightdm startup:

https://askubuntu.com/questions/408302/rotated-monitor-login-screen-needs-rotation

I also have to thank Mitch Lindgren by his post on how to set LXDE DPI settings:

http://blog.mlindgren.ca/entry/2015/02/21/configuring-dpi-in-lubuntu-slash-lxde/

If you are interested in more info about running Linux (Arch Linux) in a Chiwi Hi10 Pro, you can get more information on
Daniel Otero's repository:

https://github.com/danielotero/linux-on-hi10

## About

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
