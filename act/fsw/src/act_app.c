/*******************************************************************************
** File: act_app.c
**
** Purpose:
**   This file contains the source code for the Actuation App.
**
*******************************************************************************/

/*
**   Include Files:
*/

#include "act_app.h"
#include "act_perfids.h"
#include "act_msgids.h"
#include "act_msg.h"
#include "act_events.h"
#include "act_version.h"


/*
** global data
*/

boolean fo_u_state;
boolean fc_u_state;
boolean av_m_state;

boolean s2_state;
boolean s3_state;

boolean s3_po_state;
boolean s3_pr_state;

CFE_TIME_SysTime_t curtime;
CFE_TIME_SysTime_t switchtime;
CFE_TIME_SysTime_t timediff;
uint32 diffus;

int pi;


act_hk_tlm_t    ACT_HkTelemetryPkt;
CFE_SB_PipeId_t    ACT_CommandPipe;
CFE_SB_MsgPtr_t    ACTMsgPtr;

static CFE_EVS_BinFilter_t  ACT_EventFilters[] =
       {  /* Event ID    mask */
          {ACT_STARTUP_INF_EID,       0x0000},
          {ACT_COMMAND_ERR_EID,       0x0000},
          {ACT_COMMANDNOP_INF_EID,    0x0000},
          {ACT_COMMANDRST_INF_EID,    0x0000},
       };

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* ACT_AppMain() -- Application entry point and main process loop             */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void ACT_AppMain( void )
{
    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(ACT_PERF_ID);

    ACT_AppInit();

    /*
    ** ACT Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(ACT_PERF_ID);

        /*Pend on receipt of command packet -- timeout set to 5ms 
        so we don't have an infinite loop of infinite speed*/
        status = CFE_SB_RcvMsg(&ACTMsgPtr, ACT_CommandPipe, 5);
        
        CFE_ES_PerfLogEntry(ACT_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            ACT_ProcessCommandPacket();
        }

        curtime = CFE_TIME_GetTime();
        timediff = CFE_TIME_Subtract(curtime, switchtime);
        diffus = CFE_TIME_Sub2MicroSecs(timediff.Subseconds);

        /*switch s3's pins off after 250ms because it's a latching relay*/
        if(1 == s3_state)
        {

            if(((timediff.Seconds > 1) || (diffus > 250000)) && (1 == s3_po_state))
            {
                gpio_write(pi, S3_PIN_ON, PI_LOW);
                s3_po_state = 0;
                CFE_EVS_SendEvent(ACT_COMMAND_ENABLES3_EID, CFE_EVS_INFORMATION,
                    "ACT: State 3 enabled");
            }

        }
        else
        {

            if(((timediff.Seconds > 1) || (diffus > 250000)) && (1 == s3_pr_state))
            {
                gpio_write(pi, S3_PIN_RST, PI_LOW);
                s3_pr_state = 0;
                CFE_EVS_SendEvent(ACT_COMMAND_DISABLES3_EID, CFE_EVS_INFORMATION,
                    "ACT: State 3 disabled");
            }

        }




    }

    /*quit pigpio before exiting program*/
    pigpio_stop(pi);

    CFE_ES_ExitApp(RunStatus);

} /* End of ACT_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* ACT_AppInit() --  initialization                                           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void ACT_AppInit(void)
{
    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp() ;

    /*
    ** Register the events
    */ 
    CFE_EVS_Register(ACT_EventFilters,
                     sizeof(ACT_EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    CFE_SB_CreatePipe(&ACT_CommandPipe, ACT_PIPE_DEPTH,"ACT_CMD_PIPE");
    CFE_SB_Subscribe(ACT_CMD_MID, ACT_CommandPipe);
    CFE_SB_Subscribe(ACT_SEND_HK_MID, ACT_CommandPipe);

    ACT_ResetCounters();

    CFE_SB_InitMsg(&ACT_HkTelemetryPkt,
                   ACT_HK_TLM_MID,
                   ACT_HK_TLM_LNGTH, TRUE);

    /*Initializes the pigpio library, prints out a warning if it fails*/
    if ((pi=pigpio_start(0,0)) < 0)
    {
        CFE_EVS_SendEvent(ACT_STARTUP_INF_EID, CFE_EVS_ERROR, 
                "FAILED TO INITIALIZE PIGPIO! MAKE SURE TO RUN 'sudo pigpiod'");
    }
    else
    {
        CFE_EVS_SendEvent(ACT_STARTUP_INF_EID, CFE_EVS_INFORMATION, 
                "pigpio initialized successfully.");
        set_mode(pi, FO_U_PIN, PI_OUTPUT);
        set_mode(pi, FC_U_PIN, PI_OUTPUT);
        set_mode(pi, AV_M_PIN, PI_OUTPUT);
        set_mode(pi, S2_PIN, PI_OUTPUT);
        set_mode(pi, S3_PIN_ON, PI_OUTPUT);
        set_mode(pi, S3_PIN_RST, PI_OUTPUT);
    }

    /*initialize state variables*/
    fo_u_state = PI_LOW;
    fc_u_state = PI_LOW;
    av_m_state = PI_LOW;

    s2_state = 0;
    s3_state = 0;

    s3_po_state = 0;
    s3_pr_state = 0;


    CFE_EVS_SendEvent (ACT_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "Actuation App Initialized. Version %d.%d.%d.%d",
                ACT_MAJOR_VERSION,
                ACT_MINOR_VERSION, 
                ACT_REVISION, 
                ACT_MISSION_REV);
                
    /*initialize time*/ 
    curtime = CFE_TIME_GetTime();
    switchtime = curtime;

} /* End of ACT_AppInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACT_ProcessCommandPacket                                           */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the ACT       */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACT_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t  MsgId;

    MsgId = CFE_SB_GetMsgId(ACTMsgPtr);

    switch (MsgId)
    {
        case ACT_CMD_MID:
            ACT_ProcessGroundCommand();
            break;

        case ACT_SEND_HK_MID:
            ACT_ReportHousekeeping();
            break;

        default:
            ACT_HkTelemetryPkt.act_command_error_count++;
            CFE_EVS_SendEvent(ACT_COMMAND_ERR_EID,CFE_EVS_ERROR,
            "ACT: invalid command packet,MID = 0x%x", MsgId);
            break;
    }

    return;

} /* End ACT_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* ACT_ProcessGroundCommand() -- ACT ground commands                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void ACT_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(ACTMsgPtr);

    /* Process "known" ACT app ground commands */
    switch (CommandCode)
    {
        case ACT_NOOP_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            CFE_EVS_SendEvent(ACT_COMMANDNOP_INF_EID,CFE_EVS_INFORMATION,
            "ACT: NOOP command");
            break;

        case ACT_RESET_COUNTERS_CC:
            ACT_ResetCounters();
            break;

        case ACT_CLOSE_FO_U_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_CloseFOU();
            break;
        case ACT_OPEN_FC_U_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_OpenFCU();
            break;
        case ACT_OPEN_AV_M_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_OpenAVM();
            break;
        case ACT_OPEN_FO_U_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_OpenFOU();
            break;
        case ACT_CLOSE_FC_U_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_CloseFCU();
            break;
        case ACT_CLOSE_AV_M_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_CloseAVM();
            break;
        case ACT_ENABLES2_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_ENABLES2();
            break;
        case ACT_DISABLES2_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_DISABLES2();
            break;
        case ACT_ENABLES3_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_ENABLES3();
            break;
        case ACT_DISABLES3_CC:
            ACT_HkTelemetryPkt.act_command_count++;
            ACT_DISABLES3();
            

        /* default case already found during FC vs length test */
        default:
            break;
    }
    return;

} /* End of ACT_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACT_ReportHousekeeping                                              */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACT_ReportHousekeeping(void)
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &ACT_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *) &ACT_HkTelemetryPkt);
    return;

} /* End of ACT_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  ACT_ResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void ACT_ResetCounters(void)
{
    /* Status of commands processed by the Actuation App */
    ACT_HkTelemetryPkt.act_command_count       = 0;
    ACT_HkTelemetryPkt.act_command_error_count = 0;

    CFE_EVS_SendEvent(ACT_COMMANDRST_INF_EID, CFE_EVS_INFORMATION,
        "ACT: RESET command");
    return;

} /* End of ACT_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* ACT_VerifyCmdLength() -- Verify command packet length                      */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
boolean ACT_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
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

        CFE_EVS_SendEvent(ACT_LEN_ERR_EID, CFE_EVS_ERROR,
           "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
              MessageID, CommandCode, ActualLength, ExpectedLength);
        result = FALSE;
        ACT_HkTelemetryPkt.act_command_error_count++;
    }

    return(result);

} /* End of ACT_VerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Actuation functions -- move solenoids and switch power supplies           */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void ACT_CloseFOU(void)
{
    if(PI_LOW == fo_u_state)
    {
        fo_u_state = PI_HIGH;

        gpio_write(pi, FO_U_PIN, PI_HIGH);

        CFE_EVS_SendEvent(ACT_COMMAND_CLOSEFOU_EID, CFE_EVS_INFORMATION,
            "ACT: Closing FO_U");
    }
    
        return;
}

