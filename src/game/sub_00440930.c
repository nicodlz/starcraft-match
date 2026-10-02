/* Independently reconstructed ECX/EDX callback predicate. */
#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#elif defined(__i386__)
#define SC_FASTCALL __attribute__((fastcall))
#else
#define SC_FASTCALL
#endif

typedef struct Sub00440930View {
    unsigned char unknown0[0x4C];
    unsigned char owner;
    unsigned char unknown1[0x64 - 0x4D];
    unsigned short type;
    unsigned char unknown2[0xC0 - 0x66];
    unsigned int occupied;
    unsigned char unknown3[0xDC - 0xC4];
    unsigned int status;
} Sub00440930View;
typedef char Sub00440930WidthCheck[sizeof(unsigned int) == 4 ? 1 : -1];

int SC_FASTCALL sub_00440930(const Sub00440930View *unit,
                             const Sub00440930View *target)
{
    unsigned int flags;
    if (((const unsigned char *)0x00664080u)[unit->type * 4u] & 8u) {
        flags = unit->status;
        if ((flags & 1u) && !(flags & 16u) && !(flags & 0x40000000u)
            && !unit->occupied) {
            if (target->type != 0xD7 || target->owner != unit->owner)
                return 1;
        }
    }
    return 0;
}
