#include "reverse/global_addresses.h"
// The observed caller passes a DWORD in ECX, and the callee returns the old DWORD.
// Windows i386 fastcall with one argument expresses that register/stack contract.
// Preserve arbitrary DWORDs: a C bool parameter/result would narrow the contract.
__attribute__((fastcall)) unsigned int sub_004DC540(unsigned int next) {
    unsigned int previous = SC_IN_GAME_LOOP;
    SC_IN_GAME_LOOP = next;
    return previous;
}
