#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
/* External declaration only: observed ECX payload, EDX length, plain RET. */
extern void SC_FASTCALL sub_00485BD0(const unsigned char *,unsigned int);
#pragma code_seg(push, ".scmatch")
void sub_004232D0(void)
{
    unsigned char command = 0x34;
    sub_00485BD0(&command, 1);
}
#pragma code_seg(pop)
