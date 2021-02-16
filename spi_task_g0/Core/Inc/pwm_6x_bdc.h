/*
 * pwm_6x_bdc.h
 *
 *  Created on: 16.02.2021
 *      Author: danie
 */

#ifndef INC_PWM_6X_BDC_H_
#define INC_PWM_6X_BDC_H_

#include "main.h"
#include "stdint.h"

typedef enum
{
	ccw,
	cw,
	stall,
	error,
	standby
}EN_PDC_STATES;

typedef struct
{
	uint16_t maxFreq, minFreq;	//pwm
	float timestep, stepdelta;	//systick und inkrement des reglers
	EN_PDC_STATES mcstates;
}TD_PDC_PARAMS;

void pdc_init();
/* rampe bezieht sich immer auf systick 1khz */
void pdc_mc_ramp(float setpoint, TD_PDC_PARAMS blower);

/* low level */
void pdc_set_duty(float duty);
void pdc_set_state(EN_PDC_STATES state);
void pdc_set_freq(uint16_t freq);

#endif /* INC_PWM_6X_BDC_H_ */
