typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
static __declspec(noinline) int sub_0049A480(u8 *p, u8 action)
{
    u32 flags = *(u32 *)(p + 0xDC);
    u16 kind;
    int enabled;
    if ((flags & 2) && (action == 0x27 || action == 0x28)) return 1;
    kind = *(u16 *)(p + 0x64);
    if ((kind == 0x2E || kind == 0x34) && action == 0x77) return 1;
    if (flags & 0x40000000) goto fail;
    if (kind == 0x2A && !((u8 *)0x0058D2C8)[p[0x4C] * 46]) goto fail;
    enabled = ((u8 *)0x00660988)[kind] != 0;
    if (!enabled) return enabled;
    if (action == 0x70) return 1;
fail:
    return 0;
}
int experiment_0049A480(u8 *p, u8 action)
{
    int result = sub_0049A480(p, action);
    return result + p[0];
}
