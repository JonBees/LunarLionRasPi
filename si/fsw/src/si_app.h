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

/************************************************************************
** Type Definitions
*************************************************************************/

/************************************************************************
** Pin Definitions
*************************************************************************/
#define MUX_1 
#define MUX_2
#define MUX_3

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

void SI_AddTC(int TCNum);
void SI_AddPT(int PTNum);

void SI_ReadTCs(void);
void SI_ReadPTs(void);

void SI_ADC(HANDLE DAQ, uint8 *SPIRx);


boolean SI_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

#endif /* _SI_h_ */
