/* Preserve the observed signed address tests and sequential access widths. */
typedef char Sub004893C0WidthCheck[sizeof(unsigned int) == 4 ? 1 : -1];

void sub_004893C0(void)
{
    unsigned int offset = 0;
    unsigned int address;
    unsigned int flags;
    do {
        address = *(const unsigned int *)(0x0051A288u + offset);
        while ((int)address > 0) {
            flags = *(const unsigned int *)(address + 0x948u) & 0xFFFFFFF6u;
            *(unsigned char *)(address + 0x967u) = 0;
            *(unsigned int *)(address + 0x948u) = flags;
            address = *(const unsigned int *)(address + 4u);
        }
        offset += 12;
    } while (offset < 96);
}
