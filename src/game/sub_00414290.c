/* Count the eight reviewed neighboring WORD predicates, preserving wraparound. */
typedef unsigned int u32;
typedef unsigned short u16;
extern u32 g_006D0F08, g_006D0C6C;
extern u16 *g_006D0E84;
#pragma code_seg(".test")
static u32 qualifies(u32 x, u32 y) {
    if (x >= g_006D0F08 || y >= g_006D0C6C) return 0;
    return (g_006D0E84[y * g_006D0F08 + x] & 0x7FF0u) == 0x10u;
}
#pragma code_seg(".near")
u32 __stdcall sub_00414290(u32 x, u32 y) {
    u32 count = 0;
    count += qualifies(x - 1, y - 1);
    count += qualifies(x, y - 1);
    count += qualifies(x + 1, y - 1);
    count += qualifies(x - 1, y);
    count += qualifies(x + 1, y);
    count += qualifies(x - 1, y + 1);
    count += qualifies(x, y + 1);
    return count + qualifies(x + 1, y + 1);
}
