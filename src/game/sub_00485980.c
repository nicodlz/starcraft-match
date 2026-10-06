typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#pragma code_seg(".strval")
static __declspec(noinline) int __stdcall sub_00485980(char *text,u32 maximum,u32 limit,u32 flags,u32 allow)
{
 int count=0;
 if(maximum>=limit)maximum=limit;
 while(maximum){
  char ch=*text;
  --maximum;++count;
  if(!ch)return count;
  if(!allow){switch(ch){
   case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:
   case 14:case 15:case 16:case 17:case 21:case 22:case 23:case 24:case 25:
   case 27:case 28:case 29:case 30:case 31:return 0;
  }}
  if(!flags && (u8)ch<32){switch(ch){
   case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:
   case 14:case 15:case 16:case 17:case 21:case 22:case 23:case 24:case 25:
   case 27:case 28:case 29:case 30:case 31:break;
   default:return 0;
  }}
  ++text;
 }
 return 0;
}
#pragma code_seg(".context")
int __stdcall context_00485980(char *text,u32 maximum,u32 limit,u32 flags,u32 allow){return sub_00485980(text,maximum,limit,flags,allow);}
