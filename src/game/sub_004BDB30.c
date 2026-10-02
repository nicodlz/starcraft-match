typedef unsigned char u8;
typedef unsigned long u32;
u32 __fastcall sub_004BDB30(const u8 *palette, u32 unused, u32 color)
{
    u32 best = 0xFFFFFFFFUL;
    u32 result = 0;
    int i;
    u8 *mask = *(u8 **)0x006D125C;
    (void)unused;
    for (i=1, palette += 4; i<256; ++i, palette += 4) {
        if (!mask[i]) {
            int r = (int)((u8 *)&color)[0] - palette[0];
            int g = (int)((u8 *)&color)[1] - palette[1];
            int b = (int)((u8 *)&color)[2] - palette[2];
            u32 distance = b*b + g*g + r*r;
            if (distance < best) { result = i; best = distance; }
        }
    }
    return result;
}
