/*******************************************************************************
** File: SI.h
**
** Purpose:
**   This file is main hdr file for the Sensor In application.
**
**
*******************************************************************************/

#ifndef _SI_h_
#define _SI_h_

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <zmq.h>

#include "u6.h"
#include "u6spi.h"

/***********************************************************************/

#define SI_PIPE_DEPTH                     32

//#define SI_READINGS_TABLE_ENTRIES         240

/************************************************************************
** Type Definitions
*************************************************************************/

/************************************************************************
** Pin Definitions
*************************************************************************/
#define MUX_1 16
#define MUX_2 17
#define MUX_3 18

/************************************************************************
** Sensor ID Definitions
*************************************************************************/

typedef struct 
{
	int32 FileHandle;
	uint32 FileSize;
	char FileName[OS_MAX_PATH_LEN];
}SI_FileInfo_t;

typedef struct
{
	char name[4];
	uint8 pinNum;
	void *linkedSensor;
}SI_Sensor_t;

typedef struct
{
	CFE_TIME_SysTime_t readingTime; //64 bits
	SI_Sensor_t sensorID; //24 bits
	int sensorValue; //16 bits
}SI_Reading_t;


/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (SI_AppMain), these
**       functions are not called from any other source module.
*/
void SI_AppMain(void);
void SI_AppInit(void);

void SI_AssignValues(void);

void SI_ProcessCommandPacket(void);
void SI_ProcessGroundCommand(void);
void SI_ReportHousekeeping(void);
void SI_ResetCounters(void);

boolean SI_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

void SI_AddTC(SI_Sensor_t TC);
void SI_AddPT(SI_Sensor_t PT);

void SI_ReadVoltage(void);
void SI_ReadCurrent(void);

void SI_ReadTCs(void);
void SI_ReadPTs(void);

int SI_CreateFile(void);
int SI_WriteFile(void);


void SI_ADC(HANDLE DAQ, uint8 *SPIRx1, uint8 *SPIRx2);

//260 elements means at least 10 loops. Should save to file at 20hz if running at 200.
SI_Reading_t SI_Readings[265];

#endif /* _SI_h_ */
