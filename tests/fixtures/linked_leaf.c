/* Synthetic compiler-owned local label; contains no game material. */
extern unsigned int fixed_state;
#pragma code_seg(".root")
unsigned int __stdcall leaf(unsigned int value) {
    volatile unsigned int address = (unsigned int)&&finish;
    unsigned int result = value * 17u + fixed_state;
    if (!value) return result;
finish:
    return result + address;
}
#pragma code_seg(".context")
unsigned int context(unsigned int value) { return leaf(value); }
