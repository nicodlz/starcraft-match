/* Independent C90 predicate; context wrapper only compiler ABI experiment. */
#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#define CALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define CALL __attribute__((stdcall))
#endif
static NOINLINE int CALL sub_004AA9F0(unsigned char a, unsigned char b)
{
    if (a == 0x80 && b)
        return 1;
    return 0;
}
int context_004AA9F0(const unsigned char *p)
{
    return sub_004AA9F0(p[0],p[1]);
}
