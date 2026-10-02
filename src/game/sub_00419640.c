/* Independently reconstructed pinned Windows i386 1.16.1 leaf. */
#if defined(_MSC_VER) && !defined(__clang__)
#define FASTCALL __fastcall
#elif defined(__i386__)
#define FASTCALL __attribute__((fastcall))
#else
#define FASTCALL
#endif
typedef char Sub00419640DwordWidth[(sizeof(unsigned int)==4)?1:-1];
/* ECX is explicitly unused; the actual input is EDX. */
void FASTCALL sub_00419640(unsigned int unused, unsigned int target)
{
 volatile unsigned int *slot=(volatile unsigned int *)0x006d5e40;
 unsigned int count=19;
 (void)unused;
 do { if (*slot==target) *slot=0; ++slot; } while (--count);
 if (*(volatile unsigned int *)0x006d5e90==target) *(volatile unsigned int *)0x006d5e90=0;
 if (*(volatile unsigned int *)0x006d5e98==target) *(volatile unsigned int *)0x006d5e98=0;
 if (*(volatile unsigned int *)0x006d5ea0==target) *(volatile unsigned int *)0x006d5ea0=0;
 if (*(volatile unsigned int *)0x006d5ea8==target) *(volatile unsigned int *)0x006d5ea8=0;
}
