typedef unsigned long u32;
static __declspec(noinline) int sub_004B2D50(u32 index)
{
    u32 state = *(const u32 *)(0x0059B418 + index * 72);
    u32 selected;
    if (state == 1 || state == 11) return 0;
    selected = *(const u32 *)(0x0059B414 + index * 72);
    if (((const u32 *)0x0059B73C)[selected] == 2 ||
        (*(const u32 *)0x0051268C == selected &&
         *(const u32 *)0x0059B3D0 == 2)) return 1;
    return 0;
}
int caller_context_004B2D50(u32 index) { return sub_004B2D50(index); }
