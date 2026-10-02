typedef unsigned char u8;
typedef unsigned int u32;
extern void __fastcall sub_00485BD0(const u8 *message, u32 length);
#pragma code_seg(".scmatch")
void sub_004C0450(void)
{
    if (*(volatile const u32 *)0x006509C4 == 0) {
        u8 message = 0x10;
        sub_00485BD0(&message, 1);
    }
}
