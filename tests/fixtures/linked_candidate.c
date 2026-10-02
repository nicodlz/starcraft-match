/* Independent synthetic fixture. No original binary/source input. */
extern unsigned __fastcall fast_target(unsigned, unsigned);
extern unsigned fixed_global;
__attribute__((section(".cand"), noinline))
unsigned __stdcall candidate(unsigned value)
{
    return fast_target(value, 7) + fixed_global;
}
__attribute__((section(".ctx"), noinline))
unsigned wrapper(unsigned value)
{
    return candidate(value);
}
