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

#include "si_app.h"
#include "si_perfids.h"
#include "si_msgids.h"
#include "si_msg.h"
#include "si_events.h"
#include "si_version.h"

/*
** global data
*/

SI_hk_tlm_t    SI_HkTelemetryPkt;
CFE_SB_PipeId_t    SI_CommandPipe;
CFE_SB_MsgPtr_t    SIMsgPtr;

int ReadingsArraySize;

//Handle and calibration info for the DAQ
HANDLE DAQ;
u6CalibrationInfo DAQCalibration;

//these keep track of how many (and which) TCs and PTs to check
int TCCount = 0;
int PTCount = 0;
SI_Sensor_t TCQueue[8];
SI_Sensor_t PTQueue[8];

uint8 SPITx[3];

SI_Sensor_t PT1, PT2, PT3, PT4, PT5, PT6, PT7, PT8, PT9, PT10, PT11, PT12, PT13, PT14, TC1, TC2, TC3, TC4, TC5, TC6, VBAT, CRNT;

char LogFilename[OS_MAX_PATH_LEN];

//zeromq pointers & such
void *outputcontext;
void *outputresponder;
int rc;

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

    CFE_ES_PerfLogEntry(SI_PERF_ID);

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

        SI_AddPT(PT1);
        SI_AddPT(PT2);
        SI_AddPT(PT3);
        SI_AddPT(PT4);
        SI_AddTC(TC1);
        SI_AddTC(TC2);

        if(ReadingsArraySize > 240)
        {
        int i = SI_WriteFile();
            if(i >= 0)
            {
            }
            else
            {
                CFE_EVS_SendEvent (SI_COMMAND_ERR_EID, CFE_EVS_ERROR,
                   "FAILED TO WRITE TO FILE: Error %d !", i);
            }
        }

        SI_ReadCurrent();
        SI_ReadVoltage();
        SI_ReadPTs();
        SI_ReadTCs();
    }
    
    closeUSBConnection(DAQ);
    CFE_ES_ExitApp(RunStatus);

} /* End of SI_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SI_AppInit() --  initialization                                            */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void SI_AppInit(void)
{
    CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "SI_AppInit Started");

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

    CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "SI_AppInit finished connecting to the software bus");

    SI_AssignValues();


    CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "SI_AppInit initialized sensorIDs");
    /*if(CFE_SUCCESS == SI_TableInit())
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID,CFE_EVS_INFORMATION,
            "Successfully initialized SI table.");
    }
    else
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID,CFE_EVS_ERROR,
            "FAILED TO INITIALIZE SI TABLE!");
    }*/

    ReadingsArraySize = 0;

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

    if((0 == getCalibrationInfo(DAQ, &DAQCalibration)) && (1 == isCalibrationInfoValid(&DAQCalibration)))
    {
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "DAQ Calibration Completed");
    }
    else
    {
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_ERROR,
               "DAQ CALIBRATION UNSUCCESSFUL!");
    }

    //create SPITx and fill it with 0s, since it doesn't matter what we try to send to the ADC
    for(int i=0; i<3; i++)
    {
        SPITx[i] = 0;
    }

    int i = SI_CreateFile();
    if(i >= 0)
    {
        sprintf(LogFilename, "/logfiles/log%d.csv", i+1);
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "Logfile Created: %s", LogFilename);
    }
    else
        CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_ERROR,
               "LOGFILE CREATION UNSUCCESSFUL!");



    CFE_EVS_SendEvent (SI_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "Sensor In App Initialized. Version %d.%d.%d.%d",
                SI_MAJOR_VERSION,
                SI_MINOR_VERSION, 
                SI_REVISION, 
                SI_MISSION_REV);
				
} /* End of SI_AppInit() */

void SI_AssignValues(void)
{
    //Mux 1
    PT1.pinNum = 0; PT1.linkedSensor = &PT8; strncpy(PT1.name, "PT1", 4);
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
}





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

/*int32 SI_TableInit(void)
{
    int32 status = CFE_SUCCESS;

    status = CFE_TBL_REGISTER(&ReadingsTableHandle, "ReadingsTable", 
        (sizeof(si_readings_table_entry_t) * SI_READINGS_TABLE_ENTRIES), 
        CFE_TBL_OPT_SINGL_BUFFER | CFE_TBL_OPT_DUMP_ONLY, NULL);
    if(status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID, CFE_EVS_ERROR,
            "Error registering ReadingsTable,RC=0x%08X",(unsigned int)status);
        return status;
    }

    status = CFE_TBL_Manage(ReadingsTableHandle)
    if(status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID, CFE_EVS_ERROR,
            "Error managing ReadingsTable,RC=0x%08X",(unsigned int)status);
        return status;
    }
    status = CFE_TBL_GetAddress((void *) (& ReadingsTablePointer), ReadingsTableHandle);
    if(status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SI_STARTUP_INF_EID, CFE_EVS_ERROR,
            "Error gettting the address of ReadingsTable,RC=0x%08X",(unsigned int)status);
        return status;
    }
    ReadingsArraySize = 0;
    return CFE_SUCCESS;
}*/


