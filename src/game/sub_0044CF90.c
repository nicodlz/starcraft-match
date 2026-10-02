typedef unsigned int U32;
#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
extern U32 data_0068F6DC;
extern U32 data_0068F6D8;
extern const char data_00504F0C[];
extern void SC sub_00410070(U32,const char *,U32,U32);
#pragma code_seg(".scmatch")
void sub_0044CF90(void)
{
    if(data_0068F6DC) {
        sub_00410070(data_0068F6DC,data_00504F0C,653,0);
        data_0068F6DC=0;
    }
    if(data_0068F6D8) {
        sub_00410070(data_0068F6D8,data_00504F0C,657,0);
        data_0068F6D8=0;
    }
}
#pragma code_seg()
