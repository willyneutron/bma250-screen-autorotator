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

#ifndef I2C_BMA250_H
#define I2C_BMA250_H

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>

// Useful types
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;

/**
 * @brief I2C_setAddress
 *
 * Uses ioctl to set up i2c connection (as slave). This function is used inside read and
 * write functions.
 *
 * @param i2cHandle
 * @param deviceAddr
 * @return
 */
int I2C_setAddress(int i2cHandle, u8 deviceAddr);

/**
 * @brief I2C_readByte
 *
 * Read a byte from I2C device.
 *
 * @param i2cHandle     Handle for i2c dev file
 * @param deviceAddr    Device address
 * @param regAddr       Register address to read from
 * @return              Readed byte
 */
u8 I2C_readByte(int i2cHandle, u8 deviceAddr,u8 regAddr);

/**
 * @brief I2C_writeByte
 *
 * Write a byte in a register of a I2C device.
 *
 * @param i2cHandle     Handle for i2c dev file
 * @param deviceAddr    Device address
 * @param regAddr       Register to write the byte into
 * @param value         Byte to write
 * @return              1 if no error encountered. 0 otherwhise
 */
int I2C_writeByte(int i2cHandle, u8 deviceAddr, u8 regAddr, u8 value);

/**
 * @brief BMA250_init
 *
 * Init bma250 device. Set range and bandwith of device.
 *
 * @param i2cHandle     Handle for i2c dev file
 * @param i2cAddress    Device address
 * @return
 */
int BMA250_init(int i2cHandle, u8 i2cAddress);

/**
 * @brief BMA250_readAccel
 *
 * Read accelerometer data.
 *
 * @param i2cHandle     Handle for i2c dev file
 * @param i2cAddress    Device address
 * @param x             Reference to store x axis data
 * @param y             Reference to store y axis data
 * @param z             Reference to store z axis data
 */
void BMA250_readAccel(int i2cHandle, u8 i2cAddress, int *x, int *y, int *z);

#endif