void SI_AddTC(SI_Sensor_t TC)
{
    if(TCCount < 6)
        TCQueue[TCCount] = TC;
    TCCount++;
}

void SI_AddPT(SI_Sensor_t PT)
{
    if(PTCount < 8)
    {
        boolean present = FALSE;
        for(int i=0; i<PTCount && (!present); i++)
        {
            if(PT.pinNum%8 == PTQueue[i].pinNum)
                present = TRUE;
        }

        if(!present)
        {
            PTQueue[PTCount] = PT;
            PTCount++;
        }
    }
}

void SI_ReadVoltage(void)
{
    SI_Reading_t *curEntry;
    double voltage;

    eAIN(DAQ, &DAQCalibration, VBAT.pinNum, 0, &voltage, LJ_rgBIP10V, 1, 1, 0, 0, 0);

    curEntry = &SI_Readings[ReadingsArraySize];

    (*curEntry).readingTime = CFE_TIME_GetTime();
    (*curEntry).sensorID = VBAT;
    (*curEntry).sensorValue = (int)voltage;

    ReadingsArraySize++;
}

void SI_ReadCurrent(void)
{
    SI_Reading_t *curEntry;
    double voltage;

    eAIN(DAQ, &DAQCalibration, CRNT.pinNum, 0, &voltage, LJ_rgBIP1V, 1, 1, 0, 0, 0);

    curEntry = &SI_Readings[ReadingsArraySize];

    (*curEntry).readingTime = CFE_TIME_GetTime();
    (*curEntry).sensorID = CRNT;
    (*curEntry).sensorValue = (int)voltage;

    ReadingsArraySize++;
}


void SI_ReadTCs(void)
{
    SI_Reading_t *curEntry;

    for(int i=0; i<TCCount; i++)
    {
        double voltage;
        //arguments 7 & 8 define resolution and settling factor. 
        //If TC values are crap, increase them.
        eAIN(DAQ, &DAQCalibration, TCQueue[i].pinNum, 0, &voltage, LJ_rgBIPP01V, 1, 1, 0, 0, 0);
        
        //get the first unfilled entry in the array.
        curEntry = &SI_Readings[ReadingsArraySize];
        //fill out that entry's data
        (*curEntry).readingTime = CFE_TIME_GetTime();
        (*curEntry).sensorID = TCQueue[i];
        (*curEntry).sensorValue = (int)voltage;

        ReadingsArraySize++;
    }
    TCCount = 0;
}

void SI_ReadPTs(void)
{
    SI_Reading_t *curEntry;

    int m1state, m2state, m3state;
    for(int i=0; i < PTCount; i++)
    {
        m1state = (PTQueue[i].pinNum)%2;
        m2state = ((PTQueue[i].pinNum)%4)/2;
        m3state = ((PTQueue[i].pinNum)%8)/4;

        uint8 sendDataBuff[12];

        sendDataBuff[0]=13; //IOType is BitDirWrite
        sendDataBuff[1]= MUX_1 + 128;//IONumber(bits 0-4) + Direction (bit 7)
        sendDataBuff[2]=11; //IOType is BitStateWrite
        sendDataBuff[3]= MUX_1 + (128*m1state);//IONumber(bits 0-4) + State (bit 7)

        sendDataBuff[4]=13;//IOType is BitDirWrite
        sendDataBuff[5]= MUX_2 + 128; //IONumber(bits 0-4) + Direction (bit 7)
        sendDataBuff[6]=11;//IOType is BitStateWrite
        sendDataBuff[7]= MUX_2 + (128*m2state);//IONumber(bits 0-4) + State (bit 7)

        sendDataBuff[8]=13;//IOType is BitDirWrite
        sendDataBuff[9]= MUX_3 + 128; //IONumber(bits 0-4) + Direction (bit 7)
        sendDataBuff[10]=11;//IOType is BitStateWrite
        sendDataBuff[11]= MUX_3 + (128*m3state);//IONumber(bits 0-4) + State (bit 7)
        

        uint8 errorcode, errorframe;
        long muxresult;
        muxresult = ehFeedback(DAQ, sendDataBuff, 12, &errorcode, &errorframe, NULL, 0);

        uint8 result1[3], result2[3];
        SI_ADC(DAQ, &result1[0], &result2[0]);

        //get the first unfilled entry in the table.
        curEntry = &SI_Readings[ReadingsArraySize];
        (*curEntry).readingTime = CFE_TIME_GetTime();
        (*curEntry).sensorID = PTQueue[i];
        //combine bytes 2 and 3 to get an int, then convert to voltage
        (*curEntry).sensorValue = (int)(result1[1]*256 + result1[2])*(5.044/65535);

        ReadingsArraySize++;

        curEntry = &SI_Readings[ReadingsArraySize];
        (*curEntry).readingTime = CFE_TIME_GetTime();
        (*curEntry).sensorID = *((SI_Sensor_t*)PTQueue[i].linkedSensor);
        (*curEntry).sensorValue = (int)(result2[1]*256 + result2[2])*(5.044/65535);

        ReadingsArraySize++;
    }
    PTCount = 0;
}

