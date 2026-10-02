#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef int (STDCALL *Dialog)(u32,const char *,u32,u32,int);
extern void sub_004215D0(const char *format,...);
#pragma code_seg(".scmatch")
int sub_00421360(void)
{
 int result = (*(Dialog *)0x004FE318)(*(u32 *)0x006D5DE4,(const char *)111,
                 *(u32 *)0x0051BFB0,0x00420980,0);
 if (result == -1) sub_004215D0((const char *)0x00505D74,111);
 return result == 1;
}

#pragma code_seg()
