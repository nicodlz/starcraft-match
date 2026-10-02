#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
int SC_STDCALL sub_004285E0(void *unused) {
    const unsigned char *const *selection = (const unsigned char *const *)0x00597208u;
    (void)unused;
    do {
        const unsigned char *object = *selection;
        if (object != 0 && object[0x4D] != 0x21) return 1;
        selection++;
    } while ((int)selection < 0x00597238);
    return 0;
}
