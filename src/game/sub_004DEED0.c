#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int U32;
typedef U32 (STDCALL *Ticks)(void);
#define CELL(a,t) (*(t *)(a))
void sub_004DEED0(void)
{
    U32 next = (((U32 *)0x004ff90c)[CELL(0x006d0f6a,unsigned char)] *
                CELL(0x0057f23c,U32)) / 1000u;
    int changed = 0;
    int toggled;
    if (next != CELL(0x0050e05c,U32)) {
        CELL(0x0050e05c,U32) = next;
        changed = 1;
    }
    toggled = 0;
    if (CELL(0x006d11b0,U32)) {
        U32 now = CELL(0x004fe0c4,Ticks)();
        if ((int)(now - CELL(0x006d11b8,U32)) > 600) {
            U32 previous = CELL(0x006d11b4,U32);
            CELL(0x006d11b8,U32) = now;
            CELL(0x006d11b4,U32) = previous == 0;
            toggled = 1;
        }
    }
    if (changed || toggled) {
        CELL(0x0068c1b0,U32) = 1;
        CELL(0x0068ac74,unsigned char) = 1;
        CELL(0x0068c1f8,unsigned char) = 1;
        CELL(0x0068c1e8,U32) = 0;
        CELL(0x0068c1ec,U32) = 0;
    }
}
