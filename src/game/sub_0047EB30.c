typedef unsigned char u8;
typedef unsigned long u32;
typedef int (__stdcall *cursor_fn)(int, int);
void sub_0047EB30(void)
{
    if (*(u8 *)0x00658AC0) {
        *(u8 *)0x00658AC0 = 0;
        (*(cursor_fn *)0x004FE2CC)(320, 200);
        *(volatile u32 *)0x006CDDC4 = 320;
        *(volatile u32 *)0x006CDDC8 = 200;
    }
}
