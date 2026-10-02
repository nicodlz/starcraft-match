#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
/* The single stack argument is ignored by the observed callback. */
unsigned int SC_STDCALL sub_00428670(void *unused)
{
    unsigned char **cursor = (unsigned char **)0x00597208u;
    (void)unused;
    do {
        unsigned char *object = *cursor;
        if (object != 0 && object[0x4D] != 0x21u)
            return 1;
        ++cursor;
    } while ((int)cursor < 0x00597238);
    return 0;
}
