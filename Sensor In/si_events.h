/************************************************************************
** File:
**    SI_events.h 
**
** Purpose: 
**  Define Sensor In App Events IDs
**
** Notes:
**
**
*************************************************************************/
#ifndef _SI_events_h_
#define _SI_events_h_


#define SI_RESERVED_EID              0
#define SI_STARTUP_INF_EID           1 
#define SI_COMMAND_ERR_EID           2
#define SI_COMMANDNOP_INF_EID        3 
#define SI_COMMANDRST_INF_EID        4
#define SI_INVALID_MSGID_ERR_EID     5 
#define SI_LEN_ERR_EID               6 

#define SI_COMMAND_CLOSEFOU_EID      7
#define SI_COMMAND_OPENFCU_EID       8
#define SI_COMMAND_OPENAVM_EID       9

#define SI_COMMAND_OPENFOU_EID       10
#define SI_COMMAND_CLOSEFCU_EID      11
#define SI_COMMAND_CLOSEAVM_EID      12

#endif /* _SI_events_h_ */

/************************/
/*  End of File Comment */
/************************/
