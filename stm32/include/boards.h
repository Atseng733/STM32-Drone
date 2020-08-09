#ifndef BOARDS_H
#define BOARDS_H

#include <configuration.h>

#if defined(BOARD_F407)
	#include <f407.h>
#elif defined(BOARD_F103)
	#include <f103.h>
#endif


#endif