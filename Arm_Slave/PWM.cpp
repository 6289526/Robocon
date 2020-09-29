/*
 * PWM.cpp
 *
 *  Created on: Mar 4, 2020
 *      Author: nuc
 */

#include "PWM.h"
#include <algorithm>

using namespace std;

PWM::PWM() {
	// TODO Auto-generated constructor stub
	min_period = -1;
	max_period = -1;

	htim = nullptr;
	tim_channel = 0;
}

PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

HAL_StatusTypeDef PWM::init(TIM_HandleTypeDef& _htim, uint32_t _tim_channel){
	htim = &_htim;
	tim_channel = _tim_channel;
	return HAL_TIM_PWM_Start(htim, tim_channel);
}

int PWM::set_minmax_duty_time(double min_usec, double max_usec){
	if(!htim){
		min_period = -1;
		max_period = -1;
		return -1;
	}


	double prescalar = htim->Init.Prescaler + 1;
	//double period    = htim->Init.Period + 1;
	double clk       = HAL_RCC_GetSysClockFreq();

	// PWM_freq = rcc_conf.PLL.PLLN / ( (htim->Init.Prescaler + 1) * (htim->Init.Period + 1) )

	// Period = (Prescalar + 1) / Clock
	min_period = min_usec * clk / (1000000.0 * prescalar);
	max_period = max_usec * clk / (1000000.0 * prescalar);

	return 0;
}

uint32_t PWM::set_org(uint32_t pwm_val){
	return __HAL_TIM_SET_COMPARE(htim, tim_channel, pwm_val);
}

uint32_t PWM::set(double duty_ratio){
	if(!htim)
		return 1;

	duty_ratio = max(-1.0, duty_ratio);
	//マイナス値は反転
	if(duty_ratio < 0)
		duty_ratio = -duty_ratio;
	duty_ratio = min(1.0, duty_ratio);

	double period    = htim->Init.Period + 1;
	if(max_period >= 0 && min_period >= 0)
		duty_ratio = (duty_ratio * (max_period - min_period) + min_period) / period;

	uint32_t pwm_val = htim->Init.Period * duty_ratio;
	return __HAL_TIM_SET_COMPARE(htim, tim_channel, pwm_val);
}
