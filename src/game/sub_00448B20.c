#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int u32;
typedef void *(__stdcall *Active)(void);
typedef void *(__stdcall *Send)(void *,u32,u32,u32);
typedef int (__stdcall *GetObject)(void *,int,void *);
typedef int (__stdcall *Scale)(int,int,int);
typedef void *(__stdcall *Create)(void *);
void *__cdecl memset(void *,int,unsigned int);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memset)
#endif
typedef struct { int height; unsigned char pad[12]; int weight; unsigned char flags[8]; char face[32]; } View;
typedef struct {int number; const char *text;} Table;
typedef char view_size_is_60[sizeof(View)==60 ? 1 : -1];
typedef char table_size_is_8[sizeof(Table)==8 ? 1 : -1];
static NOINLINE void *__cdecl sub_00448B20(void *window,u32 index)
{
 View local; void *font; const char *name; char *dst;
 if(!window) { window=(*(Active *)0x004fe35c)(); if(!window) return 0; }
 font=(*(Send *)0x004fe358)(window,0x31,0,0);
 if(!font) return 0;
 memset(&local,0,sizeof(local));
 if(!(*(GetObject *)0x004fe060)(font,60,&local)) return 0;
 local.height=(int)(0u-(u32)(*(Scale *)0x004fe180)(((Table *)0x0051aea4)[index].number,0x60,0x48));
 name=((Table *)0x0051aea4)[index].text;
 local.weight=700;
 dst=local.face;
 while((*dst++=*name++)!=0) {}
 return (*(Create *)0x004fe048)(&local);
}
void * __stdcall hypothetical_context(void *w,u32 i) { void *result=sub_00448B20(w,i); return result; }
