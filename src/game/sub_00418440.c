#ifdef _MSC_VER
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
typedef unsigned int u32;
void FASTCALL sub_00418440(unsigned char *object)
{
    u32 flags = *(u32 *)(object+0x18);
    unsigned char *parent;
    unsigned char *selected;
    if (!(flags & 2u) && (flags & 8u)) {
        parent = *(unsigned char **)(object+0x32);
        selected = *(unsigned char **)(parent+0x3e);
        if (object == selected ||
            (*(unsigned short *)(object+0x22) == 1 && !selected &&
             !(*(u32 *)(parent+0x18) & 0x20000000u))) {
            *(u32 *)(object+0x18) = flags | 0x1000u;
            return;
        }
    }
    *(u32 *)(object+0x18) = flags & ~0x1000u;
}
