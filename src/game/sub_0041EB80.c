typedef unsigned int u32;
extern u32 __stdcall sub_0041005E(const char *path,u32 *handle);
extern int __stdcall sub_00410064(const char *path,u32 handle,u32 size,void *buffer);
extern int __stdcall sub_00410058(const void *buffer,const char *key,void **value,u32 *length);
typedef u32 (__stdcall *module_fn)(void *,char *,u32);
typedef void *(__stdcall *allocate_fn)(void *,u32,u32,u32);
typedef int (__stdcall *release_fn)(void *,u32,u32);
#if defined(__clang__)
#define clear_bytes __builtin_memset
#define copy_bytes __builtin_memcpy
#else
extern void *__cdecl memset(void *,int,unsigned int);
extern void *__cdecl memcpy(void *,const void *,unsigned int);
#pragma intrinsic(memset,memcpy)
#define clear_bytes memset
#define copy_bytes memcpy
#endif
#pragma code_seg(push,".scmatch")
void __stdcall sub_0041EB80(void *output)
{
 char path[260];void *value;u32 length,handle,size;void *buffer;
 clear_bytes(output,0,52);
 if((*(module_fn *)0x004FE22CU)((void *)0,path,260)){
  size=sub_0041005E(path,&handle);
  if(size){
   buffer=(*(allocate_fn *)0x004FE0A4U)((void *)0,size,0x1000,4);
   if(sub_00410064(path,0,size,buffer)){
    if(sub_00410058(buffer,(const char *)0x005016CCU,&value,&length)){
     u32 amount=length;
     if(amount>=52)amount=52;
     copy_bytes(output,value,amount);
    }
   }
   (*(release_fn *)0x004FE1B0U)(buffer,0,0x8000);
  }
 }
}
#pragma code_seg(pop)
