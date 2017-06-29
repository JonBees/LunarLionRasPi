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



SI_hk_tlm_t    SI_HkTelemetryPkt;
CFE_SB_PipeId_t    SI_CommandPipe;
CFE_SB_MsgPtr_t    SIMsgPtr;

//Handle and calibration info for the DAQ
HANDLE DAQ;
u6CalibrationInfo DAQCalibration;

//these keep track of how many (and which) TCs and PTs to check
int TCCount = 0;
int PTCount = 0;
int TCQueue[6];
int PTQueue[8];

int temps[6];
int pressures[16];


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
    }

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

    DAQ = openUSBConnection(-1);
    if(NULL != DAQ){
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "DAQ Connected Successfully");
    }
    else
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID,CFE_EVS_ERROR,
            "NO DAQ CONNECTED! Make sure it's pluggged in and restart the SI app");
    }

    if((0 == getCalibrationInfo(DAQ, &DAQCalibration)) && 1 == isCalibrationInfoValid(&DAQCalibration))
    {
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "DAQ Calibration Completed");
    }
    else
    {
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "DAQ CALIBRATION UNSUCCESSFUL!");
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

void SI_AddTC(int TCPin)
{
    if(TCCount < 6)
        TCQueue[TCCount] = TCPin;
    TCCount++;
}
void SI_AddPT(int PTPin)
{
    if(PTCount < 8)
    {
        boolean present = FALSE;
        for(int i=0; i<PTCount && (!present); i++)
        {
            if(PTPin%8 == PTQueue[i])
                present = TRUE;
        }

        if(!present)
        {
            PTQueue[PTCount] = PTPin;
            PTCount++;
        }
    }
}

void SI_ReadTCs(void)
{
    for(int i=0; i<TCCount; i++)
    {
        double voltage;
        //arguments 7 & 8 define resolution and settling factor. 
        //If TC values are crap, increase them.
        eAIN(DAQ, &DAQCalibration, TCQueue[i], 0, &voltage, LJ_rgBIPP01V, 1, 1, 0, 0, 0);
        temps[i] = voltage;
    }
}
void SI_ReadPTs(void)
{
    int m1state, m2state, m3state;
    for(int i=0; i< PTCount; i++)
    {
        m1state = PTQueue[i]%2;
        m2state = (PTQueue[i]%4)/2;
        m3state = (PTQueue[i]%8)/4;

        uint8 sendDataBuff[12];

        sendDataBuff[0]=13; //IOType is BitDirWrite
        sendDataBuff[1]= MUX_1 + 128;//IONumber(bits 0-4) + Direction (bit 7)
        sendDataBuff[2]=11; //IOType is BitStateWrite
        sendDataBuff[3]= MUX_1 + (128*m1state)//IONumber(bits 0-4) + State (bit 7)

        sendDataBuff[4]=13//IOType is BitDirWrite
        sendDataBuff[5]= MUX_2 + 128; //IONumber(bits 0-4) + Direction (bit 7)
        sendDataBuff[6]=11//IOType is BitStateWrite
        sendDataBuff[7]= MUX_2 + (128*m2state)//IONumber(bits 0-4) + State (bit 7)

        sendDataBuff[8]=13//IOType is BitDirWrite
        sendDataBuff[9]= MUX_3 + 128; //IONumber(bits 0-4) + Direction (bit 7)
        sendDataBuff[10]=11//IOType is BitStateWrite
        sendDataBuff[11]= MUX_3 + (128*m3state)//IONumber(bits 0-4) + State (bit 7)
        

        uint8 errorcode, errorframe;
        long muxresult;
        muxresult = ehFeedback(DAQ, sendDataBuff, 12, &errorcode, &errorframe, NULL, 0);

        uint8 result1[3], result2[3];
        SI_ADC(DAQ, &result1, &result2);
        //combine bytes 2 and 3 to get an int, then convert to voltage
        pressures[i] = (result1[1]*256 + result1[2])*(5.044/65535);
        pressures[i+8] = (result2[1]*256 + result2[2])*(5.044/65535);
        
    }
}







void SI_ADC(HANDLE DAQ, uint8 *SPIRx1, *SPIRx2)
{
    //create SPITx and fill it with 0s, since it doesn't matter what we try to send to the ADC
    uint8 *SPITx = (uint8*)malloc(sizeof(uint8)*3);
    for(int i=0; i<3; i++)
    {
        SPITx[i] = 0;
    }

    //(Device handle, CSPin, CLKPin, MISOPin, MOSIPin, SIOpts, NumSPIBytes, *SPITx, *SPIRx)
    int errorcode1;
    errorcode1 = SPI(DAQ, 0, 1, 2, 3, (uint8)0x80, 3, *SPITx, *SPIRx1);
    switch(errorcode1){
        case 0: //No error
            break;
        case -1:
            CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : write failed");
            break;
        case -2:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : did not write all of the buffer");
            break;
        case -3:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : read failed");
            break;
        case -4:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : did not write all of the buffer"); 
            break;
        case -5:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : read buffer has bad checksum"); 
            break;
        case -6:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : read buffer has incorrect command byte");
            break;
        case -7: 
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : read buffer has incorrect number of data words");
            break;
        case -8:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 Error : read buffer has incorrect extended command number");
            break;
        case -9: 
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 1 error : read buffer has bad checksum16");
            break;
        default:
            CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "Unknown SPI 1 Error");
    }


    int errorcode2;
    errorcode2 = SPI(DAQ, 0, 1, 2, 3, (uint8)0x80, 3, *SPITx, *SPIRx2);
    switch(errorcode2){
        case 0: //No error
            break;
        case -1:
            CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : write failed");
            break;
        case -2:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : did not write all of the buffer");
            break;
        case -3:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : read failed");
            break;
        case -4:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : did not write all of the buffer"); 
            break;
        case -5:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : read buffer has bad checksum"); 
            break;
        case -6:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : read buffer has incorrect command byte");
            break;
        case -7: 
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : read buffer has incorrect number of data words");
            break;
        case -8:
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 Error : read buffer has incorrect extended command number");
            break;
        case -9: 
        CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "SPI 2 error : read buffer has bad checksum16");
            break;
        default:
            CFE_EVS_SendEvent(SI_LEN_ERR_EID, CFE_EVS_ERROR,
           "Unknown SPI 2 Error");
    }
}
