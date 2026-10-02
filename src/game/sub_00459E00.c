/* Independent C reconstruction; ordinary context is hypothetical and uncounted. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#define CDECL __cdecl
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#define CDECL __attribute__((cdecl))
#endif
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned u32;
void * CDECL memcpy(void *,const void *,unsigned);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memcpy)
#endif
#pragma pack(push,1)
struct Packet { u8 type,one,two; u32 position; u16 length; u8 payload[128]; };
#pragma pack(pop)
typedef char packet_size_is_137[(sizeof(struct Packet)==137)?1:-1];
typedef void (STDCALL *Send)(void*,unsigned,unsigned);
#define U32(p,n) (*(u32*)((u8*)(p)+(n)))
#define U8(p,n) (*(u8*)((u8*)(p)+(n)))
static NOINLINE unsigned sub_00459E00(void *object,unsigned count) {
 struct Packet packet; unsigned position, limit, selector; const void *data;
 if(!*(Send*)0x0066fc00)return 0;
 position=U32(object,0x38);
 if(count>=128)count=128;
 limit=U32(object,0xc);
 if(position>=limit)return 0;
 if(position+count>limit)count=limit-position;
 limit=U32(object,0x40);
 if(position+count>limit) {U8(object,0x34)&=0xfd;position=limit;count=0;}
 packet.one=U8(object,8);packet.two=U8(object,9);
 data=(void*)U32(object,0x44);selector=U8(object,0x3c);
 packet.position=position;packet.type=4;packet.length=(u16)count;
 memcpy(packet.payload,(const u8*)data+position,count);
 (*(Send*)0x0066fc00)(&packet,count+9,selector);
 return count;
}
unsigned context(void *object,unsigned count) {return sub_00459E00(object,count);}
