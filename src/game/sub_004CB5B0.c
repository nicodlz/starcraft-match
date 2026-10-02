typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
void *__cdecl memset(void *,int,unsigned int);
#pragma intrinsic(memset)
typedef struct input {u32 payload; u8 kind,a,b,c;} input;
typedef struct output {u8 flag,kind1,kind2,a,zero,b,pad6,pad7;u32 payload;u8 c,pad13,pad14,pad15;} output;
extern output data_006CE2A0[];
#pragma code_seg(".scfill")
static __forceinline void fill(u32 index,u8 kind,u32 payload,u8 a,u8 b,u8 c)
{
    output *q=data_006CE2A0+index;
    q->kind1=kind; q->kind2=kind; q->a=a; q->b=b;
    q->zero=0; q->payload=payload; q->c=c;
}
#pragma code_seg(".scmatch")
static __declspec(noinline) void sub_004CB5B0(input *p)
{
    u8 index;
    u32 mask=1;
    u16 *bits;
    memset(data_006CE2A0,0,128);
    index=0;
    if(p->kind) {
        bits=((u16 **)0x5127dc)[*(u16 *)0x57f1dc];
        do {
            output *q=data_006CE2A0+index;
            fill(index,p->kind,p->payload,p->a,p->b,p->c);
            if(mask & *bits) q->flag=1;
            ++index;
            ++p;
            mask<<=1;
        } while(p->kind);
    }
}
#pragma code_seg(".scctx")
void isolated_caller(input *p) {sub_004CB5B0(p);}
