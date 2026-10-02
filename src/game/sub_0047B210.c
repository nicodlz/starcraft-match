/* EAX carries the DWORD input and result. No memory is accessed. */
__attribute__((regparm(1))) unsigned int sub_0047B210(unsigned int value) {
    if (__builtin_expect(value == 0, 0))
        return 0;
    return 0x0059CB58u + (value & 0x7FFu) * 0x150u;
}
