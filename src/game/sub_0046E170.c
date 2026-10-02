typedef unsigned short u16;
typedef unsigned int u32;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern u32 data_0066FF60;
extern u16 data_00660A70[];
extern const u16 data_00514178[];
extern void sub_0046E100(void);
#pragma code_seg(".scmatch")
static NOINLINE u16 sub_0046E170(u16 identifier)
{
    u32 offset;
    data_0066FF60=0;
    if(data_00660A70[identifier]==0xffffu) sub_0046E100();
    offset=data_00660A70[identifier];
    if(offset && data_00514178[offset]==0xff02u)
        return data_00514178[offset+1];
    return 0xe4u;
}
#pragma code_seg(".scctx")
u16 context_0046E170(u16 identifier) { return sub_0046E170(identifier); }
#pragma code_seg()
