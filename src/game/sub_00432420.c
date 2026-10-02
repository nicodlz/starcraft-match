#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
struct View00432420 {
    unsigned char unknown[0x4c];
    unsigned char field4c;
};
typedef char View00432420_size[(sizeof(struct View00432420)==0x4d)?1:-1];
unsigned int SC_FASTCALL sub_00432420(const struct View00432420 *unit,
                                     unsigned int value)
{
    return unit->field4c==value;
}
