#if defined(_MSC_VER)
#define SC_004283C0_STDCALL __stdcall
#else
#define SC_004283C0_STDCALL __attribute__((stdcall))
#endif

/* The dispatcher supplies one ignored object pointer on the stack. */
unsigned int SC_004283C0_STDCALL sub_004283C0(const void *ignored_object) {
    unsigned char * const *cursor =
        (unsigned char * const *)0x00597208u;
    do {
        unsigned char *unit = *cursor;
        if (unit && (unit[0xdc] & 0x10))
            return 0;
        ++cursor;
    } while ((int)cursor < 0x00597238);
    return 1;
}
