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
#include <pigpiod_if2.h>


/***********************************************************************/

#define SI_PIPE_DEPTH                     32

/************************************************************************
** Type Definitions
*************************************************************************/

/************************************************************************
** Pin Definitions
*************************************************************************/
#define FO_U_PIN 23
#define FC_U_PIN 24
#define AV_M_PIN 25


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

void SI_CloseFOU(void);
void SI_OpenFCU(void);
void SI_OpenAVM(void);
void SI_OpenFOU(void);
void SI_CloseFCU(void);
void SI_CloseAVM(void);



boolean SI_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

#endif /* _SI_h_ */