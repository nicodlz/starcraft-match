#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned int FASTCALL sub_00436B90(unsigned int player) {
    const short *counts=*(const short **)0x006D5BFCu;
    unsigned int bound=(unsigned int)(int)*counts;
    unsigned int index=1;
    if (bound>index) {
        const unsigned char *entry=((const unsigned char **)0x0069A604u)[player]+0x3c;
        do {
            if ((*entry & 0x10u)!=0) break;
            ++index;
            entry+=0x34;
        } while (index<bound);
    }
    return index==bound;
}
