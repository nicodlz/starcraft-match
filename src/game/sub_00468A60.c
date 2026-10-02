unsigned char * __fastcall sub_00468A60(unsigned char *object)
{
    unsigned char *p = ((unsigned char **)0x006283F8UL)[object[76]];
    while (p) {
        if (p[77] == 83 &&
            (((unsigned char *)0x00664080UL)[4UL * *(unsigned short *)(p + 100)] & 8) &&
            ((*(unsigned char **)(p + 12))[14] & 32) &&
            *(unsigned char **)(p + 92) == object)
            return p;
        p = *(unsigned char **)(p + 108);
    }
    return 0;
}
