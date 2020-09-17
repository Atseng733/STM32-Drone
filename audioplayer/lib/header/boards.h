#ifndef BOARDS_H
#define BOARDS_H

#include <configuration.h>

#if defined(BOARD_F407)
	#include <f407.h>
	#include <f407_fn.h>
#elif defined(BOARD_F103)
	#include <f103.h>
	#include <f1_gpio.h>
abc
#endif

#endif