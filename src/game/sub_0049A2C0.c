/* Only the observed DWORD and timer-byte offsets are described here. */
typedef struct {
    unsigned char reserved00[220];
    unsigned int valueDC;
    unsigned char reservedE0[55];
    unsigned char value117;
    unsigned char reserved118;
    unsigned char value119;
    unsigned char reserved11A[10];
    unsigned char value124;
} View0049A2C0;
unsigned int sub_0049A2C0(void) {
    unsigned int result = 1;
    View0049A2C0 **cursor = (View0049A2C0 **)0x006284B8u;
    do {
        View0049A2C0 *object = *cursor;
        if (object == 0) break;
        if ((object->valueDC & 0x400u) == 0 && object->value117 == 0 &&
            object->value119 == 0 && object->value124 == 0) {
            result = 0;
            break;
        }
        ++cursor;
    } while ((int)cursor < 0x006284E8);
    return result;
}
