extern unsigned int fixed_state;
#pragma code_seg(".helper")
static __declspec(noinline) unsigned int __stdcall helper(unsigned int value) { return value * 17u + fixed_state; }
#pragma code_seg(".root")
unsigned int __stdcall component(unsigned int value) {
    volatile unsigned int address = (unsigned int)&&finish;
    unsigned int result = helper(value);
    if (!value) return result;
finish:
    return result + address;
}
#pragma code_seg(".context")
unsigned int context(unsigned int value) { return component(value); }
