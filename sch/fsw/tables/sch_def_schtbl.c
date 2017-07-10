/*
** $Id: sch_def_schtbl.c 1.5 2015/03/01 14:02:05EST sstrege Exp  $
**
**  Copyright © 2007-2014 United States Government as represented by the 
**  Administrator of the National Aeronautics and Space Administration. 
**  All Other Rights Reserved.  
**
**  This software was created at NASA's Goddard Space Flight Center.
**  This software is governed by the NASA Open Source Agreement and may be 
**  used, distributed and modified only pursuant to the terms of that 
**  agreement.
**
** Purpose: Scheduler (SCH) default schedule table data
**
** Author: 
**
** Notes:
**
** $Log: sch_def_schtbl.c  $
** Revision 1.5 2015/03/01 14:02:05EST sstrege 
** Added copyright information
** Revision 1.4 2012/07/20 17:09:20EDT aschoeni 
** Fixed table compiler warning
** Revision 1.3 2011/07/21 14:52:44EDT aschoeni 
** removed default entries from table and replaced with unused entries
** Revision 1.2 2011/06/30 20:30:57EDT aschoeni 
** updated table header
** Revision 1.1 2009/03/27 00:32:26EDT dkobe 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/sch/fsw/tables/project.pj
*/

/*************************************************************************
**
** Include section
**
**************************************************************************/

#include "cfe.h"
#include "cfe_tbl_filedef.h"
#include "sch_platform_cfg.h"
#include "sch_msgdefs.h"
#include "sch_tbldefs.h"

/*************************************************************************
**
** Macro definitions
**
**************************************************************************/

/*
** Schedule Table "group" definitions
*/
#define SCH_GROUP_NONE         (0)

/* Define highest level multi-groups */
#define SCH_GROUP_CDH         (0x000001)                        /* All C&DH Messages        */
#define SCH_GROUP_GNC         (0x000002)                        /* All GNC  Messages        */

/* Define sub multi-groups           */
#define SCH_GROUP_CFS_HK      (  (0x000010) | SCH_GROUP_CDH)    /* CFS HK Messages          */
#define SCH_GROUP_CFE_HK      (  (0x000020) | SCH_GROUP_CDH)    /* cFE HK Messages          */
#define SCH_GROUP_GNC_HK      (  (0x000040) | SCH_GROUP_GNC)    /* GNC HK Messages          */

/* Define groups for messages that appear multiple times in Schedule */
#define SCH_GROUP_MD_WAKEUP   ((0x01000000) | SCH_GROUP_CDH)    /* MD Wakeup (aka Group #1) */

#define SCH_GROUP_SI       ((0x02000000) | SCH_GROUP_CDH) /*Sensor Input commands*/

/*************************************************************************
**
** Type definitions
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Exported data
**
**************************************************************************/

