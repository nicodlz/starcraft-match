/* Independent dialog/error wrapper. Error-report dependency remains external. */
typedef unsigned int u32;
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef int (STDCALL *Dialog)(u32,const char *,u32,u32,int);
extern void sub_004215D0(const char *,...);
#pragma code_seg(".scmatch")
int sub_004213A0(void)
{
    int result;
    result=(*(Dialog *)0x004FE318)(*(u32 *)0x006D5DE4,(const char *)0x6D,*(u32 *)0x0051BFB0,0x00420980,0);
    if(result==-1) sub_004215D0((const char *)0x00505D74,0x6D);
    return result==1;
}
