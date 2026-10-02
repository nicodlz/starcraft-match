#if defined(_MSC_VER)
#define SC __stdcall
#define FC __fastcall
#define NI __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define FC __attribute__((fastcall))
#define NI __attribute__((noinline))
#endif
typedef unsigned long u32;
typedef void (FC *callback)(char *, u32, u32);
static NI void SC sub_0044D0C0(char **names, u32 *values, callback cb, u32 context)
{
    if (names && values && cb && **names) {
        u32 delta = (u32)values - (u32)names;
        do {
            cb(*names, *(u32 *)((u32)names + delta), context);
            ++names;
        } while (**names);
    }
}
void context(char **names, u32 *values, callback cb, u32 arg)
{
    sub_0044D0C0(names,values,cb,arg);
}
