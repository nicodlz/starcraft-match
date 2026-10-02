#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
struct Sub0045CC90Rect {
    int left, top, right, bottom;
};
typedef char Sub0045CC90IntWidth[sizeof(int) == 4 ? 1 : -1];
typedef char Sub0045CC90RectSize[sizeof(struct Sub0045CC90Rect) == 16 ? 1 : -1];

static int SC_NOINLINE sub_0045CC90(struct Sub0045CC90Rect *rect)
{
    int right = rect->right, bottom, left, top;
    if (right <= 0)
        return 1;
    bottom = rect->bottom;
    if (bottom <= 0)
        return 1;
    left = rect->left;
    if (left >= 640)
        return 1;
    top = rect->top;
    if (top >= 400)
        return 1;
    if (left < 0)
        rect->left = 0;
    if (right >= 640)
        rect->right = 640;
    if (top < 0)
        rect->top = 0;
    if (bottom >= 400)
        rect->bottom = 400;
    return 0;
}

/* Ordinary C compilation context; not reconstructed or counted. */
int sc_probe_0045CC90(struct Sub0045CC90Rect *rect)
{
    return sub_0045CC90(rect);
}
