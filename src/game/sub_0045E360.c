typedef unsigned int U32;
#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
extern U32 data_0068AC7C;
extern U32 data_0068AC84;
extern void SC sub_00410070(U32 allocation,U32 file,U32 line,U32 flags);
#pragma code_seg(".scmatch")
void sub_0045E360(void)
{
    if(data_0068AC7C) {
        sub_00410070(data_0068AC7C,0,0,0);
        data_0068AC7C=0;
    }
    if(data_0068AC84) {
        sub_00410070(data_0068AC84,0,0,0);
        data_0068AC84=0;
    }
}
#pragma code_seg()
