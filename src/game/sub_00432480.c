#if defined(_MSC_VER)
#define LEAF static __declspec(noinline)
#else
#define LEAF static __attribute__((noinline))
#endif
typedef struct { unsigned char pad[0x64]; unsigned short type; } View;
LEAF unsigned int sub_00432480(unsigned short type, const View *object) {
unsigned char flags=((const unsigned char*)0x006637A0u)[type];
if(flags&2u) {if(((const unsigned char*)0x006637A0u)[object->type]&2u) return 1u;}
else if(flags&1u) {if(((const unsigned char*)0x006637A0u)[object->type]&1u) return 1u;}
else {if(((const unsigned char*)0x006637A0u)[object->type]&4u) return 1u;}
*(unsigned int*)0x0066FF60u=0x19u;
return 0u;
}
unsigned int context_00432480(unsigned short type,const View *object) {return sub_00432480(type,object);}
