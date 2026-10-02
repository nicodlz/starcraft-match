/* Custom emitted EDI/ESI ABI selected by ordinary static C context.
 * MSVC i386 va_list is a byte pointer; Clang uses its builtin abstraction.
 * External formatter dependency reviewed for ABI only, not reconstructed. */
typedef unsigned int u32;
#ifdef _MSC_VER
#define NI __declspec(noinline)
typedef char *sc_va_list;
#define SC_VA_START(ap,last) ((ap)=(char *)&(last)+sizeof(last))
#define SC_VA_END(ap) ((ap)=(sc_va_list)0)
#else
#define NI __attribute__((noinline))
typedef __builtin_va_list sc_va_list;
#define SC_VA_START(ap,last) __builtin_va_start(ap,last)
#define SC_VA_END(ap) __builtin_va_end(ap)
#endif
extern int __cdecl sub_004115C3(char *,u32,const char *,void *);
#pragma code_seg(".scmatch")
static NI int __cdecl sub_0041F1B0(char *destination,u32 capacity,const char *format,...)
{
 sc_va_list args;
 int result;
 SC_VA_START(args,format);
 result=sub_004115C3(destination,capacity,format,args);
 SC_VA_END(args);
 destination[capacity-1u]=0;
 return result;
}
#pragma code_seg(".scctx")
int hypothetical_context(char *destination,u32 capacity,const char *format,u32 argument)
{
 return sub_0041F1B0(destination,capacity,format,argument);
}
