/* Independent C reconstruction of pinned Windows i386 target. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned (STDCALL *GetPid)(unsigned,unsigned*);
typedef int (STDCALL *EnumFn)(unsigned,unsigned);
void sub_004DCC50(void) {
 unsigned pid;
 if (*(unsigned*)0x006d11bc==4) {
  (*(GetPid*)0x004fe334)(*(unsigned*)0x0051bfb0,&pid);
  (*(EnumFn*)0x004fe32c)(0x004dc6d0,pid);
 }
 *(unsigned*)0x006d11bc=25;
}
