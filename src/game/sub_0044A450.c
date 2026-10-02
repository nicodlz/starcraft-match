typedef unsigned int u32;
typedef int (__stdcall *Send)(u32,u32,u32,void*);
#ifdef _MSC_VER
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
__declspec(dllimport) int __stdcall SendMessageA(u32,u32,u32,void*);
extern int __stdcall sub_00410226(const char*,const char*,u32,const char*);
#pragma code_seg(".scmatch")
static NI void sub_0044A450(u32 window)
{
 char text[32];
 Send send=SendMessageA;
 if(send(window,0x147,0,0)!=-1) {
  send(window,0x0d,32,text);
  sub_00410226((const char*)0x004ff894,(const char*)0x00503778,0,text);
 }
}
#pragma code_seg(".scctx")
void hypothetical_context(u32 window){sub_0044A450(window);}
