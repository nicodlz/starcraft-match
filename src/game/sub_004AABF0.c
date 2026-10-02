void *memset(void *destination, int value, unsigned int size);
#pragma intrinsic(memset)
void sub_004AABF0(void)
{
    int index;
    unsigned int value;
    switch (*(unsigned char *)0x0059686Eu) {
    case 0:
        memset((void *)0x0057F0F0u,0,48);
        memset((void *)0x0057F120u,0,48);
        memset((void *)0x0057F180u,0,48);
        memset((void *)0x0057F150u,0,48);
        break;
    case 1:
        value = *(unsigned int *)0x0059687Cu;
        for (index = 0; index < 12; ++index) {
            ((unsigned int *)0x0057F0F0u)[index] = value;
            ((unsigned int *)0x0057F180u)[index] = value;
            ((unsigned int *)0x0057F120u)[index] = 0;
            ((unsigned int *)0x0057F150u)[index] = 0;
        }
        break;
    default:
        memset((void *)0x0057F0F0u,0,48);
        memset((void *)0x0057F120u,0,48);
        memset((void *)0x0057F180u,0,48);
        memset((void *)0x0057F150u,0,48);
        break;
    }
}
