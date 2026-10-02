#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
typedef struct { unsigned char a[8]; unsigned short key; unsigned char b[2]; unsigned short type; } View;
#if defined(_MSC_VER)
#define SC_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define SC_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
typedef char sc_key_offset[(SC_OFFSET(View, key) == 8) ? 1 : -1];
typedef char sc_type_offset[(SC_OFFSET(View, type) == 12) ? 1 : -1];

void SC_FASTCALL sub_004D4410(const View *p) {
    if(p->type!=15u || p->key==27u || p->key==13u || p->key==32u)
        *(volatile unsigned int *)0x005967f0u=1u;
}
