/*
 * OS_Sched_Core.h
 *
 *  Created on: 02/11/2017
 *      Author: uidj2522
 */

#ifndef OS_SCHED_CORE_H_
#define OS_SCHED_CORE_H_

/***********************************************
 * Includes
 ***********************************************/
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "app_PIT.h"

/***********************************************
 * Definitions
 ***********************************************/
#define OS_SCHED_CORE_MAX_TASK_COUNT	((T_UWORD)0xFFFFU)
#define OS_SCHED_CORE_MIN_TASK_COUNT	((T_UWORD)0x0001U)

/***********************************************
 * Prototypes
 ***********************************************/
extern void app_NULL(void);

#endif /* OS_SCHED_CORE_H_ */
