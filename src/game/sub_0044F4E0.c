/* Independent C reconstruction of eight fixed player-record checks. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SC_FASTCALL __fastcall
#elif defined(__i386__)
#define SC_FASTCALL __attribute__((fastcall))
#else
#define SC_FASTCALL
#endif
unsigned SC_FASTCALL sub_0044F4E0(unsigned team){unsigned count=0; unsigned char human=2;
if(*(unsigned char*)0x57EEEAu==team && *(unsigned char*)0x57EEE8u==human)count=1;
if(*(unsigned char*)0x57EF0Eu==team && *(unsigned char*)0x57EF0Cu==human)count++;
if(*(unsigned char*)0x57EF32u==team && *(unsigned char*)0x57EF30u==human)count++;
if(*(unsigned char*)0x57EF56u==team && *(unsigned char*)0x57EF54u==human)count++;
if(*(unsigned char*)0x57EF7Au==team && *(unsigned char*)0x57EF78u==human)count++;
if(*(unsigned char*)0x57EF9Eu==team && *(unsigned char*)0x57EF9Cu==human)count++;
if(*(unsigned char*)0x57EFC2u==team && *(unsigned char*)0x57EFC0u==human)count++;
if(*(unsigned char*)0x57EFE6u==team && *(unsigned char*)0x57EFE4u==human)count++;
return count;
}
