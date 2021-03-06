#ifndef __TOM_DOT_H__
#define __TOM_DOT_H__

/* Needs generalizing and tidying up across the RC2014 systems */

#include "config.h"

/* SIO 2 ports */

#define SIO0_BASE 0x00
__sfr __at (SIO0_BASE + 0) SIOA_D;
__sfr __at (SIO0_BASE + 1) SIOB_D;
__sfr __at (SIO0_BASE + 2) SIOA_C;
__sfr __at (SIO0_BASE + 3) SIOB_C;

extern void sio2_otir(uint8_t port) __z88dk_fastcall;

#endif
