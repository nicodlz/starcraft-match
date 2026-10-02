#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
typedef struct View {
    unsigned char a[0x64];
    unsigned short type;
    unsigned char b[0x29];
    unsigned char count;
    unsigned char c[0x30];
    struct View *next;
} View;
/* Only the three observed offsets are modeled. */
#if defined(_MSC_VER)
#define SC_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define SC_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
typedef char sc_type_offset[(SC_OFFSET(View, type) == 0x64) ? 1 : -1];
typedef char sc_count_offset[(SC_OFFSET(View, count) == 0x8f) ? 1 : -1];
typedef char sc_next_offset[(SC_OFFSET(View, next) == 0xc0) ? 1 : -1];

void SC_FASTCALL sub_004759C0(View *p) {
    do {
        unsigned char count=p->count;
        if(count<255u) {
            ++count;
            p->count=count;
        }
        if(p->type!=0x49u) return;
        p=p->next;
    } while(p);
}
