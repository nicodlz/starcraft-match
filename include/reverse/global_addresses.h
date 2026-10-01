#ifndef STARCRAFT_REVERSE_GLOBAL_ADDRESSES_H
#define STARCRAFT_REVERSE_GLOBAL_ADDRESSES_H
// Preferred-VA lvalues for the pinned, non-relocatable 1.16.1 image.
// These preserve access widths and keep candidate object sections relocation-free.
// Semantic names are community annotations; addresses/accesses are binary observations.
_Static_assert(sizeof(unsigned int) == 4, "DWORD width required");
#define SC_PAUSE_STATE (*(volatile unsigned int *)0x006509C4u)
#define SC_VISIBILITY_HASH_UPDATE (*(volatile unsigned int *)0x00629D90u)
#define SC_MAP_START_STATUS (*(volatile unsigned char *)0x006D121Cu)
#define SC_IN_GAME_LOOP (*(volatile unsigned int *)0x006D11C8u)
#endif
