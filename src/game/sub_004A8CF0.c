unsigned char sub_004A8CF0(void) {
    unsigned char result = 0;
    unsigned int p = 0x0057F008u;
    do {
        unsigned char state = *(const unsigned char *)(p - 0x24);
        p -= 0x24;
        if (state == 6) ++result;
    } while (p != 0x0057EEE8u);
    return result;
}