void ACT_OpenFCU(void)
{
    if(PI_LOW == fc_u_state)
    {
        fc_u_state = PI_HIGH;

        gpio_write(pi, FC_U_PIN, PI_HIGH);

        CFE_EVS_SendEvent(ACT_COMMAND_OPENFCU_EID, CFE_EVS_INFORMATION,
            "ACT: Opening FC_U");
    }
    
        return;
}

void ACT_OpenAVM(void)
{
    if(PI_LOW == av_m_state)
    {
        av_m_state = PI_HIGH;

        gpio_write(pi, AV_M_PIN, PI_HIGH);

        CFE_EVS_SendEvent(ACT_COMMAND_OPENAVM_EID, CFE_EVS_INFORMATION,
            "ACT: Opening AV_M");
    }
    
        return;
}

void ACT_OpenFOU(void)
{
    if(PI_HIGH == fo_u_state)
    {
        fo_u_state = PI_LOW;

        gpio_write(pi, FO_U_PIN, PI_LOW);

        CFE_EVS_SendEvent(ACT_COMMAND_OPENFOU_EID, CFE_EVS_INFORMATION,
            "ACT: Opening FO_U");
    }
    
        return;
}

void ACT_CloseFCU(void)
{
    if(PI_HIGH == fc_u_state)
    {
        fc_u_state = PI_LOW;

        gpio_write(pi, FC_U_PIN, PI_LOW);

        CFE_EVS_SendEvent(ACT_COMMAND_CLOSEFCU_EID, CFE_EVS_INFORMATION,
            "ACT: Closing FC_U");
    }
    
        return;
}

