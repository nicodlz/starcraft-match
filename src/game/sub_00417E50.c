/* Independent C reconstruction; only sub_00417E50 is a matching candidate.
 * Ordinary context selects observed private ECX/EAX ABI; context is not reconstructed. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#else
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#endif
typedef struct Event { unsigned a,b,c; unsigned short code; unsigned short unused; unsigned d; } Event;
typedef void (FASTCALL *Callback)(void*,Event*);
static NOINLINE void sub_00417E50(void *object,unsigned index) {
 Event event; event.code=14; event.a=11; event.b=index;
 (*(Callback*)((char*)object+42))(object,&event);
}
void context(void *object,unsigned index) { sub_00417E50(object,index); }
