/* Independent C; standard external-only linking, context excluded. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
/* Independent C scaffold: actual leaf inputs selected by compiler context.
   External sub_00470DB0 is unresolved and never bypassed for matching. */
extern void STDCALL sub_00470DB0(int first, int second);
#pragma code_seg(".scmatch")
static NOINLINE int sub_00452350(int first, int second)
{
    if (first < 8 && second < 8 && first != second) {
        sub_00470DB0(first, second);
        return 1;
    }
    return 0;
}
/* Hypothetical compilation context only, not reconstructed or counted. */
#pragma code_seg(".scctx")
int context_00452350(int first, volatile int *value)
{
    return sub_00452350(first, *value - 6);
}
