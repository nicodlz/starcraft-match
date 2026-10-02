#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned int FASTCALL sub_00436BD0(unsigned int index) {
    const short *table=*(const short **)0x006D5BFCu;
    unsigned int limit=(unsigned int)(int)table[0];
    unsigned int position=1;
    if(limit>position) {
        const unsigned char *flags=((const unsigned char **)0x0069A604u)[index]+0x3c;
        do {
            if((*flags&2u)!=0) break;
            ++position;
            flags+=0x34;
        } while(position<limit);
    }
    return position==limit;
}
