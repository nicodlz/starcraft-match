typedef unsigned int U32;
extern __declspec(dllimport) U32 __stdcall GetModuleFileNameA(void *module,char *output,U32 capacity);
extern char *sub_0040C530(const char *text,int character);
extern U32 __stdcall sub_0041007C(char *output,const char *text,U32 capacity);
extern char data_00503EA8[],data_00500BC4[],data_00500BCC[];
extern unsigned char data_0057F0B4;
#pragma code_seg(".scmatch")
static __declspec(noinline) void __stdcall sub_004A8790(char *output,U32 capacity,const char *suffix)
{
 char *last;
 if(!GetModuleFileNameA(0,output,capacity)) *output=0;
 last=sub_0040C530(output,0x5c);
 if(last) last[1]=0;
 sub_0041007C(output,data_00503EA8,capacity);
 sub_0041007C(output,suffix,capacity);
 sub_0041007C(output,data_0057F0B4?data_00500BC4:data_00500BCC,capacity);
}
#pragma code_seg()
#pragma code_seg(".scctx")
void context_004A8790(char *output,U32 capacity,const char *suffix){sub_004A8790(output,capacity,suffix);}
#pragma code_seg()
