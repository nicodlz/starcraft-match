#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
#define READ(address) (*(const volatile unsigned int *)(address))
static SC_NOINLINE unsigned int sub_0045B170(volatile unsigned int *alternate,
                                            unsigned int key)
{
    unsigned int base;
    unsigned int cursor;
    unsigned int tag;
    unsigned int value;
    base = READ(0x0068C104u);
    *alternate = 0;
    cursor = base + READ(base);
    tag = READ(cursor);
    while (tag != 0) {
        if (tag == key) {
            value = READ(cursor + 4u);
            if (value != 0) return value;
            break;
        }
        tag = READ(cursor + 16u);
        cursor += 16u;
    }
    base = READ(0x0068C108u);
    cursor = base + READ(base);
    tag = READ(cursor);
    while (tag != 0) {
        if (tag == key) {
            value = READ(cursor + 4u);
            if (value == 0) return 0;
            *alternate = 1;
            return value;
        }
        tag = READ(cursor + 8u);
        cursor += 8u;
    }
    return 0;
}
unsigned int context_0045B170(volatile unsigned int *alternate, unsigned int key)
{
    return sub_0045B170(alternate, key);
}
