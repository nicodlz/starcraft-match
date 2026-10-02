#include <stddef.h>

/* The observed register inputs are EAX (object) and ECX (unbounded index). */
__attribute__((regcall)) void sub_00432430(unsigned char *object, unsigned int index) {
    unsigned char *state = *(unsigned char **)(object + 0x134);
    if (state != NULL && state[8] == 3) {
        state[index + 9] = 0;
        *(unsigned int *)(state + index * 4 + 0x18) = 0;
    }
}
