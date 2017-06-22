/*******************************************************************************
** File: act_app.c
**
** Purpose:
**   This file contains the source code for the Sensor In App.
**
*******************************************************************************/

/*
**   Include Files:
*/

#include "SI_app.h"
#include "SI_perfids.h"
#include "SI_msgids.h"
#include "SI_msg.h"
#include "SI_events.h"
#include "SI_version.h"


/*
** global data
*/

boolean fo_u_state = PI_LOW;
boolean fc_u_state = PI_LOW;
boolean av_m_state = PI_LOW;

int pi;


SI_hk_tlm_t    SI_HkTelemetryPkt;
CFE_SB_PipeId_t    SI_CommandPipe;
CFE_SB_MsgPtr_t    SIMsgPtr;

static CFE_EVS_BinFilter_t  SI_EventFilters[] =
       {  /* Event ID    mask */
          {SI_STARTUP_INF_EID,       0x0000},
          {SI_COMMAND_ERR_EID,       0x0000},
          {SI_COMMANDNOP_INF_EID,    0x0000},
          {SI_COMMANDRST_INF_EID,    0x0000},
       };

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* SI_AppMain() -- Application entry point and main process loop              */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SI_AppMain( void )
{
    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(ACT_PERF_ID);

    SI_AppInit();

    /*
    ** SI Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(SI_PERF_ID);

        /*Pend on receipt of command packet -- timeout set to non-blocking*/
        status = CFE_SB_RcvMsg(&SIMsgPtr, SI_CommandPipe, CFE_SB_POLL);
        
        CFE_ES_PerfLogEntry(SI_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            SI_ProcessCommandPacket();
        }

        gpio_write(pi, FO_U_PIN, fo_u_state); 
        gpio_write(pi, FC_U_PIN, fc_u_state); 
        gpio_write(pi, AV_M_PIN, av_m_state); 
    }

    /*quit pigpio before exiting program*/
    pigpio_stop(pi);

    CFE_ES_ExitApp(RunStatus);

} /* End of SI_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SI_AppInit() --  initialization                                            */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void SI_AppInit(void)
{
    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp() ;

    /*
    ** Register the events
    */ 
    CFE_EVS_Register(SI_EventFilters,
                     sizeof(SI_EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    CFE_SB_CreatePipe(&SI_CommandPipe, SI_PIPE_DEPTH,"SI_CMD_PIPE");
    CFE_SB_Subscribe(SI_CMD_MID, SI_CommandPipe);
    CFE_SB_Subscribe(SI_SEND_HK_MID, SI_CommandPipe);

    SI_ResetCounters();

    CFE_SB_InitMsg(&SI_HkTelemetryPkt,
                   SI_HK_TLM_MID,
                   SI_HK_TLM_LNGTH, TRUE);

    /*Initializes the pigpio library, prints out a warning if it fails*/
    if ((pi=pigpio_start(0,0)) < 0)
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID, CFE_EVS_ERROR, 
                "FAILED TO INITIALIZE PIGPIO! MAKE SURE TO RUN 'sudo pigpiod'");
    }
    else
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID, CFE_EVS_INFORMATION, 
                "pigpio initialized successfully.");
        set_mode(pi, FO_U_PIN, PI_OUTPUT);
        set_mode(pi, FC_U_PIN, PI_OUTPUT);
        set_mode(pi, AV_M_PIN, PI_OUTPUT);
    }

    CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "Sensor In App Initialized. Version %d.%d.%d.%d",
                SI_MAJOR_VERSION,
                SI_MINOR_VERSION, 
                SI_REVISION, 
                SI_MISSION_REV);
				
} /* End of SI_AppInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SI_ProcessCommandPacket                                            */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the ACT       */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SI_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t  MsgId;

    MsgId = CFE_SB_GetMsgId(SIMsgPtr);

    switch (MsgId)
    {
        case SI_CMD_MID:
            SI_ProcessGroundCommand();
            break;

        case SI_SEND_HK_MID:
            SI_ReportHousekeeping();
            break;

        default:
            SI_HkTelemetryPkt.SI_command_error_count++;
            CFE_EVS_SendEvent(SI_COMMAND_ERR_EID,CFE_EVS_ERROR,
			"SI: invalid command packet,MID = 0x%x", MsgId);
            break;
    }

    return;

} /* End SI_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SI_ProcessGroundCommand() -- SI ground commands                            */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void SI_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(SIMsgPtr);

    /* Process "known" SI app ground commands */
    switch (CommandCode)
    {
        case SI_NOOP_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            CFE_EVS_SendEvent(SI_COMMANDNOP_INF_EID,CFE_EVS_INFORMATION,
			"SI: NOOP command");
            break;

        case SI_RESET_COUNTERS_CC:
            SI_ResetCounters();
            break;

        case SI_CLOSE_FO_U_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            SI_CloseFOU();
            break;
        case SI_OPEN_FC_U_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            SI_OpenFCU();
            break;
        case SI_OPEN_AV_M_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            SI_OpenAVM();
            break;
        case SI_OPEN_FO_U_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            SI_OpenFOU();
            break;
        case SI_CLOSE_FC_U_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            SI_CloseFCU();
            break;
        case SI_CLOSE_AV_M_CC:
            SI_HkTelemetryPkt.SI_command_count++;
            SI_CloseAVM();
            break;
            

        /* default case already found during FC vs length test */
        default:
            break;
    }
    return;

} /* End of SI_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SI_ReportHousekeeping                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SI_ReportHousekeeping(void)
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &SI_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &SI_HkTelemetryPkt);
    return;

} /* End of SI_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SI_ResetCounters                                                   */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SI_ResetCounters(void)
{
    /* Status of commands processed by the Sensor In App */
    SI_HkTelemetryPkt.SI_command_count       = 0;
    SI_HkTelemetryPkt.SI_command_error_count = 0;

    CFE_EVS_SendEvent(SI_COMMANDRST_INF_EID, CFE_EVS_INFORMATION,
		"SI: RESET command");
    return;

} /* End of SI_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SI_VerifyCmdLength() -- Verify command packet length                      */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
boolean SI_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{     
    boolean result = TRUE;

    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
              MessageID, CommandCode, ActualLength, ExpectedLength);
        result = FALSE;
        SI_HkTelemetryPkt.SI_command_error_count++;
    }

    return(result);

} /* End of SI_VerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SI_CloseFOU() -- Verify command packet length                             */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void SI_CloseFOU(void)
{
    fo_u_state = PI_HIGH;

    CFE_EVS_SendEvent(SI_COMMAND_CLOSEFOU_EID, CFE_EVS_INFORMATION,
            "SI: Closing FO_U");
        return;
}

