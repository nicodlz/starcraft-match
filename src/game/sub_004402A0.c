/* Independently observed WORD equality callback. */
#if defined(_MSC_VER)
#define SUB004402A0_FASTCALL __fastcall
#elif defined(__i386__)
#define SUB004402A0_FASTCALL __attribute__((fastcall))
#else
#define SUB004402A0_FASTCALL
#endif

typedef struct {
    unsigned char opaque[0x64];
    unsigned short field_64;
} Sub004402A0View;
typedef char Sub004402A0WordWidth[(sizeof(unsigned short) == 2) ? 1 : -1];
typedef char Sub004402A0ViewSize[(sizeof(Sub004402A0View) == 0x66) ? 1 : -1];

int SUB004402A0_FASTCALL
sub_004402A0(const Sub004402A0View *object, unsigned short value)
{
    return object->field_64 == value;
}
