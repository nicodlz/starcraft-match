/* Independent C from reviewed pinned region; external helper is not defined. */
#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#pragma code_seg(".scmatch")
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
extern void SC_FASTCALL sub_00485BD0(const unsigned char *data,unsigned int length);
void sub_00423430(void)
{
 unsigned char command=0x18;
 sub_00485BD0(&command,1);
}
