/* Static compiler context selects the observed custom register ABI under
 * MSVC 13.10.3077. The ordinary C helper is experimental compilation context,
 * not a reconstructed or counted game function. */
#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
static void SC_NOINLINE sub_00432430(unsigned char *object, unsigned int index)
{
    unsigned char *state = *(unsigned char **)(object + 0x134);
    if (state != 0 && state[8] == 3) {
        state[index + 9] = 0;
        *(unsigned int *)(state + index * 4 + 0x18) = 0;
    }
}
void context_00432430(unsigned char *object, unsigned int index)
{
    sub_00432430(object, index);
}
