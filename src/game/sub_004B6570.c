typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
static __declspec(noinline) void sub_004B6570(u8 *p)
{
    u8 index;
    if (*(u32 *)0x006D051C != 1) return;
    if (*(u16 *)(p + 0x22)) p = *(u8 **)(p + 0x32);
    p = *(u8 **)(p + 0x42);
    while (p) {
        if (*(u16 *)(p + 0x20) == 6) break;
        p = *(u8 **)p;
    }
    if (!p) return;
    if (!p[0x46]) return;
    index = p[0x48];
    if (index == 255) return;
    *(u32 *)0x006D5A48 = *(u32 *)0x006D5A4C + (*(u32 **)(p + 0x42))[index] * 8;
}
void experiment_004B6570(u8 *p) { sub_004B6570(p); }
