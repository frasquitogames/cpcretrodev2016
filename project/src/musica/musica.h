#ifndef _MUSICA_H_
#define _MUSICA_H_

#include <cpctelera.h>
#include <types.h>


extern __at(0x9600) const u8 G_musica[257];
void initMusica();

#endif