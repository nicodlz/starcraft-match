#if defined(_MSC_VER) && !defined(__clang__)
#define SC_FAST __fastcall
void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#define SC_BARRIER() _ReadWriteBarrier()
#else
#define SC_FAST __attribute__((fastcall))
#define SC_BARRIER() __atomic_signal_fence(__ATOMIC_SEQ_CST)
#endif
unsigned int SC_FAST sub_0045B100(
        unsigned int unit, unsigned int flag, unsigned char player) {
    unsigned int index;
    unsigned int result;
    unsigned char raw = *(volatile unsigned char *)&player;
    SC_BARRIER();
    if (flag) {
        index = (unsigned short)unit * 12u + raw;
        result = ((unsigned int *)0x00584DE4u)[index];
        if (unit == 30u) result += ((unsigned int *)0x00584ED4u)[raw];
        else if (unit == 5u) result += ((unsigned int *)0x00585384u)[raw];
    } else {
        index = (unsigned short)unit * 12u + raw;
        result = ((unsigned int *)0x00582324u)[index];
        if (unit == 30u) result += ((unsigned int *)0x00582414u)[raw];
        else if (unit == 5u) result += ((unsigned int *)0x005828C4u)[raw];
    }
    return result;
}