/*
** Default schedule table data
*/
SCH_ScheduleEntry_t SCH_DefaultScheduleTable[SCH_TABLE_ENTRIES] =
{

/*
** Structure definition...
**
**    uint8    EnableState  -- SCH_UNUSED, SCH_ENABLED, SCH_DISABLED
**    uint8    Type         -- 0 or SCH_ACTIVITY_SEND_MSG
**    uint16   Frequency    -- how many seconds between Activity execution
**    uint16   Remainder    -- seconds offset to perform Activity
**    uint16   MessageIndex -- Message Index into Message Definition table
**    uint32   GroupData    -- Group and Multi-Group membership definitions
*/


  /* slot #0 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #1 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #2 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #3 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  3,  2, SCH_GROUP_CFE_HK },   /* EVS HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #4 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #5 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #6 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #7 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #8 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #9 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  2,  7, SCH_GROUP_CFS_HK },  /* DS HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #10 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #11 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #12 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #13 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  3,  3, SCH_GROUP_CFE_HK },   /* SB HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #14 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  1,  8, SCH_GROUP_CFS_HK },   /* FM HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #15 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #16 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #17 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #18 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #19 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  2,  9, SCH_GROUP_CFS_HK },   /* HK HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #20 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #21 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #22 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #23 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  3,  4, SCH_GROUP_CFE_HK },   /* TIME HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #24 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #25 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #26 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 21, SCH_GROUP_NONE },  /* SC Wakeup */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #27 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #28 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #29 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_DISABLED, SCH_ACTIVITY_SEND_MSG,  4,  2, 11, SCH_GROUP_CFS_HK },  /* LC HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                        
  /* slot #30 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #31 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #32 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #33 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  3,  5, SCH_GROUP_CFE_HK },   /* TBL HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #34 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #35 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #36 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 23, SCH_GROUP_NONE },   /* DS Wakeup */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #37 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #38 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #39 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #40 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #41 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #42 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #43 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  3,  1, SCH_GROUP_CFE_HK },   /* ES HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #44 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  1, 14, SCH_GROUP_CFS_HK },   /* SC HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #45 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #46 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #47 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #48 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #49 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  2, 15, SCH_GROUP_CFS_HK },   /* SCH HK Request */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #50 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #51 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 22, SCH_GROUP_NONE },  /* LC Sample Action Points */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #52 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #53 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #54 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #55 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #56 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  1, 30, SCH_GROUP_NONE },   /* CI HK Request */
  {  SCH_ENABLED,  SCH_ACTIVITY_SEND_MSG,  4,  2, 31, SCH_GROUP_NONE },   /* TO HK Request */  
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #57 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #58 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #59 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #60 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #61 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #62 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #63 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #64 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #65 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #66 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #67 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #68 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #69 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #70 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #71 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #72 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #73 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #74 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #75 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #76 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #77 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #78 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #79 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #80 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #81 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #82 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #83 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #84 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #85 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #86 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #87 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #88 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #89 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #90 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #91 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  0, 16, SCH_GROUP_CFS_HK },   /* HK Send Combined HK '1' */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  1, 17, SCH_GROUP_CFS_HK },   /* HK Send Combined HK '2' */  
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #92 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  2, 18, SCH_GROUP_CFS_HK },   /* HK Send Combined HK '3' */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  4,  3, 19, SCH_GROUP_CFS_HK },   /* HK Send Combined HK '4' */  
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #93 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #94 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #95 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #96 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #97 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #98 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #99 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #100 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #101 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #102 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #103 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #104 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #105 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #106 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #107 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #108 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #109 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #110 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #111 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #112 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #113 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #114 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #115 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #116 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #117 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #118 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #119 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #120 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #121 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #122 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #123 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #124 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #125 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #126 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #127 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #128 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #129 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #130 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #131 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #132 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #133 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #134 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #135 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #136 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #137 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #138 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #139 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #140 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #141 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #142 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #143 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #144 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #145 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #146 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #147 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #148 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #149 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #150 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #151 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #152 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #153 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #154 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #155 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #156 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #157 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #158 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #159 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #160 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #161 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #162 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #163 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #164 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #165 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #166 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #167 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #168 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #169 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #170 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #171 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #172 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #173 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #174 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #175 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #176 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #177 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #178 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #179 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #180 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #181 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #182 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #183 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #184 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #185 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #186 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #187 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #188 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #189 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #190 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  
   /* slot #191 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                                              
  
   /* slot #192 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #193 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #194 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                         
   /* slot #195 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #196 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #197 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
   /* slot #198 */
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 32, SCH_GROUP_SI }, //gather sensor data                                       
  {  SCH_ENABLED, SCH_ACTIVITY_SEND_MSG,  1,  0, 33, SCH_GROUP_SI }, //transmit sensor data                                       
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
                                           
  /* slot #199 - Left Empty to allow Scheduler to Easily Resynchronize with 1 Hz */
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE},                                        
  {  SCH_UNUSED,   0,      0,  0, 0,  SCH_GROUP_NONE}                                       
};

/*
** Table file header
*/
CFE_TBL_FILEDEF(SCH_DefaultScheduleTable, SCH.SCHED_DEF, SCH schedule table, sch_def_schtbl.tbl)

/*************************************************************************
**
** File data
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Local function prototypes
**
**************************************************************************/

/*
** (none)
*/

/************************/
/*  End of File Comment */
/************************/

