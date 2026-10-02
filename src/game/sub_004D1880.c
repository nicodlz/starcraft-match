/* Independent reconstruction against the pinned 1.16.1 region.
   Import pointers and callback address are binary observations; semantic
   community naming is documented separately. Unaligned DWORD destination
   0x006d0f31 is intentional on the pinned Windows i386 target. */
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int (STDCALL *window_callback)(void *,u32);
typedef u32 (STDCALL *window_process)(void *,u32 *);
typedef int (STDCALL *enumerate)(window_callback,u32);
#define DWORD(a) (*(u32 *)(a))
#define WORD(a) (*(u16 *)(a))
#define BYTE(a) (*(u8 *)(a))
void sub_004D1880(void)
{
    u32 process;
    if (DWORD(0x006d11bc) == 4) {
        DWORD(0x005967f0) = 1;
        (*(window_process *)0x004fe334)((void *)DWORD(0x0051bfb0),&process);
        (*(enumerate *)0x004fe32c)((window_callback)0x004dc6d0, process);
    } else DWORD(0x005967f0) = 1;
    if (WORD(0x00596904) == 3) {
        DWORD(0x006d11bc) = 0x19;
        {
            u32 third = DWORD(0x006d0f14);
            BYTE(0x006d11ec) = 0;
            WORD(0x0051ce90) = 2;
            if (!third) DWORD(0x006d0f31) = DWORD(0x0057f23c);
        }
    } else {
        DWORD(0x006d11bc) = 0x19;
        WORD(0x00596904) = 2;
    }
}
