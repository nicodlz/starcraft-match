typedef unsigned char u8;
typedef unsigned long u32;
static __declspec(noinline) u8 *__fastcall sub_0047D2C0(u32 a, u32 b)
{
    u8 *node = ((u8 **)0x00658B10)[((a << 4) + b + a) & 0x3FF];
    if (node) {
      do {
        if (node[0x10] == b && node[0x11] == a) break;
        node = *(u8 **)(node + 8);
      } while (node);
    }
    return node;
}

u8 *context_0047D2C0(u32 a,u32 b) { return sub_0047D2C0(a,b); }
