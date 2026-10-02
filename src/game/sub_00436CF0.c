/* Private compiler-context hypothesis; only the static leaf is measured. */
#if defined(_MSC_VER) && !defined(__clang__)
void * __cdecl memcpy(void *, const void *, unsigned int);
#define SC_LEAF static __declspec(noinline)
#pragma intrinsic(memcpy)
#else
#define SC_LEAF static __attribute__((noinline))
#endif

SC_LEAF void sub_00436CF0(unsigned char *state)
{
    unsigned char snapshot[2500];
    unsigned int i;
    unsigned char *base;
    unsigned char *region;
    unsigned short *neighbors;
    unsigned int count;

#if defined(_MSC_VER) && !defined(__clang__)
    memcpy(snapshot, state, 2500);
#else
    for (i = 0; i < 2500u; i++)
        ((volatile unsigned char *)snapshot)[i] =
            ((const volatile unsigned char *)state)[i];
#endif
    base = *(unsigned char **)0x006D5BFCu;
    for (i = 0; i < 2500u; i++) {
        if (snapshot[i] == 2) {
            state[i] = 3;
            region = base + 0x449FC + (unsigned short)i * 64u;
            neighbors = *(unsigned short **)(region + 12);
            count = (unsigned int)region[7] - (int)*(signed char *)(region + 33);
            while (count) {
                if (state[*neighbors] == 0)
                    state[*neighbors] = 4;
                neighbors++;
                count--;
            }
        }
    }
}

/* Independently authored context, not reconstructed or counted. */
void compiler_context_00436CF0(unsigned char *state)
{
    sub_00436CF0(state);
}
