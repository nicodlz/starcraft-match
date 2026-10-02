/* Independent C90 reconstruction; private EDX input selected by C context. */
typedef unsigned char u8;
#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
static NOINLINE int sub_00438410(u8 *p)
{
    u8 *a = *(u8 **)(p + 0x134);
    u8 *node;
    if (!a || a[8] != 4 || *(u8 **)(a + 12) != p)
        return 0;
    if (((u8 *)0x00664080U)[*(unsigned short *)(p + 0x64) * 4U] & 1)
        return 0;
    a = *(u8 **)(a + 16);
    if (a[5] == 2)
        return 0;
    node = *(u8 **)(a + 0x30);
    while (node) {
        u8 *owner = *(u8 **)(node + 12);
        if (owner != p && owner[0x4d] == 0x60 && !(owner[0xdc] & 0x40))
            return 1;
        node = *(u8 **)node;
    }
    return 0;
}
int context_00438410(u8 *p) { return sub_00438410(p); }
