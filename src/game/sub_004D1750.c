#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef struct { int x; int y; } Point;
typedef void *(STDCALL *LoadFn)(void *, const char *);
typedef void *(STDCALL *CursorFn)(void *);
typedef int (STDCALL *GetFn)(Point *);
typedef int (STDCALL *PosFn)(int, int);
typedef int (STDCALL *ShowFn)(int);
static NOINLINE void sub_004D1750(int show)
{
    void *cursor = *(void **)0x006d6384;
    Point position;
    if (!cursor) {
        cursor = (*(LoadFn *)0x004fe344)(0, (const char *)0x7f00);
        *(void **)0x006d6384 = cursor;
    }
    (*(CursorFn *)0x004fe338)(show ? cursor : 0);
    (*(GetFn *)0x004fe2dc)(&position);
    (*(PosFn *)0x004fe2cc)(position.x, position.y);
    if (*(int *)0x0051a3d8 != show) {
        *(int *)0x0051a3d8 = show;
        (*(ShowFn *)0x004fe308)(show);
    }
}
int context_004D1750(int show)
{
    sub_004D1750(show);
    return show;
}
