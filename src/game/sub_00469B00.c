#if defined(_MSC_VER)
#define SC_00469B00_NOINLINE __declspec(noinline)
#define SC_00469B00_FASTCALL __fastcall
#else
#define SC_00469B00_NOINLINE __attribute__((noinline))
#define SC_00469B00_FASTCALL __attribute__((fastcall))
#endif

SC_00469B00_NOINLINE static unsigned int SC_00469B00_FASTCALL sub_00469B00(
        unsigned int *array, unsigned int flag, unsigned int value) {
    unsigned int upper = *(unsigned int *)0x0066FF74u;
    unsigned int lower;
    unsigned int middle;
    unsigned int threshold;
    if (upper == 0) return 0;
    threshold = value * 2u + (flag == 0 ? 1u : ~0u);
    lower = 0;
    middle = upper >> 1;
    while (lower < upper) {
        if ((int)threshold < (int)(array[middle * 2u + 1u] << 1)) {
            upper = middle;
            middle = (middle + lower) >> 1;
        } else {
            lower = middle + 1u;
            middle = (middle + upper + 1u) >> 1;
        }
    }
    return upper;
}
/* Compiler anchor is not a reconstructed game function. */
#ifdef SC_FINDER_COMPONENT
#pragma code_seg(".anchor")
#endif
unsigned int compiler_anchor_00469B00(unsigned int *array, unsigned int flag, unsigned int value) {
    return sub_00469B00(array, flag, value);
}
