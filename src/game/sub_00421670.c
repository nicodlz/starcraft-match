typedef int (__stdcall *CursorCall)(int,int);
static __declspec(noinline) void sub_00421670(short a,short b) {
 int sy=b,sx=a;
 (*(CursorCall *)0x004FE2CC)(sx,sy);
 *(volatile int *)0x006CDDC4=sx;
 *(volatile int *)0x006CDDC8=sy;
}
/* Compiler context only; not a reconstructed game function. */
int context_sub_00421670(short a,short b) {sub_00421670(a,b);return a;}
