typedef unsigned char u8;
typedef unsigned long u32;
typedef signed long s32;
static __inline u32 amount_004475B0(u32 index,u32 offset) { return *(volatile u32 *)(0x68fee8+index*0x4e8+offset); }
static __inline u8 fraction_004475B0(u32 a,u32 b) { u32 total=a+b; a*=100; return (u8)(a/total); }
static __declspec(noinline) void __stdcall sub_004475B0(u32 index, u8 * volatile second, volatile u8 *first)
{
    u32 a = amount_004475B0(index,4);
    u32 b;
    s32 db;
    u8 ratio;
    if (a == 0) {
        *first = 0;
        *second = 100;
        return;
    }
    b = amount_004475B0(index,0);
    if (b == 0) {
        *(u8 *)first = 100;
        *second = 0;
        return;
    }
    a -= ((u32 *)0x57f120)[index];
    db = (s32)(b - ((u32 *)0x57f0f0)[index]);
    if (db > 0 && (s32)a <= 0) {
        *second = 100;
        *first = 0;
        return;
    }
    if ((s32)a > 0 && db <= 0) {
        *second = 0;
        *first = 100;
        return;
    }
    a = amount_004475B0(index,4);
    ratio = fraction_004475B0(a,b);
    *first = (u8)ratio;
    *second = (u8)(100-ratio);
}
void context_004475B0(u32 i,u8 *a,u8 *b) { sub_004475B0(i,b,a); }
