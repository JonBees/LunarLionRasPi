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

#define SI_CLOSE_FO_U_CC 7
#define SI_OPEN_FC_U_CC 8
#define SI_OPEN_AV_M_CC 9

#define SI_OPEN_FO_U_CC 10
#define SI_CLOSE_FC_U_CC 11
#define SI_CLOSE_AV_M_CC 12

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
