#if defined(_MSC_VER) && !defined(__clang__)
#define SC_LOCAL static
#define SC_NOINLINE __declspec(noinline)
typedef unsigned int ScAddress;
#else
#define SC_LOCAL
#define SC_NOINLINE __attribute__((noinline))
typedef __UINTPTR_TYPE__ ScAddress;
#endif
typedef struct {
    unsigned char reserved_00[6];
    unsigned char field_06;
    unsigned char field_07;
    unsigned int reserved_08;
    unsigned int field_0C;
} Sub00483160View;
SC_LOCAL SC_NOINLINE unsigned int sub_00483160(const Sub00483160View *value) {
    unsigned int first = value->field_06;
    unsigned int remaining = (unsigned int)value->field_07 - first;
    if (remaining == 0) return 0;
    {
    const unsigned short *current;
    unsigned short identifiers[5];
    unsigned short *end;
    unsigned int count;
    current = (const unsigned short *)(ScAddress)value->field_0C + first;
    count = 0;
    end = identifiers;
    do {
        const unsigned char *entry = *(const unsigned char **)0x006D5BFCu;
        unsigned int index = *current;
        entry += (index << 6) + 0x449FCu;
        --remaining;
        if (*(const unsigned short *)(entry + 4) >= 4u) {
            unsigned short identifier = *(const unsigned short *)(entry + 2);
            unsigned short *scan = identifiers;
            while (scan < end) {
                if (identifier == *scan) break;
                ++scan;
            }
            if (scan >= end) {
                ++count;
                if (count >= 5u) return count;
                *end++ = identifier;
            }
        }
        ++current;
    } while (remaining);
    return count >= 2u ? count : 0;
    }
}
/* Hypothetical ordinary C compiler context, not reconstructed or counted. */
unsigned int sc_context_00483160(const Sub00483160View *value) {
    return sub_00483160(value);
}
