/* Independently reconstructed from the reviewed pinned PE region. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SUB004916E0_FAST __fastcall
#else
#define SUB004916E0_FAST __attribute__((fastcall))
#endif

typedef struct Sub004916E0View {
    unsigned char reserved_00[0x96];
    unsigned char field_96;
    unsigned char reserved_97[0x45];
    unsigned int field_dc;
    unsigned char reserved_e0[0x10];
    struct Sub004916E0View *field_f0;
    struct Sub004916E0View *field_f4;
} Sub004916E0View;

unsigned int SUB004916E0_FAST sub_004916E0(Sub004916E0View *object)
{
    if (object->field_96)
        return 0;
    {
        unsigned int changed = 0;
        unsigned int result = 1;
        if (*(Sub004916E0View **)0x0063FF5C == object) {
            *(Sub004916E0View **)0x0063FF5C = object->field_f4;
            changed = result;
        }
        if (object->field_f0) {
            object->field_f0->field_f4 = object->field_f4;
            changed = result;
        }
        if (object->field_f4) {
            object->field_f4->field_f0 = object->field_f0;
            changed = result;
        }
        object->field_dc &= ~0x800u;
        object->field_f0 = 0;
        object->field_f4 = 0;
        if (changed) {
            *(unsigned int *)0x0068C1B0 = result;
            *(unsigned char *)0x0068AC74 = (unsigned char)result;
            *(unsigned char *)0x0068C1F8 = (unsigned char)result;
            *(unsigned int *)0x0068C1E8 = 0;
            *(unsigned int *)0x0068C1EC = 0;
        }
        return result;
    }
}
