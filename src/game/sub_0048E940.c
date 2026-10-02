/* Independent game-wrapper scaffold. Runtime random generator is not reconstructed. */
typedef unsigned int u32;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern int sub_0040C7BD(void);
#pragma code_seg(".scmatch")
static NOINLINE int sub_0048E940(int lower,int upper)
{
    int result;
    if(lower==upper) {
        *(int *)0x006D5BE0=lower;
        return lower;
    }
    result=(int)((u32)((sub_0040C7BD()>>8) % (int)((u32)upper-(u32)lower+1u))+(u32)lower);
    if(result==*(int *)0x006D5BE0) {
        result=(int)((u32)result+1u);
        if(result>upper) result=lower;
    }
    *(int *)0x006D5BE0=result;
    return result;
}
#pragma code_seg(".scctx")
int hypothetical_context(int lower,int upper) { return sub_0048E940(lower,upper); }
