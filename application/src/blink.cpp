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
 * add.cpp
 *
 *  Created on: 12 Aug 2019
 *      Author: jeppa
 */
#include <stdio.h>
#include "interrupt.hpp"
#include "clock.hpp"
#include "timer.hpp"
#include "gpio.hpp"
#include "minimumCppRuntime.hpp"

Clock clock;
Interrupt timer1Cmp0Irq( Interrupt::pwm1cmp0 );
extern "C"
{
	extern void _enable_interrupt();
}

int main ()
{
	Interrupt::init();
	Interrupt::setThreshold( 0 );
	int count = 0;
	clock.usePllWithHfXosc();
	timer1->setUp1MsTimeBase();
	timer1Cmp0Irq.enable();
	_enable_interrupt();
	gpio->setAsOutput( Gpio::pin19 );
	gpio->setAsOutput( Gpio::pin21 );
	gpio->setAsOutput( Gpio::pin22 );
	gpio->set( Gpio::pin19 );
	gpio->clear( Gpio::pin21 );
	gpio->set( Gpio::pin22 );
	while ( 1 )
	{
//		if ( 500 == count )
//		{
//			gpio->clear( Gpio::pin21 );
//		}
//		if ( 1000 == count )
//		{
//			count = 0;
//			gpio->set( Gpio::pin21 );
//		}
//		timer2->waitFor1MsTimeOut();
//		count++;
	}
	return 0;
}


