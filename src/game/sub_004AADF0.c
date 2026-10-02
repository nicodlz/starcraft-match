#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef void (STDCALL *Callback)(void *, void *, unsigned char *, void *);
static NOINLINE int STDCALL sub_004AADF0(unsigned char kind, void *opaque,
                         unsigned char *entry, Callback cb, void *context, void *extra)
{
    if (kind == 3 && entry[0] < 0x81 && *(unsigned short *)(entry+2) < 8) {
        cb(context,opaque,entry,extra);
        return 1;
    }
    return 0;
}
/* Hypothetical compilation context, not reconstructed or counted. */
int context_004AADF0(unsigned char kind, void *opaque, unsigned char *entry,
                    Callback cb, void *context, void *extra)
{
    return sub_004AADF0(kind,opaque,entry,cb,context,extra);
}
