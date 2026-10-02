typedef unsigned char u8;
typedef unsigned short u16;
static __forceinline u8 *find_004AAFF0(const u8 *input)
{
    u8 *p = *(u8 **)0x0051A270;
    u8 first;
    if ((long)p <= 0) return 0;
    first = input[12];
    do {
        if (p[72] == first && p[73] == input[13] && *(u16 *)(p + 74) == *(const u16 *)(input + 14))
            return p + 72;
        p = *(u8 **)(p + 4);
        if ((long)p <= 0) return 0;
    } while (p);
    return 0;
}
int __fastcall sub_004AAFF0(const u8 *input)
{
    u8 *p = find_004AAFF0(input);
    if (!p) return 0;
    return !p[16] || p[16] <= input[9];
}
