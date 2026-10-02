#if defined(_MSC_VER)
#define FC __fastcall
#define NI __declspec(noinline)
#else
#define FC __attribute__((fastcall))
#define NI __attribute__((noinline))
#endif
typedef unsigned long u32;
typedef unsigned short u16;
static NI void FC sub_00401FA0(u32 ignored,short *point,u16 id)
{
    u32 offset = (u32)id * 8;
    short limit = *(short *)(offset + 0x006617C8);
    short value = point[0];
    if (value < limit) point[0] = limit;
    else {
        u32 dimension = *(u32 *)0x00628450;
        int extent = *(volatile short *)(offset + 0x006617CC);
        if ((int)value >= (int)(u16)dimension - (int)extent)
            point[0] = (short)(dimension - *(volatile u16 *)(offset + 0x006617CC) - 1);
    }
    limit = *(short *)(offset + 0x006617CA);
    value = point[1];
    if (value < limit) point[1] = limit;
    else {
        short extent = *(short *)(offset + 0x006617CE);
        u32 dimension = *(u32 *)0x006284B4;
        if ((int)value >= (int)((u32)(u16)dimension - (int)extent - 32))
            point[1] = (short)(dimension - (u16)extent - 33);
    }
}
/* Hypothetical context only, not matched or counted. */
void context(short *point,u16 id) { sub_00401FA0(0,point,id); }