int SI_CreateFile(void)
{
    int32 FileDescriptor;
    boolean FileExists = 1;
    int i;
    char filename[OS_MAX_PATH_LEN];

    //iterate through all possible logfiles until we find one that doesn't exist
    for(i=0; (!FileExists) || (i<999); i++)
    {
        sprintf(filename, "/logfiles/log%d.csv", i+1);
        FileDescriptor = OS_open(filename, OS_READ_ONLY, 0);
        
        if(FileDescriptor >= 0)
            FileExists = 1;
        else
            FileExists = 0;

        OS_close(FileDescriptor);
    }
    //return an error if all 1000 logfiles exist somehow.
    if(FileExists)
        return -1;

    //actually create the file.
    FileDescriptor = OS_creat(filename, OS_WRITE_ONLY);

    //write a CSV header
    char header[34];
    sprintf(header, "readingTime,sensorID,sensorValue\n");
    FileDescriptor = OS_open(filename, OS_READ_WRITE, 0);
    OS_write(FileDescriptor, &header, sizeof(header));

    OS_close(FileDescriptor);

    //send back which logfile we've created
    return i;
}

int SI_WriteFile(void)
{
    int32 FileDescriptor;
    int32 Offset;
    uint32 BytesWritten;

    //create an array of chars with enough space to hold all of the text we're going to put into the file
    //20 chars each for seconds and microseconds (uint32), 4 for sensorID (char[4]), 5 for sensorValue (int)
    //plus three for commas and two for the \n character (which may just need 1? not taking chances though)
    char FileText[sizeof(SI_Readings)*54];
    uint32 DataLength = 0;

    for(int i=0; i<ReadingsArraySize; i++)
    {
        //create a char array for each line
        char EntryText[54];

        //pull the variables we're recording out of the readings array
        uint32 tSec = SI_Readings[i].readingTime.Seconds;
        uint32 tMicrosec = CFE_TIME_Sub2MicroSecs(SI_Readings[i].readingTime.Subseconds);
        int sVal = SI_Readings[i].sensorValue;

        //turn those variables into a string
        snprintf(EntryText, sizeof(EntryText), "%ld,%ld,%s,%d\n", tSec, tMicrosec, SI_Readings[i].sensorID.name, sVal);
        //add that string to the end of FileText
        strncat(FileText, EntryText, sizeof(EntryText));

        DataLength += strlen(EntryText);
    }

    //open the file, find our current spot, write, and close.
    FileDescriptor = OS_open(LogFilename, OS_READ_WRITE, 0);
    Offset = OS_lseek(FileDescriptor, 0, OS_SEEK_CUR);
    BytesWritten = OS_write(FileDescriptor, &FileText, DataLength);
    OS_close(FileDescriptor);
    if(BytesWritten != DataLength)
        return -1;
    else
        return BytesWritten;
}

void SI_ADC(HANDLE DAQ, uint8 *SPIRx1, uint8 *SPIRx2)
{

    //(Device handle, CSPin, CLKPin, MISOPin, MOSIPin, SIOpts, NumSPIBytes, *SPITx, *SPIRx)
    int errorcode1;
    errorcode1 = SPI(DAQ, 0, 1, 2, 3, (uint8)0x80, 3, &SPITx[0], SPIRx1);
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
    errorcode2 = SPI(DAQ, 0, 1, 2, 3, (uint8)0x80, 3, &SPITx[0], SPIRx2);
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
