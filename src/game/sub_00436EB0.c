typedef unsigned char u8;
typedef unsigned long u32;
static __declspec(noinline) u32 sub_00436EB0(u8 *p)
{
    u8 *node = *(u8 **)(p + 0x30);
    while (node) {
        u8 *unit = *(u8 **)(node + 0x0c);
        u32 kind;
        if (!(unit[0xdc] & 1)) return 1;
        kind = unit[0x4d];
        if (kind == 0x6a || kind == 0x96) return 1;
        node = *(u8 **)node;
    }
    return 0;
}
u32 context_00436EB0(u8 *p) { return sub_00436EB0(p); }
