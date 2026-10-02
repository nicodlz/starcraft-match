/* Two reads precede both writes in the original routine. Preserve that order.
 * The minimap interpretation is a community annotation, not an original symbol. */
void sub_0047CCB0(void) {
    unsigned char first = *(volatile unsigned char *)0x0059C1A8u;
    unsigned char second = *(volatile unsigned char *)0x0059C2B8u;
    *(volatile unsigned char *)0x0065FC10u = first;
    *(volatile unsigned char *)0x0065EB2Du = second;
}
