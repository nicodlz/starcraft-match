#pragma code_seg(".b2e0")
/* Independently reconstructed pinned Windows i386 1.16.1 leaf. */
struct Sub0047B2E0View { unsigned char unknown[0x64]; unsigned short field; };
#if defined(_MSC_VER) && !defined(__clang__)
#define PRIVATE_NOINLINE __declspec(noinline)
#elif defined(__i386__)
#define PRIVATE_NOINLINE __attribute__((noinline, regparm(1)))
#else
#define PRIVATE_NOINLINE __attribute__((noinline))
#endif
#if defined(_MSC_VER) && !defined(__clang__)
#define FIELD_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define FIELD_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
typedef char Sub0047B2E0WordWidth[(sizeof(unsigned short)==2)?1:-1];
typedef char Sub0047B2E0ResultWidth[(sizeof(unsigned int)==4)?1:-1];
typedef char Sub0047B2E0FieldOffset[(FIELD_OFFSET(struct Sub0047B2E0View,field)==0x64)?1:-1];
static PRIVATE_NOINLINE unsigned int sub_0047B2E0(const struct Sub0047B2E0View *object)
{
#if defined(_MSC_VER) && !defined(__clang__)
 unsigned short value=object->field;
#else
 volatile unsigned short value=object->field;
#endif
 if (value==0x6a || value==0x6f || value==0x71 || value==0x72 || value==0x82 || value==0x83 || value==0x84 || value==0x85 || value==0x9a || value==0xa0 || value==0xa7 || value==0x9b) return 1;
 return 0;
}
/* Ordinary independent compiler context, neither matched nor counted. */
#pragma code_seg(".pctx")
unsigned int compiler_context_0047B2E0(const struct Sub0047B2E0View *object) { return sub_0047B2E0(object); }

typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct Unit {u8 bytes[336];} Unit;
#define NI __declspec(noinline)
#define B(p,n) (*(volatile u8*)((u32)(p)+(n)))
#define NB(p,n) (*(u8*)((u32)(p)+(n)))
#define W(p,n) (*(volatile u16*)((u32)(p)+(n)))
#define D(p,n) (*(volatile u32*)((u32)(p)+(n)))
#define P(p,n) ((Unit*)D(p,n))
extern volatile u8 g_00662098[];
#pragma code_seg(".h5ea0")
static NI u8 __cdecl sub_004E5EA0(Unit *unit){
 u16 kind=W(unit,0x64);u8 value;
 if(kind==0x67 && (B(unit,0xdc)&0x10))return 3;
 value=g_00662098[kind];
 if(!value && (B(unit,0xdc)&2) && sub_0047B2E0((struct Sub0047B2E0View*)unit))value=2;
 return value;
}

#pragma code_seg(".ectx")
u8 context5EA0(Unit *unit){return sub_004E5EA0(unit);}
