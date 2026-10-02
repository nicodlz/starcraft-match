#if defined(_MSC_VER)
#define SUB0048EBC0_STDCALL __stdcall
#elif defined(__i386__)
#define SUB0048EBC0_STDCALL __attribute__((stdcall))
#else
#define SUB0048EBC0_STDCALL
#endif
typedef unsigned int U32;
typedef unsigned char Byte;
extern Byte data_006D5BBD;
extern U32 data_0064086C, data_006D5BAC, data_006D5BB4;
extern U32 SUB0048EBC0_STDCALL sub_00410268(U32,int,U32);
#pragma code_seg(".scmatch")
void sub_0048EBC0(void)
{
 Byte prior=data_006D5BBD;
 data_0064086C=1;
 if(!prior) {
  U32 object=data_006D5BAC;
  data_006D5BBD=1;
  if(object) {
   int level=(int)(data_006D5BB4-750U);
   if(level < -10000) level=-10000;
   sub_00410268(object,level,0);
  }
 }
}
#pragma code_seg()
