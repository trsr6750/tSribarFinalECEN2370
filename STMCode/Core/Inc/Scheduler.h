/*
 * Scheduler.h
 *
 *  Created on: Sep 10, 2024
 *      Author: trevo
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

#define DELAY_EVENT (0x1)
#define PULL_MOVE_RIGHT_EVENT (0x1 << 1)
#define PULL_MOVE_LEFT_EVENT (0x1 << 2)
#define PULL_ROTATE_PLUS_EVENT (0x1 << 3)
#define PULL_ROTATE_MINUS_EVENT (0x1 << 4)

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t);
void removeSchedulerEvent(uint32_t);

#endif /* SCHEDULER_H_ */
