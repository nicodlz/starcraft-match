/* WORD kind and DWORD flags observed in the callback. */
#if defined(_MSC_VER)
#define SUB00417E30_FASTCALL __fastcall
#elif defined(__i386__)
#define SUB00417E30_FASTCALL __attribute__((fastcall))
#else
#define SUB00417E30_FASTCALL
#endif

typedef struct {
    unsigned char opaque[0x18];
    unsigned int flags_18;
    unsigned char opaque_1c[6];
    unsigned short kind_22;
} Sub00417E30View;
typedef char Sub00417E30DwordWidth[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char Sub00417E30ViewSize[(sizeof(Sub00417E30View) == 0x24) ? 1 : -1];

int SUB00417E30_FASTCALL sub_00417E30(const Sub00417E30View *object)
{
    if (object->kind_22 != 8) return 0;
    return (object->flags_18 & 0x1au) == 0x18u;
}
