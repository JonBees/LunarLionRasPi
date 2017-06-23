/*******************************************************************************
** File:
**   SI_msg.h 
**
** Purpose: 
**  Define Sensor In App Messages and info
**
** Notes:
**
**
*******************************************************************************/
#ifndef _SI_msg_h_
#define _SI_msg_h_

/*
** Sensor In App command codes
*/
#define SI_NOOP_CC                 0
#define SI_RESET_COUNTERS_CC       1

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];

} SI_NoArgsCmd_t;

/*************************************************************************/
/*
** Type definition (Sensor In App housekeeping)
*/
typedef struct 
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              SI_command_error_count;
    uint8              SI_command_count;
    uint8              spare[2];

}   OS_PACK SI_hk_tlm_t  ;

#define SI_HK_TLM_LNGTH   sizeof ( SI_hk_tlm_t )

#endif /* _SI_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
