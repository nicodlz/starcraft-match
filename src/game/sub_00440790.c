#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
typedef struct {
    unsigned char a[0x4c];
    unsigned char owner;
    unsigned char b[0xf];
    unsigned int presence;
    int value;
    unsigned short type;
} View;
#if defined(_MSC_VER)
#define SC_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define SC_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
typedef char sc_owner_offset[(SC_OFFSET(View, owner) == 0x4c) ? 1 : -1];
typedef char sc_presence_offset[(SC_OFFSET(View, presence) == 0x5c) ? 1 : -1];
typedef char sc_value_offset[(SC_OFFSET(View, value) == 0x60) ? 1 : -1];
typedef char sc_type_offset[(SC_OFFSET(View, type) == 0x64) ? 1 : -1];

unsigned int SC_FASTCALL sub_00440790(const View *p,const View *other) {
    unsigned short type;
    if(p->owner!=other->owner) return 0;
    if(!p->presence) return 0;
    type=p->type;
    if(type==0x48u || type==0x52u || type==0x53u || type==0x51u)
        return (p->value & (int)0xffffff00u)<=0xa00;
    return 0;
}
