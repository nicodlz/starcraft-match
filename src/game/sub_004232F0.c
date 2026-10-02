#if defined(_MSC_VER)
#define FASTCALL __fastcall
#pragma code_seg(".scmatch")
#else
#define FASTCALL __attribute__((fastcall))
#endif
extern void FASTCALL sub_00485BD0(const unsigned char *, unsigned);
void sub_004232F0(void)
{
    unsigned char command=0x33;
    sub_00485BD0(&command,1);
}
