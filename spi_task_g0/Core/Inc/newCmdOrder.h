/*
 * newCmdOrder.h
 *
 *  Created on: 07.01.2021
 *      Author: daniel
 *
 *      Callback Funktionen für Uart-Terminal o.ä.
 */

#include "datatypes.h"

#ifndef APP_NEWCMDORDER_H_
#define APP_NEWCMDORDER_H_


/*--------------------------*/
void 	cmd_init_callbacks();
void 	cmd_parse_lobj(TD_LINEOBJ *line);

/*------------modflag Commands--------------*/

void    reset	(int argc, const char **argv);
void    settime	(int argc, const char **argv);
void    setdate	(int argc, const char **argv);


/*------------motor control commands--------------
 * - Contactron Interface Setter
 * -
 *
 */

void	pwm		(int argc, const char **argv);
void	ramp	(int argc, const char **argv);
void	speed	(int argc, const char **argv);
void	mspd	(int argc, const char **argv);
void	dir		(int argc, const char **argv);
void	init	(int argc, const char **argv);


#endif /* APP_NEWCMDORDER_H_ */
