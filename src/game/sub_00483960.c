typedef unsigned short u16;
typedef unsigned long u32;
static __declspec(noinline) void __stdcall sub_00483960(int y, int x, unsigned char *grid, short *out, u16 value)
{
    int vertical = 1, horizontal = 1, corner = 1;
    int origin_x, origin_y;
    int limit_x, limit_y;
    int count, width, height, maximum, bound;
    u16 *p;
    out[1] = (short)y;
    out[0] = (short)x;
    bound = *(u16 *)0x0057F1D4;
    origin_x = (short)x;
    origin_y = (short)y;
    limit_x = origin_x + 8;
    if (limit_x > bound) limit_x = bound;
    bound = *(u16 *)0x0057F1D6;
    limit_y = origin_y + 7;
    if (limit_y > bound) limit_y = bound;
    ++x;
    ++y;
    while (x < limit_x && y < limit_y && (vertical || horizontal)) {
        if (vertical) {
            p = (u16 *)(grid + ((origin_y << 8) + x) * 2 + 12);
            count = y - origin_y;
            while (count > 0) {
                if (*p != value) { vertical = 0; break; }
                --count;
                p += 256;
            }
        }
        if (horizontal) {
            p = (u16 *)(grid + ((y << 8) + origin_x) * 2 + 12);
            count = x - origin_x;
            while (count > 0) {
                if (*p != value) { horizontal = 0; break; }
                --count;
                ++p;
            }
        }
        if (*(u16 *)(grid + ((y << 8) + x) * 2 + 12) != value) corner = 0;
        if (corner) {
            if (horizontal) ++y;
            if (vertical) ++x;
        } else {
            if (horizontal) ++y;
            else if (vertical) ++x;
        }
    }
    out[2] = (short)x;
    out[3] = (short)y;
    width = (int)(short)x - out[0];
    height = (int)(short)y - out[1];
    if (width > height) {
        maximum = (long)((u32)(height * 3) << 16) / 65536;
        if (width > maximum) width = maximum;
    } else {
        maximum = (long)((u32)(width * 3) << 16) / 65536;
        if (height > maximum) height = maximum;
    }
    out[2] = (short)(out[0] + width);
    out[3] = (short)(out[1] + height);
}
void __stdcall context_00483960(int y, int x, unsigned char *grid, short *out, u16 value)
{
    sub_00483960(y, x, grid, out, value);
}
