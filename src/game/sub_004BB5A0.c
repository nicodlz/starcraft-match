#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
void * memset(void *,int,unsigned int);
#if defined(_MSC_VER)
#pragma intrinsic(memset)
#endif
typedef struct Desc {u32 size, flags, bytes, reserved, format;} Desc;
typedef int (STDCALL *Create)(void *, Desc *, void **, void *);
/* Static compiler context induces observed ESI input. */
static NOINLINE int sub_004BB5A0(int *state) {
 Desc d;
 int result;
 void *object;
 memset(&d,0,20);
 object=*(void **)0x006D59F4;
 d.size=20;
 d.flags=1;
 result=(*(Create **)object)[3](object,&d,(void **)0x006D59F8,0);
 state[0]=result;
 if(result) {state[2]=0x00502C9C;return 0;}
 return 1;
}
int context_sub_004BB5A0(int *state) {int ok=sub_004BB5A0(state);return ok+state[0];}
