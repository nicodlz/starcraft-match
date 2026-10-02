#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
static NOINLINE void sub_004049A0(unsigned char *object, unsigned char *table)
{
    unsigned int packed;
    *(unsigned short *)(object+0) += *(unsigned short *)(table+0x30 + object[6]*2);
    packed = object[7];
    *(unsigned short *)(object+2) += *(unsigned short *)(table+0x30 + (packed&3)*2);
    *(unsigned short *)(object+4) += *(unsigned short *)(table+0x30 + ((packed>>2)&3)*2);
}
/* Hypothetical context, unmatched and uncounted. */
void context_004049A0(unsigned char *object, unsigned char *table)
{ sub_004049A0(object,table); }
