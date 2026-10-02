typedef unsigned char u8;
extern void * __stdcall sub_0041006A(unsigned int, const char *, unsigned int, unsigned int);
#pragma code_seg(".scmatch")
static __declspec(noinline) void sub_00471010(u8 value)
{
    u8 *p;
    if (*(u8 *)0x0066FBF9 == value)
        return;
    p = *(u8 **)0x006D5C74;
    *(u8 *)0x0066FBF9 = value;
    if (!p) {
        p = sub_0041006A(2, (const char *)0x0050467C, 300, 0);
        *(u8 **)0x006D5C74 = p;
    }
    p[0] = 61;
    p[1] = value;
}
#pragma code_seg(".scctx")
/* Hypothetical compiler context only; excluded and not reconstructed. */
void experiment_00471010(u8 value)
{
    sub_00471010(value);
}
