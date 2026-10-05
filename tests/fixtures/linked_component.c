extern unsigned int fixed_state;
#pragma code_seg(".helper")
static __declspec(noinline) unsigned int __stdcall helper(unsigned int value)
{
    return value * 17u + fixed_state;
}
#pragma code_seg(".root")
unsigned int __stdcall component(unsigned int value)
{
    return helper(value) ^ 0x12345678u;
}
#pragma code_seg(".context")
unsigned int context(unsigned int value)
{
    return component(value);
}
