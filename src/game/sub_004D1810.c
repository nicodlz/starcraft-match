typedef unsigned char u8;
typedef unsigned long u32;
#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
typedef short (SC_STDCALL *KeyState)(int);
u32 sub_004D1810(void)
{
    u32 flags = 0;
    KeyState key;
    if (*(volatile u8 *)0x00596A28UL) flags = 3;
    if (*(volatile u8 *)0x00596A29UL) flags |= 4;
    if (*(volatile u8 *)0x00596A2AUL) flags |= 8;
    key = *(KeyState *)0x004FE2C0UL;
    if (key(0x14) & 1) flags |= 0x40;
    if (key(0x90) & 1) flags |= 0x20;
    if (key(0x91) & 1) flags |= 0x10;
    if (key(0x2D) & 1) flags |= 0x80;
    return flags;
}
