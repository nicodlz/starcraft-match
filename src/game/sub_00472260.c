typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int __cdecl sub_0040A069(int ch);
#pragma code_seg(".parse")
static __declspec(noinline) char *__stdcall sub_00472260(u32 fallback,char *text,u32 *output)
{
 char ch;
 if(!text){*output=fallback;return 0;}
 if(*text==','){*output=fallback;return text+1;}
 *output=0;
 ch=*text;
 for(;;){
  if(ch==',')return text+1;
  ++text;ch=(char)sub_0040A069((int)ch);
  if(ch<'0'||ch>'9'){
   if(ch<'a'||ch>'f')return 0;
   ch-=87;
  }else ch-=48;
  *output=(*output<<4)+(int)ch;
  ch=*text;
 }
}
#pragma code_seg(".context")
char *__stdcall context_00472260(u32 fallback,char *text,u32 *output){return sub_00472260(fallback,text,output);}
