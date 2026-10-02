#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_FASTCALL __fastcall
#define SC_STDCALL __stdcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_FASTCALL __attribute__((fastcall))
#define SC_STDCALL __attribute__((stdcall))
#endif
/* Recorded MSVC whole-TU optimization emits AX/CX/DX plus five stack slots. */
static SC_NOINLINE void SC_STDCALL sub_00458800(unsigned short a, unsigned short b, unsigned short c, unsigned short d, unsigned short e, unsigned short f, unsigned short g, unsigned short h) {
    *(volatile unsigned short *)0x0068C1D0u = a;
    *(volatile unsigned short *)0x0068C1D2u = b;
    *(volatile unsigned short *)0x0068C1D4u = c;
    *(volatile unsigned short *)0x0068C1D6u = d;
    *(volatile unsigned short *)0x0068C1D8u = e;
    *(volatile unsigned short *)0x0068C1DAu = f;
    *(volatile unsigned short *)0x0068C1DCu = g;
    *(volatile unsigned short *)0x0068C1DEu = h;
}
/* Independent compiler scaffold, not a reconstructed game caller. */
void SC_FASTCALL independent_probe_00458800(unsigned short a, unsigned short b, unsigned short c, unsigned short d, unsigned short e, unsigned short f, unsigned short g, unsigned short h) {
    sub_00458800(a,b,c,d,e,f,g,h);
}
