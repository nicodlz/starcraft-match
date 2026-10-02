typedef unsigned long u32;
#if defined(_MSC_VER)
#define FC __fastcall
#else
#define FC __attribute__((fastcall))
#endif
extern int __cdecl sub_00409CBE(const char *,const char *);
#pragma code_seg(".scmatch")
void FC sub_0044D540(const char *name,const char *text,u32 ignored)
{
    int index;
    const char **record=(const char **)0x00500F60;
    if (!*(unsigned char *)0x0058F440) record=(const char **)0x00500E40;
    index=0;
    do {
        if (!sub_00409CBE(name,*record)) break;
        ++index;
        record+=4;
    } while(index<18);
    if(index!=18) {
        if (*text) { ((const char **)0x006D5D00)[index]=text; return; }
        ((const char **)0x006D5D00)[index]=(const char *)0x00504FD4;
    }
}
#pragma code_seg()
