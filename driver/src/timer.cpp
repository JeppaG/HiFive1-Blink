/*
 * Copyright 2019 JG Mechatronics AB
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *****************************************************************************
 *
 * timer.cpp
 *
 *  Created on: 20 Aug 2019
 *      Author: jeppa
 */

#include "timer.hpp"
#include "hwRegisterOperations.hpp"
#include "gpio.hpp"
#include "interrupt.hpp"

Timer timerObject0( Timer::pwm0 );
Timer timerObject1( Timer::pwm1 );
Timer timerObject2( Timer::pwm2 );

Timer* timer0 = &timerObject0;
Timer* timer1 = &timerObject1;
Timer* timer2 = &timerObject2;


/***********************************************************************/
Timer::timerRegisterType* const Timer::timerRegisterPwm0 = reinterpret_cast<timerRegisterType*>( pwm0BaseAddress );
Timer::timerRegisterType* const Timer::timerRegisterPwm1 = reinterpret_cast<timerRegisterType*>( pwm1BaseAddress );
Timer::timerRegisterType* const Timer::timerRegisterPwm2 = reinterpret_cast<timerRegisterType*>( pwm2BaseAddress );

Timer::Timer( const uint8_t timerSelect )
{
	switch ( timerSelect )
	{
	case pwm0 : timerRegister = timerRegisterPwm0;
		break;
	case pwm1 : timerRegister = timerRegisterPwm1;
		break;
	case pwm2 : timerRegister = timerRegisterPwm2;
		break;
	default :
		break;
	}
}

Timer::~Timer()
{
}

void Timer::setUp1MsTimeBase()
{
	timerRegister->pwmCmp0 = tickTimerPwm0CmpConfig;
	timerRegister->pwmCfg = tickTimerConfig;
}

void Timer::waitFor1MsTimeOut()
{
	static uint32_t* claimRegister = reinterpret_cast<uint32_t*>( 0xc200004 );
	static uint32_t* pendingRegister1 = reinterpret_cast<uint32_t*>( 0xC001000 );
	static uint32_t* pendingRegister2 = reinterpret_cast<uint32_t*>( 0xC001004 );
	static uint32_t* enableRegister1 = reinterpret_cast<uint32_t*>( 0xC002000 );
	static uint32_t* enableRegister2 = reinterpret_cast<uint32_t*>( 0xC002004 );


	while ( false == hwRegOps::compareBits( timerRegister->pwmCfg, cmp0IrqMask )  );
	uint32_t pwmCfg1 = timerRegister->pwmCfg;
	uint32_t pending1_1 = *pendingRegister1;
	uint32_t pending2_1 = *pendingRegister2;
	uint32_t enable1_1 = *enableRegister1;
	uint32_t enable2_1 = *enableRegister2;
	uint32_t claim1 = *claimRegister;
	hwRegOps::clearBits( timerRegister->pwmCfg, cmp0IrqMask );
	uint32_t pwmCfg2 = timerRegister->pwmCfg;
	uint32_t pending1_2 = *pendingRegister1;
	uint32_t pending2_2 = *pendingRegister2;
	uint32_t enable1_2 = *enableRegister1;
	uint32_t enable2_2 = *enableRegister2;
	uint32_t claim2 = *claimRegister;
	*claimRegister = 44;
}

/* Interrupt handlers */
void Timer::pwm1cmp0handler()
{
	static uint32_t count = 0;

	hwRegOps::clearBits( timerRegisterPwm1->pwmCfg, cmp0IrqMask );
	count++;
	if ( 250 == count )
	{
		gpio->clear( Gpio::pin21 );
	}
	else if ( 500 == count )
	{
		gpio->set( Gpio::pin21 );
		count = 0;
	}
}
