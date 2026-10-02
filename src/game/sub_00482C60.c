#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_STDCALL __stdcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_STDCALL __attribute__((stdcall))
#endif

struct Sub00482C60Rect {
    short left;
    short top;
    short right;
    short bottom;
};
typedef char Sub00482C60ShortWidth[sizeof(short) == 2 ? 1 : -1];
typedef char Sub00482C60RectSize[sizeof(struct Sub00482C60Rect) == 8 ? 1 : -1];

static void SC_NOINLINE SC_STDCALL
sub_00482C60(struct Sub00482C60Rect *rect, unsigned short value,
             unsigned char *grid)
{
    int y, x;
    for (y = rect->top; y < rect->bottom; ++y)
        for (x = rect->left; x < rect->right; ++x)
            *(unsigned short *)(grid + 12 + 2 * (y * 256 + x)) = value;
}

/* Ordinary C compilation context; not a reconstructed or counted routine. */
void sc_probe_00482C60(struct Sub00482C60Rect *rect, unsigned short value,
                     unsigned char *grid)
{
    sub_00482C60(rect, value, grid);
}
