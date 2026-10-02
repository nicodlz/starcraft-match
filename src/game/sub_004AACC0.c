typedef unsigned int u32;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef void (STDCALL *Callback)(void *, void *, void *, u32);
static NOINLINE void STDCALL sub_004AACC0(unsigned char first, unsigned char second, Callback callback)
{
    unsigned char *entry = *(unsigned char **)0x0051a270UL;
    if ((int)entry > 0) do {
        if (entry[0x48] == first && entry[0x49] == second)
            callback(entry + 8, entry + 0x28, entry + 0x48, 0);
        entry = *(unsigned char **)(entry + 4);
        if ((int)entry <= 0) break;
    } while (entry);
}
u32 context(unsigned char first, unsigned char second, Callback callback)
{
    sub_004AACC0(first, second, callback);
    return (u32)callback + first;
}
