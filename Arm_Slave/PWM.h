/*
 * PWM.h
 *
 *  Created on: Mar 4, 2020
 *      Author: nuc
 */
#include "main.h"

#ifndef PWM_H_
#define PWM_H_

class PWM {
private:
	double min_period;	// pulse width under
	double max_period;	// pulse width top
	TIM_HandleTypeDef* htim;
	uint32_t tim_channel;
public:
	PWM();
	virtual ~PWM();

	HAL_StatusTypeDef init(TIM_HandleTypeDef& htim, uint32_t tim_channel);
	int set_minmax_duty_time(double min_usec = -1, double max_usec = -1);

	uint32_t set_org(uint32_t pwm_val);
	uint32_t set(double duty_ratio);
};

#endif /* PWM_H_ */
