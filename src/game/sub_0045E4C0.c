typedef unsigned int U32;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
extern U32 data_006D5CA8;
extern int STDCALL sub_004100E8(U32 handle,U32 argument,U32 *changed);
#pragma code_seg(".scmatch")
static NOINLINE int STDCALL sub_0045E4C0(U32 handle,U32 *changed,U32 argument)
{
    U32 state=*(U32 *)0x00515224;
    if (!state) return 0;
    if (state!=2 && !data_006D5CA8) return 1;
    if (!sub_004100E8(handle,argument,changed)) return 0;
    if (data_006D5CA8 && changed && *changed) --data_006D5CA8;
    return 1;
}
#pragma code_seg(".scctx")
int context_0045E4C0(U32 handle,U32 *changed,U32 argument)
{ return sub_0045E4C0(handle,changed,argument); }
#pragma code_seg()
