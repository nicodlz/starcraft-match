#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
typedef struct { unsigned char a[0x4c]; unsigned char owner; unsigned char b[0x17]; unsigned short type; unsigned char c[0x76]; unsigned char flags; } View;
unsigned int SC_FAST sub_00468930(const View *v, unsigned int unused, const View *other) {
(void)unused;
return (v->flags & 1u) && (v->type == 0x6eu || v->type == 0x9du || v->type == 0x95u) && v->owner == other->owner;
}
