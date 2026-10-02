#pragma code_seg(".scmatch")
typedef unsigned long u32;
extern unsigned char * __stdcall sub_0041006A(u32, const char *, u32, u32);
int sub_00452320(void)
{
    unsigned char *p = *(unsigned char **)0x006D5C94;
    if (!p) {
        p = sub_0041006A(1, (const char *)0x0050467C, 0x3F3, 0);
        *(unsigned char **)0x006D5C94 = p;
    }
    *p = 0x5B;
    return 1;
}

#pragma code_seg()
