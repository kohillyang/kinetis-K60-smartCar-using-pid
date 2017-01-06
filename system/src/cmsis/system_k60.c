/*
 * system_k60.c
 *
 *  Created on: 2017Äê1ÔÂ4ÈÕ
 *      Author: kohill
 */



#include "wdog.h"
void SystemInit (void){
	wdog_unlock();
	wdog_disable();
}
void SystemCoreClockUpdate (void){

}
