#if defined(_MSC_VER)
#define SC __stdcall
#define NI __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define NI __attribute__((noinline))
#endif
typedef unsigned long u32;
static NI int SC sub_0047A750(int value, int total, int *output, int count)
{
    int percentage, scaled, remainder;
    count = (int)((u32)count - 1);
    if (total) percentage = (int)((u32)value * 100) / total;
    else percentage = 100;
    scaled = (int)((u32)percentage * (u32)count) / 100;
    if (scaled < 3) scaled = 3;
    remainder = scaled % 3;
    if (remainder) {
        if (remainder > 1) {
            scaled += 3 - remainder;
        }
        else scaled -= remainder;
    }
    *output = scaled;
    return percentage;
}
/* Hypothetical compiler context, not reconstructed/counted. */
int context(int value,int total,int *output,int count)
{
    return sub_0047A750(value,total,output,count);
}
