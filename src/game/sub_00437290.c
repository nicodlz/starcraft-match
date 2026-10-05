/* Decode the reviewed path reference; preserve quotient narrowing and unsigned limit comparison. */
typedef unsigned int u32;
typedef unsigned char u8;
u32 __fastcall sub_00437290(u32 id) {
    u8 pool;
    u32 index;
    unsigned char *base;
    if (!id) return 0;
    pool = (u8)(id / 2500u);
    index = id - pool * 2500u;
    if (pool >= 8) return 0;
    base = ((unsigned char **)0x0069A604u)[pool];
    if (!base || !index || index > (u32)**(short **)0x006D5BFCu) return 0;
    return (u32)(base + index * 52 - 52);
}
