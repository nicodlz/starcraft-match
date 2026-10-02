/* Independent body; next link intentionally reloads after the external call. */
typedef unsigned int u32;
typedef unsigned char u8;
#if defined(_MSC_VER)
#define NI __declspec(noinline)
#define STDCALL __stdcall
#define FAST __fastcall
#else
#define NI __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#define FAST __attribute__((fastcall))
#endif
/* EDX is ignored by the original helper; the dummy preserves call placement. */
extern void FAST sub_0049E590(u8 *current,u8 *ignored_edx,u8 *removed);
#pragma code_seg(".scmatch")
static NI void STDCALL sub_0049E8A0(u32 mask,u8 *removed)
{
    u32 bit = 1;
    u8 index = 0;
    mask &= 0xfffu;
    while (mask) {
        if (mask & bit) {
            u8 *current;
            mask &= ~bit;
            current = ((u8 **)0x006283f8)[index];
            while (current) {
                sub_0049E590(current,removed,removed);
                current = *(u8 **)(current + 0x6c);
            }
        }
        bit <<= 1;
        ++index;
    }
}
#pragma code_seg(".scctx")
void compilation_context(u32 mask,u8 *removed) {sub_0049E8A0(mask,removed);}
