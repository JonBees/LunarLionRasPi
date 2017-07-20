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


SI_Sensor_t PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12, PT13, PT14, TC1, TC2, TC3, TC4, TC5, TC6, VBAT, CRNT;

/*SI_Sensor_t PT2;
SI_Sensor_t PT3;
SI_Sensor_t PT4;
SI_Sensor_t PT5;
SI_Sensor_t PT6;
SI_Sensor_t PT7;
SI_Sensor_t PT8;
SI_Sensor_t PT9;
SI_Sensor_t PT10;
SI_Sensor_t PT11;
SI_Sensor_t PT12;
SI_Sensor_t PT13;
SI_Sensor_t PT14;
SI_Sensor_t TC1;
SI_Sensor_t TC2;
SI_Sensor_t TC3;
SI_Sensor_t TC4;
SI_Sensor_t TC5;
SI_Sensor_t TC6;
SI_Sensor_t VBAT;
SI_Sensor_t CRNT;*/





/*
//Mux 1
PT1.pinuNm = 0; PT1.linkedSensor = &PT8; strncpy(PT1.name, "PT1", 4);
PT2.pinNum = 1; PT2.linkedSensor = &PT9; strncpy(PT2.name, "PT2", 4);
PT3.pinNum = 2; PT3.linkedSensor = &PT10; strncpy(PT3.name, "PT3", 4);
PT4.pinNum = 3; PT4.linkedSensor = &PT11; strncpy(PT4.name, "PT4", 4);
PT5.pinNum = 4; PT5.linkedSensor = &PT12; strncpy(PT5.name, "PT5", 4);
PT6.pinNum = 5; PT6.linkedSensor = &PT13; strncpy(PT6.name, "PT6", 4);
PT7.pinNum = 6; PT7.linkedSensor = &PT14; strncpy(PT7.name, "PT7", 4);
///Mux 2
PT8.pinNum = 7; PT8.linkedSensor = &PT1; strncpy(PT8.name, "PT8", 4);
PT9.pinNum = 8; PT9.linkedSensor = &PT2; strncpy(PT9.name, "PT9", 4);
PT10.pinNum = 9; PT10.linkedSensor = &PT3; strncpy(PT10.name, "PT10", 4);
PT11.pinNum = 10; PT11.linkedSensor = &PT4; strncpy(PT11.name, "PT11", 4);
PT12.pinNum = 11; PT12.linkedSensor = &PT5; strncpy(PT12.name, "PT12", 4);
PT13.pinNum = 12; PT13.linkedSensor = &PT6; strncpy(PT13.name, "PT13", 4);
PT14.pinNum = 13; PT14.linkedSensor = &PT7; strncpy(PT14.name, "PT14", 4);
//Analog in
TC1.pinNum = 1; strncpy(TC1.name, "TC1", 4);
TC2.pinNum = 1; strncpy(TC2.name, "TC2", 4);
TC3.pinNum = 1; strncpy(TC3.name, "TC3", 4);
TC4.pinNum = 1; strncpy(TC4.name, "TC4", 4);
TC5.pinNum = 1; strncpy(TC5.name, "TC5", 4);
TC6.pinNum = 1; strncpy(TC6.name, "TC6", 4);
VBAT.pinNum = 0; strncpy(VBAT.name, "VBAT", 4);//AIN0
CRNT.pinNum = 1; strncpy(CRNT.name, "CRNT", 4);//AIN1
*/

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
