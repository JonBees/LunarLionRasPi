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

#define PT1 1
#define PT2 2
#define PT3 3
#define PT4 4
#define PT5 5
#define PT6 6
#define PT7 7
#define PT8 8
#define PT9 9
#define PT10 10
#define PT11 11
#define PT12 12
#define PT13 13
#define PT14 14


#define TC1 15
#define TC2 16
#define TC3 17
#define TC4 18
#define TC5 19
#define TC6 20

#define VBAT 21
#define CRNT 22

typedef struct 
{
	int32 FileHandle;
	uint32 FileSize;
	char FileName[OS_MAX_PATH_LEN];
}SI_FileInfo_t;

typedef struct
{
	CFE_TIME_SysTime_t readingTime; //64 bits
	SI_Sensor_t sensorID; //8 bits
	int sensorValue; //16 bits
}SI_Reading_t;

typedef struct
{
	char name[4];
	uint8 pinNum;
	SI_Sensor_t* linkedSensor;
}SI_Sensor_t;

SI_Sensor_t PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12, PT13, PT14, TC1, TC2, TC3, TC4, TC5, TC6, VBAT, CRNT;
PT1.pinNum = 0; PT1.linkedSensor = &PT8; strncpy(PT1.name, "PT1", 4);
PT2.pinNum = 1; PT2.linkedSensor = &PT9; strncpy(PT1.name, "PT2", 4);
PT3.pinNum = 2; PT3.linkedSensor = &PT10; strncpy(PT1.name, "PT3", 4);
PT4.pinNum = 3; PT4.linkedSensor = &PT11; strncpy(PT1.name, "PT4", 4);
PT5.pinNum = 4; PT5.linkedSensor = &PT12; strncpy(PT1.name, "PT5", 4);
PT6.pinNum = 5; PT6.linkedSensor = &PT13; strncpy(PT1.name, "PT6", 4);
PT7.pinNum = 6; PT7.linkedSensor = &PT14; strncpy(PT1.name, "PT7", 4);
PT8.pinNum = 7; PT8.linkedSensor = &PT1; strncpy(PT1.name, "PT8", 4);
PT9.pinNum = 8; PT9.linkedSensor = &PT2; strncpy(PT1.name, "PT9", 4);
PT10.pinNum = 9; PT10.linkedSensor = &PT3; strncpy(PT1.name, "PT10", 4);
PT11.pinNum = 10; PT11.linkedSensor = &PT4; strncpy(PT1.name, "PT11", 4);
PT12.pinNum = 11; PT12.linkedSensor = &PT5; strncpy(PT1.name, "PT12", 4);
PT13.pinNum = 12; PT13.linkedSensor = &PT6; strncpy(PT1.name, "PT13", 4);
PT14.pinNum = 13; PT14.linkedSensor = &PT7; strncpy(PT1.name, "PT14", 4);
TC1.pinNum = 1; strncpy(PT1.name, "TC1", 4);
TC2.pinNum = 1; strncpy(PT1.name, "TC2", 4);
TC3.pinNum = 1; strncpy(PT1.name, "TC3", 4);
TC4.pinNum = 1; strncpy(PT1.name, "TC4", 4);
TC5.pinNum = 1; strncpy(PT1.name, "TC5", 4);
TC6.pinNum = 1; strncpy(PT1.name, "TC6", 4);
VBAT.pinNum = 1; strncpy(PT1.name, "VBAT", 4);
CRNT.pinNum = 1; strncpy(PT1.name, "CRNT", 4);


/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (SI_AppMain), these
**       functions are not called from any other source module.
*/
void SI_AppMain(void);
void SI_AppInit(void);
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


void SI_ADC(HANDLE DAQ, uint8 *SPIRx);




//260 elements means at least 10 loops. Should save to file at 20hz if running at 200.
SI_Reading_t SI_Readings[265];




#endif /* _SI_h_ */
