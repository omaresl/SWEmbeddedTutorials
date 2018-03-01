/*
 * OS_Sched_Core.c
 *
 *  Created on: 02/11/2017
 *      Author: uidj2522
 */

/***********************************************
 * Includes
 ***********************************************/
#include "OS_Sched_Core.h"
#include "OS_Sched_Tasks.h"

/***********************************************
 * Variables
 ***********************************************/
static T_UBYTE rub_ExecuteTaskFlag = FALSE;
static T_UWORD ruw_TaskCounter = 0U;

/***********************************************
 * Constants
 ***********************************************/
const FCT_POINTER cpf_ScheduledTasks[sizeof(ruw_TaskCounter) * 8] = {
		app_OS_Sched_Task_1tk, //1tick
		NULL, //2ticks
		NULL, //4ticks
		NULL, //8ticks
		NULL, //16ticks
		NULL, //32ticks
		NULL, //64ticks
		NULL, //128ticks
		NULL, //256ticks
		NULL, //512ticks
		NULL, //1024ticks
		NULL, //2048ticks
		NULL, //4096ticks
		NULL, //8192ticks
		NULL, //16384ticks
		NULL  //32768ticks
};

T_UBYTE OS_Sched_Core_SelectTask(T_UWORD luw_TaskCounter);

/***********************************************
 * Code
 ***********************************************/

/***********************************************
 * Name: OS_Sched_Core_Loop
 * Description: TBD
 ***********************************************/
void OS_Sched_Core_Loop(void)
{
	/* Check if a tick was occurred */
	if(rub_PITAlarm == TRUE)
	{/* Tick occurred */
		/* Clear Tick Flag */
		rub_PITAlarm = FALSE;

		/* Manage Task Counter */
		/* Check if task counter reach its limits */
		if(ruw_TaskCounter >= OS_SCHED_CORE_MAX_TASK_COUNT)
		{
			/* Reset Counter */
			ruw_TaskCounter = OS_SCHED_CORE_MIN_TASK_COUNT;
		}
		else
		{
			/* Increase Task Counter */
			ruw_TaskCounter++;
		}

		/* Set Execution task */
		rub_ExecuteTaskFlag = TRUE;
	}
	else
	{
		if(rub_ExecuteTaskFlag == TRUE)
		{
			/* Execute Flag Clear */
			rub_ExecuteTaskFlag = FALSE;

			/* Task Index */
			T_UBYTE lub_TaskIndex;

			lub_TaskIndex = OS_Sched_Core_SelectTask(ruw_TaskCounter);

			/* Check If pointer is null */
			if(cpf_ScheduledTasks[lub_TaskIndex] == NULL)
			{
				/* Do nothing */
			}
			else
			{
				/* Task Execution */
				cpf_ScheduledTasks[OS_Sched_Core_SelectTask(ruw_TaskCounter)]();
			}
		}
		else
		{
			/* Do Nothing - Wait for task to be executed */
		}
	}
}

/***********************************************
 * Name: OS_Sched_Core_SelectTask
 * Description: TBD
 ***********************************************/
T_UBYTE OS_Sched_Core_SelectTask(T_UWORD luw_TaskCounter)
{
	T_UBYTE lub_TaskIndex;
	for(lub_TaskIndex = 0u;lub_TaskIndex < (sizeof(ruw_TaskCounter) * 8);lub_TaskIndex++)
	{
		if(((luw_TaskCounter >> lub_TaskIndex) & 0x0001u) == 0x0001u)
		{
			return lub_TaskIndex;
		}
		else
		{
			/* Do nothing */
		}
	}

	return 0x00;
}
