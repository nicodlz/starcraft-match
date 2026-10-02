typedef unsigned long u32;
#if defined(_MSC_VER)
#define STDCALL __stdcall
#define NOINLINE __declspec(noinline)
#else
#define STDCALL __attribute__((stdcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef u32 (STDCALL *CreateFn)(u32,u32 *,u32);
typedef CreateFn (STDCALL *LookupFn)(u32,const char *);
typedef u32 (STDCALL *ErrorFn)(void);
typedef void (STDCALL *SleepFn)(u32);
#define VIEW(address,type) (*(type *)(address))
static NOINLINE int sub_004BB640(u32 *error)
{
    CreateFn create = VIEW(0x004FE244,LookupFn)(VIEW(0x006D59F0,u32),(const char *)0x00502CD4);
    if (!create) {
        error[0] = VIEW(0x004FE214,ErrorFn)();
        error[2] = 0x00502CC4;
        return 0;
    }
    error[0] = create(0,(u32 *)0x006D59F4,0);
    if (error[0] == 0x8878000A) {
        SleepFn sleep = VIEW(0x004FE10C,SleepFn);
        while (error[0] == 0x8878000A && VIEW(0x0051A43C,int) > 0) {
            sleep(1000);
            --VIEW(0x0051A43C,int);
            error[0] = create(0,(u32 *)0x006D59F4,0);
        }
    }
    if (error[0]) {
        error[2] = 0x00502CD4;
        if (error[0] == 0x8878000A) error[1] = 0x87;
        return 0;
    }
    return 1;
}
/* Hypothetical compiler context, not a reconstructed or counted routine. */
int context_004BB640(u32 *error) { return sub_004BB640(error); }
