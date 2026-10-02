struct View { unsigned unused; unsigned value; };
unsigned __attribute__((fastcall)) sub_004C51B0(const volatile struct View *p)
{
    unsigned value = p->value;
    unsigned index = *(volatile unsigned *)0x006509B0u;
    ((volatile unsigned *)0x0058D6C4u)[index] = value;
    return 1;
}
