#if defined(_MSC_VER)
#define STDCALL __stdcall
#define NOINLINE __declspec(noinline)
#else
#define STDCALL __attribute__((stdcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef int (STDCALL *ReadMessage)(void *, void *, unsigned int, unsigned int);
typedef int (STDCALL *PeekMessage)(void *, void *, unsigned int, unsigned int, unsigned int);
typedef void (STDCALL *SleepMilliseconds)(unsigned int);
static NOINLINE unsigned int STDCALL sub_004D1650(void *message, int wait)
{
    if (*(volatile unsigned int *)0x006D0530 != 0) {
        *(volatile unsigned int *)0x006D0530 = 0;
        return 0;
    }
    if (wait != 0 && *(volatile unsigned int *)0x0051BFA8 == 0) {
        if (*(volatile unsigned char *)0x0057F0B4 == 0 &&
            *(volatile unsigned short *)0x00596904 != 2)
            return (*(ReadMessage *)0x004FE2B8)(message, 0, 0, 0) != -1;
        if ((*(PeekMessage *)0x004FE2D0)(message, 0, 0, 0, 1) != 0)
            return 1;
        (*(SleepMilliseconds *)0x004FE10C)(0);
        return 0;
    }
    return (*(PeekMessage *)0x004FE2D0)(message, 0, 0, 0, 1);
}
unsigned int STDCALL hypothetical_context(void *message, int wait)
{
    return sub_004D1650(message, wait);
}
