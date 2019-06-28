/*
 *  Created on: 01.15.2019
 *      Author: Georgi Angelov
 */

#ifndef __VARIANT_H__
#define __VARIANT_H__

#include <interface.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LED 0                 /* PINNAME_NETLIGHT */
#define LED_BUILTIN 0         /* PINNAME_NETLIGHT */

#ifdef __cplusplus
}

#include <HardwareSerial.h>
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;

#endif //__cplusplus

#endif /* __VARIANT_H__ */
