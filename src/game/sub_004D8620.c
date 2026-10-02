#if defined(_MSC_VER)
#define SUB004D8620_CDECL __cdecl
#define SUB004D8620_NOINLINE __declspec(noinline)
#elif defined(__i386__)
#define SUB004D8620_CDECL __attribute__((cdecl))
#define SUB004D8620_NOINLINE __attribute__((noinline))
#else
#define SUB004D8620_CDECL
#define SUB004D8620_NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32;
extern U32 SUB004D8620_CDECL sub_0040C799(const char *, char **, int);
extern U32 data_0051CEB4;
#pragma code_seg(".scmatch")
static SUB004D8620_NOINLINE void sub_004D8620(char *text)
{
 char *cursor=text;
 char *end;
 U32 result;
 while(*cursor!='>') ++cursor;
 *cursor=0;
 result=sub_0040C799(text,&end,10);
 if(result) { *cursor='>'; data_0051CEB4=result; }
 else *cursor='>';
}
#pragma code_seg(".scctx")
void context_004D8620(char *text) {sub_004D8620(text);}
#pragma code_seg()
