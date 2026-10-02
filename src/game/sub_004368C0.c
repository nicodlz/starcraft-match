typedef unsigned long u32;
static __declspec(noinline) u32 __stdcall sub_004368C0(u32 *state, u32 value, u32 *first, u32 *second)
{
    if (*state == 1) {
        *first = value;
        *state = 2;
        return 0;
    }
    *second = value;
    return 1;
}
u32 context_004368C0(u32 *state, u32 value, u32 *first, u32 *second)
{
    return sub_004368C0(state, value, first, second);
}
