#if defined(_MSC_VER)
#define REGISTER_CALL __fastcall
#else
#define REGISTER_CALL __attribute__((fastcall))
#endif
int * REGISTER_CALL sub_00446B40(unsigned int player) {
    int *second;
    int value = ((int *)0x0057F0F0u)[player];
    if (value < 500) ((int *)0x0057F0F0u)[player] = (unsigned int)value + 2000u;
    second = (int *)(0x0057F120u + player * 4u);
    value = *second;
    if (value < 500) *second = (unsigned int)value + 2000u;
    return second;
}
