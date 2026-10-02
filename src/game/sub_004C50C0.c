// Trigger timer state in the pinned preferred-layout PE.
unsigned int sub_004C50C0(void) {
    *(volatile unsigned int *)0x0058F04Cu = 0u;
    return 1u;
}
