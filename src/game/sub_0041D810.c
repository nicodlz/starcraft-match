#if defined(_MSC_VER) && !defined(__clang__)
#define REGISTER_CALL __fastcall
#else
#define REGISTER_CALL __attribute__((fastcall))
#endif
#if defined(_MSC_VER) && !defined(__clang__)
void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
#else
typedef struct __attribute__((packed)) { unsigned int value; } FillWord;
#endif
typedef struct { short stride; unsigned short padding; unsigned char *pixels; } SurfaceLeaf;
void REGISTER_CALL sub_0041D810(unsigned short count, unsigned int unused, short x, short y) {
    SurfaceLeaf *surface = *(SurfaceLeaf *const *)0x006CF4A8u;
    unsigned char colour = *(const unsigned char *)0x006CF4ACu;
    unsigned char *dest = surface->pixels + (int)y * surface->stride + x;
#if defined(_MSC_VER) && !defined(__clang__)
    memset(dest, colour, count);
#else
    /* Portable source-compilation path: preserve DWORD fills and BYTE tail. */
    unsigned int words = count >> 2;
    unsigned int tail = count & 3u;
    unsigned int repeated = (unsigned int)colour * 0x01010101u;
    while (words--) {
        ((volatile FillWord *)dest)->value = repeated;
        dest += 4;
    }
    while (tail--) *(volatile unsigned char *)dest++ = colour;
#endif
}
