/* Reviewed rectangle query; byte equality remains an open expectation. */
#define SC_FINDER_COMPONENT 1
#pragma code_seg(".search")
#include "sub_00469B00.c"

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern u32 g_006BEE64, g_006BEE6C, g_006BEE68, g_006BB930;
extern u32 g_0066FF78[], g_006769B8[], g_006BD3D0[], g_006BEE70[];
extern u8 *g_006BB938[];
typedef struct Unit {u8 prefix[12]; short *sprite; u8 gap[84]; u16 type; u8 tail[234];} Unit;
typedef char sc_observed_unit_size[(sizeof(Unit) == 336) ? 1 : -1];
extern Unit g_0059CCA8[];
#define USED g_006BEE64
#define DEPTH g_006BEE6C
#define WIDTH g_006BEE68
#define HEIGHT g_006BB930
#define XARRAY g_0066FF78
#define YARRAY g_006769B8
#define MARKS g_006BD3D0
#pragma code_seg(".unused")
static __forceinline Unit *unit_at(u32 index) {
    if (!index) return 0;
    return &g_0059CCA8[index - 1];
}
#pragma code_seg(".query")
u8 **__stdcall sub_004308A0(u16 *rect)
{
    u8 **start, **out;
    int extend_x, extend_y;
    u16 right, bottom;
    int left, top, x0, x1, y0, y1;
    u32 i;
    g_006BEE70[DEPTH] = USED;
    start = g_006BB938 + USED;
    out = start;
    ++DEPTH;
    right = rect[2];
    bottom = rect[3];
    extend_x = 0;
    extend_y = 0;
    left = (short)rect[0];
    if ((int)(short)right - left + 1 < (int)(u16)WIDTH) {
        right = rect[0] + WIDTH - 1;
        extend_x = 1;
    }
    top = (short)rect[1];
    if ((int)(short)bottom - top + 1 < (int)(u16)HEIGHT) {
        bottom = rect[1] + HEIGHT - 1;
        extend_y = 1;
    }
    x0 = sub_00469B00(XARRAY,1,(u32)left);
    x1 = sub_00469B00(XARRAY,1,(u16)right);
    y0 = sub_00469B00(YARRAY,1,(u32)top);
    y1 = sub_00469B00(YARRAY,1,(u16)bottom);
    if ((int)((u32)x1 - (u32)x0) > 0 && (int)((u32)y1 - (u32)y0) > 0) {
        for (i = x0; (int)i < x1; ++i) {
            u32 id = XARRAY[i * 2];
            if (extend_x) {
                Unit *unit = unit_at(id);
                short *sprite = unit->sprite;
                u32 type = unit->type;
                if ((int)sprite[10] - ((short *)0x006617C8u)[type * 4] > (short)rect[2]) {
                    MARKS[id] = 0;
                    continue;
                }
            }
            MARKS[id] = 1;
        }
        for (i = y0; (int)i < y1; ++i) {
            u32 id = YARRAY[i * 2];
            if (extend_y) {
                Unit *unit = unit_at(id);
                short *sprite = unit->sprite;
                u32 type = unit->type;
                if ((int)sprite[11] - ((short *)0x006617CAu)[type * 4] > (short)rect[3]) continue;
            }
            if (MARKS[id] == 1) MARKS[id] = 3;
        }
        for (i = x0; (int)i < x1; ++i) {
            u32 id = XARRAY[i * 2];
            if (MARKS[id] == 3) *out++ = (u8 *)unit_at(id);
            MARKS[id] = 0;
        }
    }
    *out = 0;
    USED = (u32)((int)((u32)out - (u32)g_006BB938 + 4u) >> 2);
    return start;
}
