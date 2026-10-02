/* Independent C, byte angle wrap and signed speed limits preserved. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
int FASTCALL sub_00494FE0(u8 *p)
{
    u8 flags=p[0x20];
    s8 delta;
    u8 current;
    s8 speed;
    u16 kind;
    int wide;
    if ((flags&2) && !(flags&1)) return 0;
    delta=(s8)(p[0x4B]-p[0x21]);
    current=p[0x21];
    wide=delta;
    if (wide>=128 || delta<=-128) delta=(s8)-128;
    speed=(s8)p[0x22];
    if (delta>speed) {
        delta=speed;
        p[0x21]=(u8)(delta+current);
    } else {
        if (delta< -(int)speed) current=(u8)(current-speed);
        else current=(u8)(current+delta);
        p[0x21]=current;
    }
    kind=*(u16 *)(p+0x24);
    if ((kind>=0x8D && kind<=0xAB) || (kind>=0xC9 && kind<=0xCE)) p[0x22]=(u8)(speed+1);
    if (p[0x23]==p[0x4B] && p[0x21]==p[0x4B]) p[0x20]=(u8)(flags&0xFE);
    return 1;
}
