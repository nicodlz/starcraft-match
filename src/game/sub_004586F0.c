typedef unsigned int U32;
#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
extern U32 value_006D5CB0;
extern U32 value_006D5CB8;
extern int SC sub_00410070(U32,U32,U32,U32);
#pragma code_seg(".scmatch")
void sub_004586F0(void)
{
    if(value_006D5CB0) {
        sub_00410070(value_006D5CB0,0,0,0);
        value_006D5CB0=0;
    }
    if(value_006D5CB8) {
        sub_00410070(value_006D5CB8,0,0,0);
        value_006D5CB8=0;
    }
}
#pragma code_seg()
