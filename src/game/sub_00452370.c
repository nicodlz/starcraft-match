#if defined(_MSC_VER)
#define NI __declspec(noinline)
#define SC __stdcall
#else
#define NI __attribute__((noinline))
#define SC __attribute__((stdcall))
#endif
typedef unsigned char u8;
typedef unsigned int u32;
extern u8 * SC dependency_0041006A(u32,const char *,u32,u32);
#pragma code_seg(".scmatch")
static NI int SC sub_00452370(u8 kind,u8 value)
{
    u8 *p;
    u8 result=kind;
    if ((u32)kind==*(u32 *)0x00512684) result=8;
    p=*(u8 **)0x006D5C7C;
    if (!p) {
        p=dependency_0041006A(3,(const char *)0x0050467C,637,0);
        *(u8 **)0x006D5C7C=p;
    }
    p[1]=result;
    p[0]=0x41;
    p[2]=value;
    return 1;
}
#pragma code_seg(".scctx")
int context(u8 kind,u8 value) { return sub_00452370(kind,value); }
