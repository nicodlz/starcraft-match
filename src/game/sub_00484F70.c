typedef unsigned char u8;
typedef unsigned long u32;
u8 __stdcall sub_00484F70(u8 key)
{
    u8 result = 255;
    u32 best = 0xffffffff;
    u32 index = 8;
    u8 *p = (u8 *)0x57f008;
    do {
        p -= 0x24;
        --index;
        if ((p[0] == 2 || p[0] == 1) && p[2] == key) {
            u32 value = *(u32 *)(p - 4);
            if (value <= best) {
                result = (u8)index;
                best = value;
            }
        }
    } while (p != (u8 *)0x57eee8);
    return result;
}
