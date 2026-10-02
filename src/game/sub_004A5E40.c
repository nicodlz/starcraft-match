typedef unsigned int U32;
typedef unsigned char U8;
#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
extern U32 value_006D5BAC;
extern U8 flag_006D5BBC;
extern int SC sub_004101D8(U32);
extern int SC sub_004100B8(U32);
#pragma code_seg(".scmatch")
void sub_004A5E40(void)
{
    if(value_006D5BAC) {
        sub_004101D8(value_006D5BAC);
        sub_004100B8(value_006D5BAC);
        value_006D5BAC=0;
    }
    flag_006D5BBC=0;
}
#pragma code_seg()
