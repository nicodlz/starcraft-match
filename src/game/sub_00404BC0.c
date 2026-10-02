#if defined(_MSC_VER)
#define STDCALL __stdcall
#define NOINLINE __declspec(noinline)
#else
#define STDCALL __attribute__((stdcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32;
/* Private EAX node plus one stack fallback pointer, selected by ordinary C context. */
static NOINLINE U32 STDCALL sub_00404BC0(const U32 *node,const U32 *volatile fallback)
{
    if (node) return node[1];
    return fallback[2];
}
/* Hypothetical context only; not reconstructed or counted. */
U32 STDCALL context_00404BC0(const U32 *node,const U32 *fallback)
{ return sub_00404BC0(node,fallback); }
