#if defined(_MSC_VER)
#define SUB0049DF10_NOINLINE __declspec(noinline)
typedef unsigned int Sub0049DF10Address;
#else
#define SUB0049DF10_NOINLINE __attribute__((noinline))
typedef __UINTPTR_TYPE__ Sub0049DF10Address;
#endif

typedef char Sub0049DF10WordSize[(sizeof(short) == 2) ? 1 : -1];
typedef char Sub0049DF10IntegerSize[(sizeof(int) == 4) ? 1 : -1];

/* Observed private ABI: AX type, ECX x, EDX y, EAX result. */
static SUB0049DF10_NOINLINE int sub_0049DF10(unsigned short type, int x, int y)
{
    unsigned int offset = (unsigned int)type * 8;
    return (int)((unsigned int)x - (unsigned int)(int)*(const volatile short *)
               (Sub0049DF10Address)(offset + 0x6617c8u)) >= 0 &&
           (int)((unsigned int)x + (unsigned int)(int)*(const volatile short *)
               (Sub0049DF10Address)(offset + 0x6617ccu)) <
               *(const unsigned short *)0x628450 &&
           (int)((unsigned int)y - (unsigned int)(int)*(const volatile short *)
               (Sub0049DF10Address)(offset + 0x6617cau)) >= 0 &&
           (int)((unsigned int)y + (unsigned int)(int)*(const volatile short *)
               (Sub0049DF10Address)(offset + 0x6617ceu)) <
               *(const unsigned short *)0x6284b4;
}

/* Compiler context hypothesis; not reconstructed or counted. */
int sub_0049DF10_context(unsigned short type, int x, int y)
{
    return sub_0049DF10(type, x, y);
}
