/*******************************************************************************
** File: u6spi.h
**
** Purpose:
**   This file adds SPI support for the LabJack U6 using the Mac/Linux Exodriver
**
** Author: 
**   Jonathan Bees
**
*******************************************************************************/

#ifndef _u6spi_h_
#define _u6spi_h_

#include <sys/time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "u6.h"
#include "labjackusb.h"


int SPI(HANDLE hDevice, 
		uint8 CSPin, 
		uint8 CLKPin, 
		uint8 MISOPin, 
		uint8 MOSIPin, 
		uint8 SPIOpts, 
		uint8 NumSPIBytes, 
		uint8 *SPITx, 
		uint8 *SPIRx);
//handles SPI communication with the U6
//based on the I2C implementation in u6.c
