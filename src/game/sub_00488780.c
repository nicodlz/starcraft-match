#include "reverse/global_addresses.h"
// Returns the complete DWORD; do not normalize a possible nonzero value to 1.
unsigned int sub_00488780(void) {
    return SC_PAUSE_STATE;
}
