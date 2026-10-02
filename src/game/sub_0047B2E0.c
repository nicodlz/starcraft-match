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
unsigned int compiler_context_0047B2E0(const struct Sub0047B2E0View *object) { return sub_0047B2E0(object); }
