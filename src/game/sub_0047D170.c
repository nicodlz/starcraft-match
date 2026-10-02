#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned int FASTCALL sub_0047D170(unsigned int ignored_ecx,
                                 unsigned int ignored_edx,
                                 unsigned int ignored_stack) {
    return 0u;
}
