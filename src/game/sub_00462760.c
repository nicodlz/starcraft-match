typedef unsigned char u8;
typedef unsigned short u16;
static __declspec(noinline) void sub_00462760(unsigned index, u16 key)
{
    u8 *node = *(u8 **)(0x0068510c + index * 8);
    while (node) {
        if (!*(unsigned *)(node + 0x0c) && *(unsigned *)(node + 0x1c)) {
            unsigned value = *(u16 *)(node + 0x10);
            if (value == 0x1e)
                value = 5;
            if (value == key)
                *(unsigned *)(node + 0x1c) = 1;
        }
        node = *(u8 **)node;
    }
}
/* Ordinary compiler context only, not recovered original source. */
void context_00462760(unsigned index, u16 key)
{
    sub_00462760(index, key);
}
