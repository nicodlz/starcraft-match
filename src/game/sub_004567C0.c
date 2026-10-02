typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
static __declspec(noinline) void sub_004567C0(const u8 *p)
{
    u8 empty = *(u8 *)0x0068C20A;
    s32 denominator;
    s32 maximum;
    s32 health;
    s32 index;
    s32 i;
    const u8 *values;
    u8 *slots = (u8 *)0x0050CE91;
    *(u8 *)0x0050CE91 = empty;
    *(u8 *)0x0050CE92 = empty;
    *(u8 *)0x0050CE93 = empty;
    *(u8 *)0x0050CE94 = empty;
    maximum = ((s32 *)0x00662350)[*(const u16 *)(p + 0x64)] >> 8;
    if (maximum) denominator = maximum;
    else {
        maximum = (s32)(*(const u32 *)(p + 8) + 255) >> 8;
        denominator = maximum ? maximum : 1;
    }
    health = (s32)(*(const u32 *)(p + 8) + 255) >> 8;
    index = (s32)((u32)health * 9) / denominator;
    if (p[0xE1] & 1) values = (u8 *)0x00515230 + index * 4;
    else values = (u8 *)0x00515258 + index * 4;
    for (i = 0; i < 4;) {
        s32 slot = ((p[0xE1] >> i) & 7) * 3 / 7;
        while (slots[slot] != empty) {
            ++slot;
            if (slot == 4) slot = 0;
        }
        slots[slot] = ((u8 *)0x0068C208)[*values];
        ++i;
        ++values;
    }
}
int experiment_004567C0(const u8 *p)
{
    sub_004567C0(p);
    return p[0];
}
