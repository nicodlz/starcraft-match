typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char Byte;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern void sub_004215D0(const char *format,...);
#pragma code_seg(".scmatch")
static NOINLINE void sub_004D6640(Byte *output,U32 script)
{
    Byte *base=*(Byte **)0x006D1200;
    U16 *record=(U16 *)(base+*(U32 *)base);
    U16 id=record[0];
    if ((U32)id!=script) {
        do {
            if(id==0xFFFFu) sub_004215D0((const char *)0x00501F08,(int)script);
            record+=2;
            id=record[0];
        } while((U32)id!=script);
    }
    *(U16 *)(output+0x10)=record[1];
}
#pragma code_seg(".scctx")
void context_004D6640(Byte *output,U32 script) {sub_004D6640(output,script);}
#pragma code_seg()
