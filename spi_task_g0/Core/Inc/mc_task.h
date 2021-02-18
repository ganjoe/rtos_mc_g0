/*
 * mc_task.h
 *
 *  Created on: 18.02.2021
 *      Author: pymd02
 *
 *      Motor - Control - App
 *      systick wird über CubeMx - FreeRtos festgelegt
 *      abhängig von den headern für jeden Control - Block
 */

/*
 * BCD mit Ankerstrom und Bemf-Regelung
 *
 * Eingangsgrößen TD_MC_IF:
 * poti0	pwm-freq
 * poti1	rampe-rauf
 * poti2	rampe-runter
 * poti3	speed
 * poti4	max speed
 * switch0	cr
 * switch1	ccr
 * switch2	reset/init/detect
 * led0		status
 * led1		ccw
 * led2		cw
 * led2		fehler
 *
 */

#ifndef INC_MC_TASK_H_
#define INC_MC_TASK_H_

void mc_setup()
{
	/* muss als reset für die mc_loop dienen können*/
}

void mc_loop()
{
	/*	Die Loop ist nicht pwm-synchron, aber die ADC-Messung.
	 *  Während jedes Durchlaufes werden die ADC-Daten durch
	 *  ein ISR-Callback gebuffert und bei Beginn gemittelt.
	 *
	 */

	/* abfrage von TD_MC_IF Variablen (durch einen anderen Task geupdated)  */
	/* ADC-FILTER - update von den adc-queues */
	/* USER-RAMP - "Poti-Rampe", ggf. der äußere Regler*/
	/* FAST-RAMP - "Safty-Rampe", ggf. der innere Regler*/
	/* PWM & FREQ - für PWM Timer setzen */

}

#endif /* INC_MC_TASK_H_ */
