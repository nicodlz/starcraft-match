typedef unsigned int U32;
typedef unsigned char U8;
extern U32 sub_004117DE(void *destination,U32 item_size,U32 count,void *stream);
extern int __stdcall sub_004C3280(void *destination,U32 size,void *stream);
extern U32 data_00596BB4;
#pragma code_seg(".scmatch")
static __declspec(noinline) int __stdcall sub_004CF0F0(U8 *output,void *stream)
{
 U8 temporary[184];
 U32 marker;
 if(!output)output=temporary;
 if(sub_004117DE(&marker,4,1,stream)!=1)return 0;
 if((marker&0xffff0000u)!=0x00690000u)return 0;
 if(!sub_004C3280(output,181,stream))return 0;
 data_00596BB4=*(U32 *)(output+4);
 return 1;
}
#pragma code_seg()

#pragma code_seg(".scctx")
int context_004CF0F0(U8 *output,void *stream){return sub_004CF0F0(output,stream);}
#pragma code_seg()
