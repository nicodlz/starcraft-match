typedef unsigned char u8;
typedef unsigned long u32;
static __inline u8 read8(u8 **cursor)
{
    u8 result = **cursor;
    ++*cursor;
    return result;
}
u8 *__fastcall sub_004CDCE0(u8 *object)
{
    u8 *cursor = *(u8 **)(object + 8);
    u32 length = *(volatile u32 *)(object + 12);
    u8 *end = (u8 *)(length + (u32)cursor);
    while (cursor < end) {
        int total;
        int count;
        cursor += 4;
        count = read8(&cursor);
        total = 0;
        while (total < count) {
            int opcode = cursor[1];
            int length = ((int *)0x005005f8)[opcode];
            cursor++;
            if (opcode >= 9 && opcode <= 11)
                length = cursor[1] * 2 + 2;
            total = (int)((u32)total + (u32)length + 1);
            cursor += length;
        }
    }
    return cursor;
}
