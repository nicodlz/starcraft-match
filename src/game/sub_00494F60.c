typedef unsigned char u8;
typedef unsigned long u32;
void __fastcall sub_00494F60(u8 *object, int value)
{
    unsigned index;
    if (*(int *)(object + 0x38) == value)
        return;
    index = object[0x4a] * 8u;
    *(int *)(object + 0x38) = value;
    *(int *)(object + 0x40) = (int)(*(u32 *)(0x00512d28 + index) * (u32)value) >> 8;
    *(int *)(object + 0x44) = (int)(*(u32 *)(0x00512d2c + index) * (u32)value) >> 8;
}
