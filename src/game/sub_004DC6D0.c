/* Independently authored callback for pinned Windows i386 imports. */
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef u32 (STDCALL *GetParentFn)(u32);
typedef u32 (STDCALL *GetProcessFn)(u32,u32 *);
typedef int (STDCALL *PostFn)(u32,u32,u32,u32);
int STDCALL sub_004DC6D0(u32 window,u32 process)
{
 u32 original=window;
 if((*(GetParentFn *)0x004FE328)(original)) {
  (*(GetProcessFn *)0x004FE334)(original,&window);
  if(window==process && original!=*(u32 *)0x0051BFB0)
   (*(PostFn *)0x004FE330)(original,16,0,0);
 }
 return 1;
}
