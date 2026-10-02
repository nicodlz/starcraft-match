#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned char * FASTCALL sub_004180A0(unsigned char *object) {
    unsigned char *parent=*(unsigned char **)(object+0x32);
    unsigned char *current=*(unsigned char **)(parent+0x42);
    if(object==current) object=0;
    while (*(unsigned char **)current!=object)
        current=*(unsigned char **)current;
    return current;
}
