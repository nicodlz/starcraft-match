typedef unsigned int u32;
/* Reviewed base binding; unsigned subtraction intentionally wraps. */
extern unsigned char g_0069F468[];
#pragma code_seg(".index")
u32 __fastcall sub_00432180(u32 value) {
    if (!value) return 0;
    return (value - (u32)g_0069F468) / 44u + 1u;
}
