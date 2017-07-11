/*******************************************************************************
** File: ACT.h
**
** Purpose:
**   This file is main hdr file for the Actuation application.
**
**
*******************************************************************************/

#ifndef _ACT_h_
#define _ACT_h_

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

#define ACT_PIPE_DEPTH                     32

/************************************************************************
** Type Definitions
*************************************************************************/

/************************************************************************
** Pin Definitions
*************************************************************************/
#define FO_U_PIN 23
#define FC_U_PIN 24
#define AV_M_PIN 25

#define S2_PIN 26
#define S3_PIN_ON 27
#define S3_PIN_RST 28


/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (ACT_AppMain), these
**       functions are not called from any other source module.
*/
void ACT_AppMain(void);
void ACT_AppInit(void);
void ACT_ProcessCommandPacket(void);
void ACT_ProcessGroundCommand(void);
void ACT_ReportHousekeeping(void);
void ACT_ResetCounters(void);

void ACT_CloseFOU(void);
void ACT_OpenFCU(void);
void ACT_OpenAVM(void);
void ACT_OpenFOU(void);
void ACT_CloseFCU(void);
void ACT_CloseAVM(void);

void ACT_ENABLES2(void);
void ACT_DISABLES2(void);

void ACT_ENABLES3(void);
void ACT_DISABLES3(void);

boolean ACT_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

#endif /* _ACT_h_ */
