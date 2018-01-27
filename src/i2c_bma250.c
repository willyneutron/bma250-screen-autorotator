/*
     Screen autorrotator based  on BMA250 Bosch accelerometer
     This module is in charge of communicating with BMA250 accelerometer using
     I2C protocol and smbus libraries.

     Do not use i2c-dev from linux kernel, use i2c-tools version instead:
     https://www.kernel.org/doc/Documentation/i2c/dev-interface

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

#include "i2c_bma250.h"

int I2C_setAddress(int i2cHandle, u8 deviceAddr) {
    if (ioctl(i2cHandle, I2C_SLAVE, deviceAddr) < 0) {
        fprintf(stderr, "Error while set I2C address 0x%x: %d error\n", deviceAddr, errno);
        return 0;
    }
    return 1;
}

u8 I2C_readByte(int i2cHandle, u8 deviceAddr,u8 regAddr) {
    u8 res;

    I2C_setAddress(i2cHandle, deviceAddr);

    res = i2c_smbus_read_byte_data(i2cHandle, regAddr);

    #ifdef DEBUG
        printf("[DEBUG] 0x%x @ 0x%x => 0x%x\n", deviceAddr, regAddr, res);
    #endif

    return res;
}

int I2C_writeByte(int i2cHandle, u8 deviceAddr, u8 regAddr, u8 value) {
    int res;

    I2C_setAddress(i2cHandle, deviceAddr);

    res = i2c_smbus_write_byte_data(i2cHandle, regAddr, value);
    if(res < 0) {
        fprintf(stderr, "Error writing 0x%x to 0x%x register on i2c bus\n",value, regAddr);
        return 0;
    }
    return 1;
}

int BMA250_init(int i2cHandle, u8 i2cAddress) {
    // Set range
    if (I2C_writeByte(i2cHandle, i2cAddress, 0x0F, 0x03)){
        // Set bandwidth
        if(I2C_writeByte(i2cHandle, i2cAddress, 0x10, 0x08)){
            return 1;
        }
    }
    return 0;
}

void BMA250_readAccel(int i2cHandle, u8 i2cAddress, int *x, int *y, int *z) {

    // Read data from 0x02
    // X-Axis LSB, X-Axis MSB, Y-Axis LSB, Y-Axis MSB, Z-Axis LSB, Z-Axis MSB
    u8 buffer[6];
    buffer[0] = I2C_readByte(i2cHandle, i2cAddress, 0x02);
    buffer[1] = I2C_readByte(i2cHandle, i2cAddress, 0x03);
    buffer[2] = I2C_readByte(i2cHandle, i2cAddress, 0x04);
    buffer[3] = I2C_readByte(i2cHandle, i2cAddress, 0x05);
    buffer[4] = I2C_readByte(i2cHandle, i2cAddress, 0x06);
    buffer[5] = I2C_readByte(i2cHandle, i2cAddress, 0x07);

    // Store the data. Order LSB and MSB bytes.
    *x = (buffer[1] * 256 + (buffer[0] & 0xC0)) / 64;
    if (*x > 511) *x -= 1024;

    *y = (buffer[3] * 256 + (buffer[2] & 0xC0)) / 64;
    if (*y > 511) *y -= 1024;

    *z = (buffer[5] * 256 + (buffer[4] & 0xC0)) / 64;
    if (*z > 511) *z -= 1024;

}
