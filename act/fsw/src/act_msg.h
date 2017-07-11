/*******************************************************************************
** File:
**   ACT_msg.h 
**
** Purpose: 
**  Define Actuation App Messages and info
**
** Notes:
**
**
*******************************************************************************/
#ifndef _act_msg_h_
#define _act_msg_h_

/*
** Actuation App command codes
*/
#define ACT_NOOP_CC                 0
#define ACT_RESET_COUNTERS_CC       1

#define ACT_CLOSE_FO_U_CC 7
#define ACT_OPEN_FC_U_CC 8
#define ACT_OPEN_AV_M_CC 9

#define ACT_OPEN_FO_U_CC 10
#define ACT_CLOSE_FC_U_CC 11
#define ACT_CLOSE_AV_M_CC 12

#define ACT_ENABLES2_CC      13
#define ACT_DISABLES2_CC     14

#define ACT_ENABLES3_CC      15
#define ACT_DISABLES3_CC     16

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
   uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];

} ACT_NoArgsCmd_t;

/*************************************************************************/
/*
** Type definition (Actuation App housekeeping)
*/
typedef struct 
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              act_command_error_count;
    uint8              act_command_count;
    uint8              spare[2];

}   OS_PACK act_hk_tlm_t  ;

#define ACT_HK_TLM_LNGTH   sizeof ( act_hk_tlm_t )

#endif /* _ACT_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
