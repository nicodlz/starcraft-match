unsigned sub_004AABB0(void)
{
    if (*(volatile unsigned char *)0x00596874 == 1) {
        if (*(volatile unsigned char *)0x00596877 == 0)
            return 1;
    }
    return 0;
}
