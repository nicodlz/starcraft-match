/* Preserve the observed DWORD representation without numeric conversion. */
void sub_004FC3F0(void) {
    *(volatile unsigned int *)0x006D5F6Cu =
        *(volatile const unsigned int *)0x004FF8F8u;
}
