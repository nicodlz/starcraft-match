#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
#define S(v) ((int)(v))
#define WORD(a) ((u32)*(unsigned short *)(a))
static NOINLINE int STDCALL sub_0049B8D0(u32 *x, u32 *y, u32 *w, u32 *h)
{
    u32 camera_x = *(u32 *)0x0062848Cu >> 5;
    u32 camera_y = *(u32 *)0x006284A8u >> 5;
    if (S(*x) < 0) *x = 0;
    else if (S(*w + *x) >= (int)WORD(0x0057F1D4u))
        *w = WORD(0x0057F1D4u) - *x;
    if (S(*y) < 0) *y = 0;
    else if (S(*h + *y) >= (int)WORD(0x0057F1D6u))
        *h = WORD(0x0057F1D6u) - *y;
    *x -= camera_x;
    *y -= camera_y;
    if (S(*x) < 0) { *w += *x; *x = 0; }
    if (S(*w + *x) >= 21) *w = 21u - *x;
    if (S(*y) < 0) { *h += *y; *y = 0; }
    if (S(*h + *y) >= 14) *h = 14u - *y;
    if (S(*w) > 0 && S(*h) > 0 && S(*x) < 21 && S(*y) < 14) {
        *x += camera_x;
        *y += camera_y;
        if (S(*x) < (int)WORD(0x0057F1D4u) && S(*y) < (int)WORD(0x0057F1D6u))
            return 1;
    }
    return 0;
}
int context_0049B8D0(u32 *x,u32 *y,u32 *w,u32 *h) { return sub_0049B8D0(x,y,w,h); }
