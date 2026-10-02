#if defined(_MSC_VER)
#define STDCALL __stdcall
#define FASTCALL __fastcall
#else
#define STDCALL __attribute__((stdcall))
#define FASTCALL __attribute__((fastcall))
#endif
#pragma code_seg(".scmatch")
extern int STDCALL ordinal_113(unsigned int slot, char *destination, unsigned int capacity);
int FASTCALL sub_00470CB0(unsigned char slot)
{
    char destination[260];
    return ordinal_113(slot, destination, 260) != 0;
}

#pragma code_seg()
