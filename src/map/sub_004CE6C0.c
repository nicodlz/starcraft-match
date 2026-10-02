/* Preferred-VA byte access observed in the pinned 1.16.1 image.
 * The original promises a result in AL; upper EAX bits are unspecified. */
unsigned char sub_004CE6C0(void) {
    return *(volatile unsigned char *)0x006D121Cu;
}
