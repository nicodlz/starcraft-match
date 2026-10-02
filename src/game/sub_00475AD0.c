#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#define SC_OFFSET(type,field) ((unsigned int)&(((type *)0)->field))
#else
#define SC_FASTCALL __attribute__((fastcall))
#define SC_OFFSET(type,field) __builtin_offsetof(type,field)
#endif
struct View00475AD0 {
    unsigned char a[0x64];
    unsigned short field64;
    unsigned char b[0x76];
    unsigned char fielddc;
};
typedef char View00475AD0_kind[(SC_OFFSET(struct View00475AD0,field64)==0x64)?1:-1];
typedef char View00475AD0_flags[(SC_OFFSET(struct View00475AD0,fielddc)==0xdc)?1:-1];
unsigned char SC_FASTCALL sub_00475AD0(const struct View00475AD0 *unit)
{
    unsigned short kind=unit->field64;
    if(kind==0x67 && !(unit->fielddc&0x10)) return 0x82;
    return *(volatile unsigned char *)(0x006636B8u+(unsigned int)kind);
}
