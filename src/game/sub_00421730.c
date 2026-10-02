/* Independently authored C90 behavioral reconstruction. */
#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef int (STDCALL *clip_fn)(const void *);
extern void sub_004215E0(void);

#pragma code_seg(".scmatch")
static NOINLINE void sub_00421730(u32 value)
{
    if (value != *(volatile u32 *)0x006D5DD0u) {
        *(volatile u32 *)0x006D5DD0u = value;
        if (value && !*(volatile u32 *)0x006D5DD4u)
            sub_004215E0();
        (*(clip_fn *)0x004FE37Cu)(value ? (const void *)0x006CDDB0u : (const void *)0);
    }
}

#pragma code_seg(".scctx")
void context_00421730(u32 value)
{
    sub_00421730(value);
}

#pragma code_seg()
