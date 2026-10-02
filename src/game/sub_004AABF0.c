#if defined(_MSC_VER) && !defined(__clang__)
void *memset(void *destination, int value, unsigned int size);
#pragma intrinsic(memset)
#define CLEAR48_004AABF0(destination) memset((void *)(destination), 0, 48)
#else
/* All observed clear operations write twelve consecutive DWORDs. */
static __forceinline void clear48_004AABF0(volatile unsigned int *destination)
{
    unsigned int i;
    for (i = 0; i < 12; ++i)
        destination[i] = 0;
}
#define CLEAR48_004AABF0(destination) clear48_004AABF0((volatile unsigned int *)(destination))
#endif
void sub_004AABF0(void)
{
    int index;
    unsigned int value;
    switch (*(unsigned char *)0x0059686Eu) {
    case 0:
        CLEAR48_004AABF0(0x0057F0F0u);
        CLEAR48_004AABF0(0x0057F120u);
        CLEAR48_004AABF0(0x0057F180u);
        CLEAR48_004AABF0(0x0057F150u);
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
        CLEAR48_004AABF0(0x0057F0F0u);
        CLEAR48_004AABF0(0x0057F120u);
        CLEAR48_004AABF0(0x0057F180u);
        CLEAR48_004AABF0(0x0057F150u);
        break;
    }
}
