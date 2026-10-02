#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct State {u32 bytes,a,b;void *object;} State;
typedef int (STDCALL *GetFormat)(void *,u8 *,u32,u32 *);
/* Private ESI input is selected by the uncounted C context below. */
static NOINLINE u32 sub_004BB890(volatile State *state) {
 u8 format[20];
 u32 obtained;
 int result;
 void *object;
 if(!state->object || !state->bytes) return 0;
 object=state->object;
 result=(*(GetFormat **)object)[5](object,format,18,&obtained);
 if(result>=0 && *(u32 *)(format+8)) return state->bytes*1000U / *(u32 *)(format+8);
 return 0;
}
u32 context_sub_004BB890(volatile State *state) {u32 value=sub_004BB890(state);return value+state->bytes;}