void ACT_CloseAVM(void)
{
    if(PI_HIGH == av_m_state)
    {
        av_m_state = PI_LOW;

        gpio_write(pi, AV_M_PIN, PI_LOW);

        CFE_EVS_SendEvent(ACT_COMMAND_CLOSEAVM_EID, CFE_EVS_INFORMATION,
            "ACT: Closing AV_M");
    }
    
        return;
}


void ACT_ENABLES2(void)
{
    if(0 == s2_state)
    {
        s2_state = 1;

        gpio_write(pi, S2_PIN, PI_HIGH);

        CFE_EVS_SendEvent(ACT_COMMAND_ENABLES2_EID, CFE_EVS_INFORMATION,
            "ACT: Enabling State 2");
    }
    
        return;
}
void ACT_DISABLES2(void)
{
    if(1 == s2_state)
    {
        s2_state = 0;

        gpio_write(pi, S2_PIN, PI_LOW);

        CFE_EVS_SendEvent(ACT_COMMAND_DISABLES2_EID, CFE_EVS_INFORMATION,
            "ACT: Disabling State 2");
    }
    
        return;
}

void ACT_ENABLES3(void)
{
    if(0 == s3_state)
    {
        s3_state = 1;

        gpio_write(pi, S3_PIN_ON, PI_HIGH);
        gpio_write(pi, S3_PIN_RST, PI_LOW);

        s3_po_state = 1;
        s3_pr_state = 0;

        switchtime = CFE_TIME_GetTime();
        CFE_EVS_SendEvent(ACT_COMMAND_ENABLES3_EID, CFE_EVS_INFORMATION,
            "ACT: Enabling State 3");
    }
    
    return;
}
void ACT_DISABLES3(void)
{
    if(1 == s3_state)
    {
        s3_state = 0;

        gpio_write(pi, S3_PIN_RST, PI_HIGH);
        gpio_write(pi, S3_PIN_ON, PI_LOW);

        s3_pr_state = 1;
        s3_po_state = 0;

        switchtime = CFE_TIME_GetTime();
        CFE_EVS_SendEvent(ACT_COMMAND_DISABLES3_EID, CFE_EVS_INFORMATION,
            "ACT: Disabling State 3");
    }

    return;
}