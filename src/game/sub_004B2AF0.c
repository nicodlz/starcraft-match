__attribute__((fastcall)) void sub_004B2AF0(unsigned char *record,
                                         unsigned int index) {
    *(volatile unsigned int *)(record + 0x19c) =
        ((volatile unsigned int *)0x00581F94u)[index];
    *(volatile unsigned int *)(record + 0x1a0) =
        ((volatile unsigned int *)0x00581FF4u)[index];
    *(volatile unsigned int *)(record + 0x1a4) =
        ((volatile unsigned int *)0x00581FC4u)[index];
    unsigned int value = ((volatile unsigned int *)0x00582054u)[index];
    value += ((volatile unsigned int *)0x00582024u)[index];
    *(volatile unsigned int *)(record + 0x24c) = value;
}
