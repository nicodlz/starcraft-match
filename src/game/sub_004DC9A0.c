#if defined(_MSC_VER)
#define SUB004DC9A0_CDECL __cdecl
#define SUB004DC9A0_NOINLINE __declspec(noinline)
#elif defined(__i386__)
#define SUB004DC9A0_CDECL __attribute__((cdecl))
#define SUB004DC9A0_NOINLINE __attribute__((noinline))
#else
#define SUB004DC9A0_CDECL
#define SUB004DC9A0_NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32;
U32 SUB004DC9A0_CDECL strlen(const char *);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(strlen)
#endif
extern void *SUB004DC9A0_CDECL sub_00408FD0(void *, const void *, U32);
#pragma code_seg(".scmatch")
static SUB004DC9A0_NOINLINE void sub_004DC9A0(char *text,U32 prefix)
{
 U32 remaining=strlen(text)-prefix+1U;
 sub_00408FD0(text,text+prefix,remaining);
 text[remaining]=0;
}
#pragma code_seg(".scctx")
void context_004DC9A0(char *text,U32 prefix) {sub_004DC9A0(text,prefix);}
#pragma code_seg()
