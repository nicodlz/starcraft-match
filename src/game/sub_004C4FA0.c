typedef unsigned long U32;
typedef unsigned short U16;
typedef unsigned char U8;
#define D(a) (*(volatile U32*)(a))
#define W(a) (*(volatile U16*)(a))
#define B(a) (*(volatile U8*)(a))
extern volatile U32 data_005971E4[8];
extern void __stdcall sub_004C4A80(U32 index,U32 value);
extern void __stdcall sub_004C4D60(U32 index,U32 zero,U32 value);
#pragma code_seg(".scmatch")
void sub_004C4FA0(void)
{
 U32 index,value;U16 mode;
 if(!B(0x57f0b4))return;
 for(index=0;index<8;++index){
  value=data_005971E4[index];
  if(value){
   mode=W(0x596904);
   if(mode==4)sub_004C4A80(index,value);
   else if(mode==3)sub_004C4D60(index,0,value);
   data_005971E4[index]=0;
  }
 }
}
