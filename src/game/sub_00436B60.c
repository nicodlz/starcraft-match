#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
unsigned int SC_STDCALL sub_00436B60(unsigned char index)
{
    unsigned int offset = (unsigned int)index << 2;
    unsigned int first = *(const unsigned int *)(0x00584DE4u + offset);
    unsigned int second = *(const unsigned int *)(0x00586554u + offset) * 4u;
    if (second > first)
        return first * 2u;
    return first + second;
}
