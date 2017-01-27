/*
 * pin_description.h
 *
 *  Created on: Oct 24, 2016
 *      Author: Tarolrr
 */

#ifndef PIN_DESCRIPTION_H_
#define PIN_DESCRIPTION_H_

#include "external_Decl.h"
#include "stm32f1xx_hal.h"

struct {
	GPIO_TypeDef * const port;
	uint16_t const pin;
	uint32_t lastEvent;			//время последнего изменения состояния. HAL_GetTick
	GPIO_PinState lastState;	//последнее состояние
} typedef PinDescription;

#define GPIO_PIN_SET(pinDesc) {HAL_GPIO_WritePin((pinDesc)->port,(pinDesc)->pin,GPIO_PIN_SET); (pinDesc)->lastState = GPIO_PIN_SET; (pinDesc)->lastEvent = HAL_GetTick();}
#define GPIO_PIN_RESET(pinDesc) {HAL_GPIO_WritePin((pinDesc)->port,(pinDesc)->pin,GPIO_PIN_RESET); (pinDesc)->lastState = GPIO_PIN_RESET; (pinDesc)->lastEvent = HAL_GetTick();}
#define GPIO_PIN_TOGGLE(pinDesc) {HAL_GPIO_TogglePin((pinDesc)->port,(pinDesc)->pin); (pinDesc)->lastState = 1 - (pinDesc)->lastState; (pinDesc)->lastEvent = HAL_GetTick();}
#define GPIO_PIN_WRITE(pinDesc,state) {HAL_GPIO_WritePin((pinDesc)->port,(pinDesc)->pin,state); (pinDesc)->lastState = state; (pinDesc)->lastEvent = HAL_GetTick();}
#define GPIO_PIN_READ(pinDesc) HAL_GPIO_ReadPin((pinDesc)->port,(pinDesc)->pin)

#endif /* PIN_DESCRIPTION_H_ */
