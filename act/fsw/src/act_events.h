/************************************************************************
** File:
**    ACT_events.h 
**
** Purpose: 
**  Define Actuation App Events IDs
**
** Notes:
**
**
*************************************************************************/
#ifndef _ACT_events_h_
#define _ACT_events_h_


#define ACT_RESERVED_EID              0
#define ACT_STARTUP_INF_EID           1 
#define ACT_COMMAND_ERR_EID           2
#define ACT_COMMANDNOP_INF_EID        3 
#define ACT_COMMANDRST_INF_EID        4
#define ACT_INVALID_MSGID_ERR_EID     5 
#define ACT_LEN_ERR_EID               6 

#define ACT_COMMAND_CLOSEFOU_EID      7
#define ACT_COMMAND_OPENFCU_EID       8
#define ACT_COMMAND_OPENAVM_EID       9

#define ACT_COMMAND_OPENFOU_EID       10
#define ACT_COMMAND_CLOSEFCU_EID      11
#define ACT_COMMAND_CLOSEAVM_EID      12

#define ACT_COMMAND_ENABLES2_EID      13
#define ACT_COMMAND_DISABLES2_EID     14

#define ACT_COMMAND_ENABLES3_EID      15
#define ACT_COMMAND_DISABLES3_EID     16


#endif /* _ACT_events_h_ */

/************************/
/*  End of File Comment */
/************************/
