#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
union Dimensions { u32 packed; struct { short width, height; } pair; };
typedef char dimensions_size_4[sizeof(union Dimensions) == 4 ? 1 : -1];
int FASTCALL sub_00487A90(u8 *object, u16 kind)
{
    u16 id = *(u16 *)(object + 0x64);
    union Dimensions dimensions;
    u8 *sprite;
    int extent;
    dimensions.packed = *(u32 *)(0x00662860 + (u32)id * 4);
    if (id == kind) {
        sprite = *(u8 **)(object + 0x0C);
        extent = dimensions.pair.width;
        if ((u32)(extent / 2 + *(short *)(sprite + 0x14) -
                  *(short *)0x006509CC) < (u32)extent) {
            extent = dimensions.pair.height;
            {
                int y = extent / 2;
                y += *(volatile short *)(sprite + 0x16);
                y -= *(volatile short *)0x006509CE;
                if ((u32)y < (u32)extent)
                    return 1;
            }
        }
    }
    return 0;
}
