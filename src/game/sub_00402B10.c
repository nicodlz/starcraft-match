typedef unsigned short u16;
typedef unsigned char u8;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#else
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#endif
#define TYPE(p) (*(const u16 *)((p)+0x64))
#define BOUNDS(p) ((const u16 *)0x006617C8 + TYPE(p)*4)
static NOINLINE void FASTCALL sub_00402B10(const u8 *first, const u8 *second, short *output, short x, short y)
{
    const short *bounds = (const short *)BOUNDS(first);
    output[1] = y - bounds[1];
    output[3] = bounds[3] + y;
    output[0] = x - bounds[0];
    output[2] = bounds[2] + x;
    output[0] += (short)(-1 - BOUNDS(second)[2]);
    output[2] += (u16)(BOUNDS(second)[0] + 1);
    output[1] += (short)(-1 - BOUNDS(second)[3]);
    output[3] += (u16)(BOUNDS(second)[1] + 1);
}
void context_00402B10(const u8 *first, const u8 *second, short *output, short x, short y)
{
    sub_00402B10(first, second, output, x, y);
}
