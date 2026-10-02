#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
typedef struct { unsigned char p00[0x64]; unsigned short value_64; } View;
unsigned int SC_FAST sub_00454070(const View *object) {
    unsigned short value = object->value_64;
    return value == 0x27u || value == 0x30u;
}
