typedef unsigned int u32;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern u32 sub_0040C799(const char *text,char **end,int radix);
#pragma code_seg(".scmatch")
static NOINLINE void sub_004D8660(char *text)
{
    char *cursor=text;
    char *end;
    u32 value;
    while (*cursor!='>') ++cursor;
    *cursor=0;
    value=sub_0040C799(text,&end,10);
    if(value) { *cursor='>'; *(unsigned char *)0x0051CEC8=(unsigned char)value; }
    else { *cursor='>'; }
}
#pragma code_seg(".scctx")
/* Ordinary compiler context, not counted or reconstructed. */
void context_004D8660(char *text) { sub_004D8660(text); }
