/* Independent C reconstruction; context helpers are hypothetical and uncounted. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#define STDCALL __attribute__((stdcall))
#endif
typedef struct Event { unsigned a,b,c; unsigned short code,unused; unsigned d; } Event;
typedef void (FASTCALL *Callback)(void*,Event*);
void FASTCALL sub_0047E440(void *object) {
 Event event; unsigned value;
 *(unsigned*)((char*)object+0x26)=0x100;
 value=(*(unsigned*)0x006cdfec >>8)&1;
 event.code=14;event.a=11;event.b=value;
 (*(Callback*)((char*)object+0x2a))(object,&event);
}
