#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef struct { int x; int y; } Size;
typedef void *(STDCALL *DesktopFn)(void);
typedef void *(STDCALL *HandleFn)(void *);
typedef void *(STDCALL *SelectFn)(void *, void *);
typedef int (STDCALL *ExtentFn)(void *, const char *, int, Size *);
typedef int (STDCALL *DeleteFn)(void *);
typedef int (STDCALL *ReleaseFn)(void *, void *);
int STDCALL sub_004ABF50(void *object)
{
    void *desktop = (*(DesktopFn *)0x004FE324)();
    void *dc = (*(HandleFn *)0x004FE304)(desktop);
    void *memory_dc = (*(HandleFn *)0x004FE054)(dc);
    Size size;
    int result;
    object = (*(SelectFn *)0x004FE04C)(memory_dc, object);
    result = 0;
    if ((*(ExtentFn *)0x004FE030)(memory_dc, (const char *)0x005037C4, 52, &size)) {
        result = (size.x / 26 + 1) / 2;
    }
    (*(SelectFn *)0x004FE04C)(memory_dc, object);
    (*(DeleteFn *)0x004FE038)(memory_dc);
    (*(ReleaseFn *)0x004FE30C)((*(DesktopFn *)0x004FE324)(), dc);
    return result;
}
