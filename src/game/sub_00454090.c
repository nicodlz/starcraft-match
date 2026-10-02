/* Two observed WORD identifiers; semantic names remain annotations. */
#if defined(_MSC_VER)
#define SUB00454090_FASTCALL __fastcall
#elif defined(__i386__)
#define SUB00454090_FASTCALL __attribute__((fastcall))
#else
#define SUB00454090_FASTCALL
#endif

typedef struct {
    unsigned char opaque[0x64];
    unsigned short field_64;
} Sub00454090View;
typedef char Sub00454090ViewSize[(sizeof(Sub00454090View) == 0x66) ? 1 : -1];

int SUB00454090_FASTCALL sub_00454090(const Sub00454090View *object)
{
    unsigned short value = object->field_64;
    return value == 2 || value == 0x13;
}
