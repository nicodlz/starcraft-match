#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
typedef unsigned int Sub004A6660Address;
#else
#define SC_NOINLINE __attribute__((noinline))
typedef __UINTPTR_TYPE__ Sub004A6660Address;
#endif
typedef struct Sub004A6660View {
    unsigned int field_00;
    unsigned int field_04;
} Sub004A6660View;
static SC_NOINLINE unsigned int sub_004A6660(Sub004A6660View *input) {
    Sub004A6660View *value = input ? input : (Sub004A6660View *)0x0051A278u;
    volatile Sub004A6660View *next = (Sub004A6660View *)(Sub004A6660Address)value->field_00;
    if (next) {
        unsigned int previous = value->field_04;
        unsigned int target;
        if ((int)previous <= 0) target = ~previous;
        else {
            unsigned int offset = (unsigned int)(Sub004A6660Address)value - next->field_04;
            target = previous + offset;
        }
        *(unsigned int *)(Sub004A6660Address)target = (unsigned int)(Sub004A6660Address)next;
        ((Sub004A6660View *)(Sub004A6660Address)value->field_00)->field_04 = value->field_04;
        value->field_00 = 0;
        value->field_04 = 0;
    }
    next = *(Sub004A6660View **)0x0051A278u;
    value->field_00 = (unsigned int)(Sub004A6660Address)next;
    value->field_04 = next->field_04;
    next->field_04 = (unsigned int)(Sub004A6660Address)input;
    *(Sub004A6660View **)0x0051A278u = value;
    return (unsigned int)(Sub004A6660Address)value;
}
/* Hypothetical compiler context, not a reconstructed or matched caller. */
unsigned int sc_context_004A6660(Sub004A6660View *input) {
    return sub_004A6660(input);
}
