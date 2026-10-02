typedef unsigned char u8;
u8 * __fastcall sub_004AA930(unsigned long unused, u8 key)
{
    u8 *p = *(u8 **)0x0051A270;
    u8 *result = 0;
    if ((long)p > 0) {
        do {
            if (key == p[0x48]) {
                result = p + 0x16c;
                break;
            }
            p = *(u8 **)(p + 4);
            if ((long)p <= 0) break;
        } while (p);
    }
    return result;
}
