#if defined(_MSC_VER)
#define STDCALL __stdcall
#define CDECL __cdecl
#else
#define STDCALL __attribute__((stdcall))
#define CDECL __attribute__((cdecl))
#endif
typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char U8;
extern U32 data_006D5C2C;
extern U16 data_00596904;
extern U32 data_006D11BC;
extern U8 data_0066FBF7;
extern void CDECL sub_004B89A0(void);
__declspec(dllimport) int STDCALL KillTimer(U32,U32);
#pragma code_seg(".scmatch")
U32 sub_00472D60(void)
{
 if(!data_006D5C2C) return 0;
 if(data_00596904==4 && data_006D11BC==3) sub_004B89A0();
 KillTimer(0,data_006D5C2C);
 data_006D5C2C=0;
 data_0066FBF7=0;
 return 1;
}
#pragma code_seg()
