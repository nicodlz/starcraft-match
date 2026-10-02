typedef unsigned long u32;
typedef int (__stdcall *event_proc)(void *);
void sub_004D3510(void)
{
    void *handle = *(void **)0x006D5ECC;
    if (handle && *(u32 *)0x006D5ED0) {
        (*(event_proc *)0x004FE144)(handle);
        *(u32 *)0x006D5ED0 = 0;
    }
}
