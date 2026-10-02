#if defined(_MSC_VER)
#define FAST __fastcall
#define STDCALL __stdcall
#define NOINLINE __declspec(noinline)
#else
#define FAST __attribute__((fastcall))
#define STDCALL __attribute__((stdcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32;
typedef struct View { unsigned char pad[44]; U32 a, b; } View;
extern U32 FAST sub_0040C360(U32 a, U32 b, U32 c, U32 d);
#pragma code_seg(".scmatch")
static NOINLINE U32 STDCALL sub_00401240(U32 reg_value, const View *object, U32 limit, volatile U32 stack_value)
{
    U32 b = object->b;
    U32 a = object->a;
    U32 measured = sub_0040C360(a, stack_value << 8, b, reg_value << 8);
    return (measured >> 8) <= limit;
}
#pragma code_seg(".scctx")
/* Hypothetical ordinary compiler context, not a reconstructed game caller. */
U32 STDCALL context_00401240(U32 reg_value, const View *object, U32 limit, U32 stack_value)
{
    return sub_00401240(reg_value, object, limit, stack_value);
}
