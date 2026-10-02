/* Eight descending BYTE reads at the observed 0x24-byte stride. */
unsigned int sub_004A8CD0(void)
{
    unsigned int result = 0;
    const unsigned char *entry = (const unsigned char *)0x0057F008u;
    do {
        entry -= 0x24;
        if (*entry == 6) ++result;
    } while (entry != (const unsigned char *)0x0057EEE8u);
    return result;
}
