#if defined(_MSC_VER) && !defined(__clang__)
#define SC_STDCALL __stdcall
void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)
#else
#define SC_STDCALL __attribute__((stdcall))
/* Portable source-only copy; avoids an unresolved fallback memcpy call. */
static __inline__ __attribute__((always_inline))
void *sc_copy_004CB3A0(void *destination, const void *source, unsigned int size)
{
    unsigned char *output = (unsigned char *)destination;
    const unsigned char *input = (const unsigned char *)source;
    while (size--) {
        *output++ = *input++;
    }
    return destination;
}
#define memcpy sc_copy_004CB3A0
#endif

typedef struct Sub004CB3A0View {
    unsigned int end;
    unsigned int current;
    unsigned int reserved;
    unsigned int size;
} Sub004CB3A0View;

unsigned int SC_STDCALL sub_004CB3A0(const Sub004CB3A0View *view,
                                    unsigned int length,
                                    unsigned int unused)
{
    unsigned short era;

    if (length != 2)
        return 0;
    if (view->current + view->size > view->end)
        return 0;
    memcpy(&era, (const void *)view->current, view->size);
    *(unsigned short *)0x57f1dcu = era;
    if (era > 4 && !*(const unsigned char *)0x58f440u)
        return 0;
    *(unsigned short *)0x57f1dcu = (unsigned short)((int)era % 8);
    return 1;
}
