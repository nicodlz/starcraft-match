/* Independently authored C; context selects observed ESI ABI and is excluded. */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
/* Independent C scaffold, direct allocation call requires relocation/linking. */
typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char Byte;
extern void *STDCALL sub_0041006A(U32 size,const char *file,U32 line,U32 flags);
#pragma code_seg(".scmatch")
static NOINLINE void sub_00457CA0(Byte *state)
{
 int kind=*(short *)(state+0x20);
 if(kind>=9 && kind<=12) *(U32 *)(state+0x2E)=0x004574E0;
 else *(U32 *)(state+0x2E)=0x00457480;
 *(U16 *)(state+0x24)=0;
 *(void **)(state+0x26)=sub_0041006A(12,(const char *)0x00504BD0,0x273,0);
}
#pragma code_seg(".scctx")
void context_00457CA0(Byte *state) {sub_00457CA0(state);}
