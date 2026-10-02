#if defined(_MSC_VER)
#define STDCALL __stdcall
#define NOINLINE __declspec(noinline)
#else
#define STDCALL __attribute__((stdcall))
#define NOINLINE __attribute__((noinline))
#endif
unsigned int __cdecl strlen(const char *);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(strlen)
#endif
typedef void *Handle;
typedef unsigned int U32;
typedef struct Rect { int left, top, right, bottom; } Rect;
typedef int (STDCALL *ClientFn)(Handle, Rect *);
typedef Handle (STDCALL *DCFn)(Handle);
typedef Handle (STDCALL *MessageFn)(Handle, U32, U32, int);
typedef Handle (STDCALL *ObjectFn)(Handle, Handle);
typedef int (STDCALL *TextFn)(Handle, const char *, int, Rect *, U32);
typedef int (STDCALL *ReleaseFn)(Handle, Handle);
typedef char RectSizeCheck[sizeof(Rect) == 16 ? 1 : -1];
static NOINLINE int STDCALL sub_004489F0(Handle window, const char *text)
{
    Rect client, bounds;
    Handle dc, previous, font;
    if (!window || !text || !*text)
        return 1;
    (*(ClientFn *)0x004FE284)(window, &client);
    bounds = client;
    dc = (*(DCFn *)0x004FE304)(window);
    if (!dc)
        return 0;
    font = (*(MessageFn *)0x004FE358)(window, 0x31, 0, 0);
    if (!font)
        return 0;
    previous = (*(ObjectFn *)0x004FE04C)(dc, font);
    (*(TextFn *)0x004FE2A8)(dc, text, (int)strlen(text), &bounds, 0x410);
    if (previous)
        (*(ObjectFn *)0x004FE04C)(dc, previous);
    (*(ReleaseFn *)0x004FE30C)(window, dc);
    return bounds.bottom < client.bottom && bounds.right <= client.right;
}
/* Hypothetical compiler context only; never reconstructed or counted. */
int STDCALL context_004489F0(Handle window, const char *text)
{
    return sub_004489F0(window, text);
}
