/* Twelve records, visited backwards; preserve the observed byte accesses. */
void sub_004A8DE0(void) {
    unsigned char *cursor = (unsigned char *)0x0059BF68u;
    do {
        unsigned char value = cursor[-0x24];
        cursor -= 0x24;
        if (value == 5 || value == 3 || value == 4 || value == 7)
            *cursor = 6;
        cursor[2] = 0;
    } while (cursor != (unsigned char *)0x0059BDB8u);
}
