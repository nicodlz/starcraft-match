/* Preferred-layout timer DWORD; callback returns the stored value. */
unsigned int sub_004C50D0(void) {
    return (*(volatile unsigned int *)0x0058F04Cu = 1u);
}
