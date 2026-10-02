#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef char U32Width[(sizeof(u32)==4)?1:-1];
typedef int (STDCALL *Show)(void *,int);
/* Registered three-DWORD callback; first index is deliberately unused. */
int STDCALL sub_0044A5D0(u32 ignored,void *window,u32 show) {
 (void)ignored;
 return (*(Show *)0x004FE380)(window,show ? 5 : 0);
}
