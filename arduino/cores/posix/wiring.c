/*
    Created on: 01.01.2019
    Author: Georgi Angelov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#include <interface.h>
#include <variant.h>

void printDateTime()
{
  time_t t;
  time(&t);
  struct tm *timeinfo;
  timeinfo = localtime(&t);
  printf("%s", asctime(timeinfo));
}

uint32_t utc()
{
  time_t t;
  time(&t);
  return t;
}

void delay(unsigned int ms)
{
  usleep(ms * 1000);
}

inline void delayMicroseconds(unsigned int us)
{
  usleep(us);
}

#include <sys/time.h>
unsigned int millis(void)
{
  struct timeval te;
  gettimeofday(&te, NULL);                                         // get current time
  long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
  return milliseconds;
}

unsigned int seconds(void)
{
  return millis() / 1000;
}

inline void yield(void) {}

bool no_interrupt = 1;

void interrupts(void)
{
  no_interrupt = 1;
}

void noInterrupts(void)
{
  no_interrupt = 0;
}

bool noStopInterrupts(void)
{
  return no_interrupt;
}

uint32_t clockCyclesPerMicrosecond(void)
{
  return 0; // TODO
}

uint32_t clockCyclesToMicroseconds(uint32_t a)
{
  return a / clockCyclesPerMicrosecond();
}

uint32_t microsecondsToClockCycles(uint32_t a)
{
  return a * clockCyclesPerMicrosecond();
}
