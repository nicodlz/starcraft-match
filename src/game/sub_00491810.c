#if defined(_MSC_VER) && !defined(__clang__)
#define SC_NOINLINE __declspec(noinline)
#define SC_EAX_ARG
#else
#define SC_NOINLINE __attribute__((noinline))
#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif
#endif
typedef struct {
    unsigned char a[0x112];
    unsigned short field112;
    unsigned char b[2];
    unsigned char field116,field117,field118,field119,field11A;
    unsigned char c[9];
    unsigned char field124;
    unsigned char d;
    unsigned char field126;
} View;
#if defined(_MSC_VER) && !defined(__clang__)
#define SC_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define SC_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
typedef char offset_field112[(SC_OFFSET(View, field112) == 0x112) ? 1 : -1];
typedef char offset_field116[(SC_OFFSET(View, field116) == 0x116) ? 1 : -1];
typedef char offset_field117[(SC_OFFSET(View, field117) == 0x117) ? 1 : -1];
typedef char offset_field118[(SC_OFFSET(View, field118) == 0x118) ? 1 : -1];
typedef char offset_field119[(SC_OFFSET(View, field119) == 0x119) ? 1 : -1];
typedef char offset_field11A[(SC_OFFSET(View, field11A) == 0x11a) ? 1 : -1];
typedef char offset_field124[(SC_OFFSET(View, field124) == 0x124) ? 1 : -1];
typedef char offset_field126[(SC_OFFSET(View, field126) == 0x126) ? 1 : -1];

static SC_NOINLINE SC_EAX_ARG unsigned int sub_00491810(const View *p) {
    return p->field112 || p->field117 || p->field124 || p->field118 || p->field116 || p->field119 || p->field11A || p->field126;
}
/* Independent C compiler context, not a reconstructed function. */
unsigned int source_context_00491810(const View *p) { return sub_00491810(p); }
