/* Three ignored DWORD stack slots; callee removes 12 bytes. */
__attribute__((stdcall)) unsigned int sub_00455650(unsigned int a, unsigned int b, unsigned int c) {
    (void)a; (void)b; (void)c;
    return 23u;
}
