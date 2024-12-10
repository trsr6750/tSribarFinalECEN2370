/*
 * Scheduler.c
 *
 *  Created on: Sep 10, 2024
 *      Author: trevo
 */

#include <Scheduler.h>

static uint32_t scheduledEvents;

uint32_t getScheduledEvents(){
	return scheduledEvents;
}
void addSchedulerEvent(uint32_t event){
	scheduledEvents |= event;
}
void removeSchedulerEvent(uint32_t event){
	scheduledEvents &= ~event;
}

