typedef unsigned char u8;
typedef unsigned long u32;
static __declspec(noinline) int sub_00447810(u8 *unit)
{
    return unit == *(u8 **)(0x006903BC + (u32)unit[0x4C] * 0x4E8);
}
int context_00447810(u8 *unit) { return sub_00447810(unit); }
