/* ECX object input; arithmetic shifts and wrapping DWORD addition. */
#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif

int SC_FASTCALL sub_00401400(const unsigned char *object)
{
    unsigned int index = *(const unsigned short *)(object + 0x64);
    int result = ((const int *)0x00662350u)[index] >> 8;
    if (result == 0) {
        result = (int)(*(const unsigned int *)(object + 8) + 255u) >> 8;
        if (result == 0)
            result = 1;
    }
    return result;
}
