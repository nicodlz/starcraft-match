/* Independently authored C wrapper; outgoing dependency remains external. */
typedef unsigned int u32;
#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
extern void FASTCALL sub_00485BD0(const unsigned char *, u32);
#pragma code_seg(".scmatch")
void sub_004C0420(void)
{
    if (*(volatile u32 *)0x006509C4) {
        unsigned char command = 0x11;
        sub_00485BD0(&command, 1);
    }
}
#pragma code_seg()
