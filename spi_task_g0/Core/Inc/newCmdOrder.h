/*
 * newCmdOrder.h
 *
 *  Created on: 07.01.2021
 *      Author: danie
 */

#include "datatypes.h"

#ifndef APP_NEWCMDORDER_H_
#define APP_NEWCMDORDER_H_

/*------------modflag Commands--------------*/

void 	cmd_init_callbacks();
void 	term_lol_parse(TD_LINEOBJ *line);

void    reset	(int argc, const char **argv);
void    settime	(int argc, const char **argv);
void    setdate	(int argc, const char **argv);

/*------------hotwater commands--------------*/
/*------------motor control commands--------------*/

void	mcc_if_pwm		(int argc, const char **argv);
void	mcc_if_ramp		(int argc, const char **argv);
void	mcc_if_speed	(int argc, const char **argv);
void	mcc_if_mspd		(int argc, const char **argv);
void	mcc_if_dir		(int argc, const char **argv);
void	mcc_if_init		(int argc, const char **argv);


#endif /* APP_NEWCMDORDER_H_ */
