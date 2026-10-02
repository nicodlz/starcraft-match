static __declspec(noinline) unsigned sub_00473410(unsigned char *object, int x, int y)
{
    if (!object || (object[0xdc] & 2) == 0 ||
        *(unsigned short *)(object + 0x64) == 0x86 ||
        ((*(unsigned char **)(object + 0xc))[0xe] & 0x20) ||
        ((int *)0x0066FF7C)[*(unsigned *)(object + 0x13c) * 2] >= (x *= 32) + 32 ||
        ((int *)0x0066FF7C)[*(unsigned *)(object + 0x140) * 2] <= x ||
        ((int *)0x006769BC)[*(unsigned *)(object + 0x144) * 2] >= (y *= 32) + 32 ||
        ((int *)0x006769BC)[*(unsigned *)(object + 0x148) * 2] <= y)
        return 1;
    return 0;
}
unsigned context_00473410(unsigned char *object, int x, int y)
{
    return sub_00473410(object, x, y);
}
