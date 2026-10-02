#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned short u16;
typedef unsigned int u32;
#pragma pack(push,2)
typedef struct { u16 f00,f02; u32 f04,f08; u16 f0c,f0e,f10; } Format;
#pragma pack(pop)
typedef char format_is_18_bytes[sizeof(Format)==18 ? 1 : -1];
typedef int (STDCALL *Method)(void *,Format *);
void * __cdecl memset(void *,int,unsigned int);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memset)
#endif
int sub_004BBA90(void)
{
 Format format;
 void *object;
 memset(&format,0,sizeof(format));
 object=*(void **)0x006d59f8;
 format.f00=1;
 format.f02=2;
 format.f04=0x5622;
 format.f0e=0x10;
 format.f0c=4;
 format.f08=0x15888;
 return (*(Method ** )object)[14](object,&format);
}
