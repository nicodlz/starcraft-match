/* AL describes the defined byte result; audited caller ignores the result. */
unsigned char sub_004DBC00(void)
{
    unsigned char flag = *(volatile const unsigned char *)0x0057F0B4u;
    /* Compiler-layout hypothesis only; no measured branch-frequency claim. */
    if (__builtin_expect(flag == 0, 1)) {
        flag = *(volatile const unsigned char *)0x0057F1E3u;
        *(volatile unsigned int *)0x0051CA1Cu = flag;
    }
    return flag;
}