void SI_OpenFCU(void)
{
    fc_u_state = PI_HIGH;

    CFE_EVS_SendEvent(SI_COMMAND_OPENFCU_EID, CFE_EVS_INFORMATION,
            "SI: Opening FC_U");
        return;
}

void SI_OpenAVM(void)
{
    av_m_state = PI_HIGH;

    CFE_EVS_SendEvent(SI_COMMAND_OPENAVM_EID, CFE_EVS_INFORMATION,
            "SI: Opening AV_M");
        return;
}

void SI_OpenFOU(void)
{
    fo_u_state = PI_LOW;

    CFE_EVS_SendEvent(SI_COMMAND_OPENFOU_EID, CFE_EVS_INFORMATION,
            "SI: Opening FO_U");
        return;
}

void SI_CloseFCU(void)
{
    fc_u_state = PI_LOW;

    CFE_EVS_SendEvent(SI_COMMAND_CLOSEFCU_EID, CFE_EVS_INFORMATION,
            "SI: Closing FC_U");
        return;
}

void SI_CloseAVM(void)
{
    av_m_state = PI_LOW;

    CFE_EVS_SendEvent(SI_COMMAND_CLOSEAVM_EID, CFE_EVS_INFORMATION,
            "SI: Closing AV_M");
        return;
}