typedef unsigned int U32;
#if defined(_MSC_VER)
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
extern unsigned char data_00515818[],data_00515688[];
extern U32 __stdcall sub_0041023E(U32);
extern void *memset(void *,int,U32);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memset)
#endif
#pragma code_seg(".scmatch")
static NI void sub_004AD190(U32 *object)
{
 memset(object,0,92);
 object[0]=92; object[1]=1;
 object[2]=sub_0041023E(0);
 object[3]=0x004AC380; object[5]=0x0044CBE0; object[6]=0x00449F60;
 object[8]=0x00448EC0; object[9]=0x004AD0B0; object[4]=0x00449810;
 object[11]=0x004AC300; object[15]=0x0044E390; object[13]=0x004F4C00;
 object[17]=0x0044E150;
 object[16]=(U32)(*(unsigned char *)0x0058F440 ? data_00515818 : data_00515688);
 object[20]=0x004AB310; object[21]=0x00453C60; object[22]=0x0049A040;
}
#pragma code_seg(".scctx")
void context_004AD190(U32 *object) { sub_004AD190(object); }
