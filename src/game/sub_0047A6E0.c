/* Independent C; ordinary context selects the observed private ABI.
   Wrapping products intentionally use unsigned32 before signed division. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef char i386_int_width[(sizeof(int) == 4 && sizeof(u32) == 4) ? 1 : -1];
static NOINLINE int STDCALL sub_0047A6E0(int numerator, int denominator, int *output, int multiplier)
{
    int percent;
    int scaled;
    int remainder;
    if (denominator) percent = (int)((u32)numerator * 100u) / denominator;
    else percent = 100;
    scaled = (int)((u32)percent * (u32)multiplier) / 100;
    if (scaled < 3) scaled = 3;
    remainder = scaled % 3;
    if (remainder) {
        if (remainder > 1) scaled += 3 - remainder;
        else scaled -= remainder;
    }
    *output = scaled;
    return percent;
}
int compilation_context(int numerator, int denominator, int *output, int multiplier)
{
    int result = sub_0047A6E0(numerator, denominator, output, multiplier);
    return result + *output;
}
