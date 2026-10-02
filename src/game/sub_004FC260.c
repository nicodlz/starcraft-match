/* Preserve the observed DWORD representation without numeric conversion. */
void sub_004FC260(void) {
    *(volatile unsigned int *)0x006D5F08u =
        *(volatile const unsigned int *)0x004FF8F8u;
}
