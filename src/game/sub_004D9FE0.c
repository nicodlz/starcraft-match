/* Independent C reconstruction of pinned Windows i386 target. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef struct Rect { int left,top,right,bottom; } Rect;
typedef int (STDCALL *GetRect)(unsigned,Rect*);
typedef unsigned (STDCALL *GetDc)(unsigned);
typedef int (STDCALL *GetCaps)(unsigned,int);
typedef int (STDCALL *ReleaseDc)(unsigned,unsigned);
typedef int (STDCALL *SetPos)(unsigned,unsigned,int,int,int,int,unsigned);
static NOINLINE void sub_004D9FE0(unsigned window) {
 Rect rect; unsigned dc; int width,height,horizontal,vertical;
 (*(GetRect*)0x004fe300)(window,&rect);
 width=rect.right-rect.left; height=rect.bottom-rect.top;
 dc=(*(GetDc*)0x004fe304)(window);
 horizontal=(*(GetCaps*)0x004fe068)(dc,8);
 vertical=(*(GetCaps*)0x004fe068)(dc,10);
 (*(ReleaseDc*)0x004fe30c)(window,dc);
 (*(SetPos*)0x004fe314)(window,0,(horizontal-width)/2,(vertical-height)/2,0,0,5);
}
void context(unsigned window) { sub_004D9FE0(window); }
