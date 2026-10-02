typedef unsigned char u8;
typedef unsigned short u16;
static u8 *find_node(u8 *p,u16 value)
{
    u8 *n;
    if (*(u16 *)(p+0x22)) p=*(u8 **)(p+0x32);
    n=*(u8 **)(p+0x42);
    while(n) {
        if (*(u16 *)(n+0x20)==value) return n;
        n=*(u8 **)n;
    }
    return 0;
}
void __fastcall sub_00460A90(u8 *p)
{
    u8 *n=find_node(p,1);
    *(int *)0x6cdfe0=*(short *)(n+0x3a);
    n=find_node(p,2);
    *(int *)0x6cdfe4=*(short *)(n+0x3a);
}
