#if defined(_MSC_VER) && !defined(__clang__)
#define PRIVATE_LEAF __declspec(noinline)
#else
#define PRIVATE_LEAF __attribute__((noinline))
#endif
static PRIVATE_LEAF unsigned int sub_00494BD0(unsigned int first, unsigned int second) {
    int distance = (first - second) & 255u;
    if (distance > 128) distance = 256 - distance;
    return distance;
}
/* Compiler context only; not a reconstructed game function. */
unsigned int compiler_context_00494BD0(unsigned int first, unsigned int second) {
    return sub_00494BD0(first, second);
}
