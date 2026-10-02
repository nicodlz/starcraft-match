#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef struct { int left, top, right, bottom; } Rect;
typedef int (STDCALL *rect_fn)(void *, Rect *);
typedef void *(STDCALL *dc_fn)(void *);
typedef int (STDCALL *cap_fn)(void *, int);
typedef int (STDCALL *release_fn)(void *, void *);
typedef int (STDCALL *pos_fn)(void *, void *, int, int, int, int, unsigned int);
#define IMPORT(a,t) (*(t *)(a))
static NOINLINE void sub_00420860(void *window)
{
    Rect r;
    int width, height, x, y;
    void *dc;
    IMPORT(0x004fe300,rect_fn)(window, &r);
    width = r.right - r.left;
    height = r.bottom - r.top;
    dc = IMPORT(0x004fe304,dc_fn)(window);
    x = IMPORT(0x004fe068,cap_fn)(dc,8);
    y = IMPORT(0x004fe068,cap_fn)(dc,10);
    IMPORT(0x004fe30c,release_fn)(window,dc);
    IMPORT(0x004fe314,pos_fn)(window,0,(x-width)/2,(y-height)/2,0,0,5);
}
/* Hypothetical source context, not reconstructed or counted. */
void context_00420860(void *window) { sub_00420860(window); }
