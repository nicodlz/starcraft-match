/* Independent C reconstruction for the reviewed pinned Windows i386 region. */
#if defined(_MSC_VER)
#define SUB00461720_STDCALL __stdcall
#elif defined(__i386__)
#define SUB00461720_STDCALL __attribute__((stdcall))
#else
#define SUB00461720_STDCALL
#endif

typedef unsigned int Sub00461720U32;
typedef char Sub00461720Width[(sizeof(Sub00461720U32) == 4) ? 1 : -1];
typedef Sub00461720U32 (SUB00461720_STDCALL *Sub00461720Timer)(void);

Sub00461720U32 sub_00461720(void)
{
    if (*(unsigned char *)0x0057F0B4) {
        Sub00461720U32 now = (*(Sub00461720Timer *)0x004FE0C4)();
        if (now <= *(Sub00461720U32 *)0x00685164 + 120000U)
            return 0;
    }
    return 1;
}
