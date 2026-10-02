typedef unsigned int U32;typedef signed short S16;
struct Entry {S16 value;unsigned short untouched;};
extern S16 data_005159A4;
extern struct Entry data_0050110C[];
extern const char data_00503794[],data_004FF894[];
extern int __stdcall sub_004100AC(const char *key,const char *name,U32 flags,char *buffer,U32 size);
extern const char *__stdcall sub_004DDD30(int identifier);
extern int __cdecl sub_00409CBE(const char *first,const char *second);
__declspec(dllimport) extern U32 __stdcall SendMessageA(void *window,U32 message,U32 wparam,U32 lparam);
#pragma code_seg(".scmatch")
void __stdcall sub_0044B0D0(void *window)
{
 char buffer[128];int i;
 sub_004100AC(data_004FF894,data_00503794,0,buffer,128);
 for(i=0;i<data_005159A4;++i){
  if(!sub_00409CBE(sub_004DDD30((int)data_0050110C[i].value),buffer)){
   SendMessageA(window,0x405,1,(U32)i);break;
  }
 }
}
#pragma code_seg()
