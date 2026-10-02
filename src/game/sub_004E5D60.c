typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
static __declspec(noinline) void sub_004E5D60(u8 *p,u16 value)
{
    if ((*(u32 *)(p+0xdc)&0x400) || p[0x117] || p[0x119] || p[0x124]) {
        u16 index=*(u16 *)(p+0x64);
        if (!(((u8 *)0x664080)[index*4]&1) && value!=228) return;
    }
    *(u16 *)(p+0x94)=value;
}
void isolated_caller(u8 *p,u16 value) {sub_004E5D60(p,value);}
