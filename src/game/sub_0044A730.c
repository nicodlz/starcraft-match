typedef unsigned int U32;
#ifdef _MSC_VER
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
extern void SC_STDCALL sub_00410070(U32 pointer,U32 label,U32 line,U32 flag);
#define D(a) (*(volatile U32 *)(a))
#pragma code_seg(".scmatch")
void sub_0044A730(void)
{
 U32 p;
 p=D(0x006D5D4C);if(p){sub_00410070(p,0x005053AC,239,0);D(0x006D5D4C)=0;}
 p=D(0x006D5D50);if(p){sub_00410070(p,0x005053AC,242,0);D(0x006D5D50)=0;}
 p=D(0x006D5D54);if(p){sub_00410070(p,0x005053AC,245,0);D(0x006D5D54)=0;}
 p=D(0x006D5D58);if(p){sub_00410070(p,0x005053AC,249,0);D(0x006D5D58)=0;}
}
#pragma code_seg()
