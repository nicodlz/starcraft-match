typedef unsigned int u32;
#if defined(_MSC_VER)
#define SC __stdcall
#define NI __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define NI __attribute__((noinline))
#endif
extern u32 SC sub_0041008E(char *destination,const char *source,u32 capacity);
typedef u32 (SC *GetError)(void);
typedef int (SC *Create)(const char *,void *);
typedef u32 (SC *Attributes)(const char *);
#pragma code_seg(".scmatch")
static NI int sub_0041EAB0(const char *path)
{
    char buffer[264];
    const char *cursor;
    GetError error;
    u32 count,value;
    if (!path) return 0;
    cursor=path;
    if (*cursor) {
    error=*(GetError *)0x004FE214;
    do {
        while (*cursor && *cursor!='\\') ++cursor;
        count=(u32)(cursor-path)+2;
        if (count>=0x105U) count=0x105U;
        value=sub_0041008E(buffer,path,count);
        if (value>=0x104U) return 0;
        if ((*(Create *)0x004FE1B8)(buffer,(void *)0)) {
            if (!*cursor) return 1;
        } else {
            value=error();
            if (value!=183 && value!=5) return 0;
            value=(*(Attributes *)0x004FE120)(buffer);
            if (value==0xffffffffU || !(value&16)) return 0;
        }
        ++cursor;
    } while(*cursor);
    }
    return 1;
}
#pragma code_seg(".scctx")
int hypothetical_context(const char *path) { return sub_0041EAB0(path); }
