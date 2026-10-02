/* Independently reconstructed pinned Windows i386 1.16.1 leaf. */
#if defined(_MSC_VER) && !defined(__clang__)
#define STDCALL __stdcall
#elif defined(__i386__)
#define STDCALL __attribute__((stdcall))
#else
#define STDCALL
#endif
struct Surface004E1D20 { short width; short unknown; unsigned char *pixels; };
#if defined(_MSC_VER) && !defined(__clang__)
typedef unsigned int Sub004E1D20Size;
#define FIELD_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
typedef __SIZE_TYPE__ Sub004E1D20Size;
#define FIELD_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
void *memset(void *,int,Sub004E1D20Size);
typedef char Sub004E1D20WordWidth[(sizeof(short)==2)?1:-1];
typedef char Sub004E1D20DwordWidth[(sizeof(unsigned int)==4)?1:-1];
#if defined(__i386__) || (defined(_MSC_VER) && !defined(__clang__))
typedef char Sub004E1D20PixelOffset[(FIELD_OFFSET(struct Surface004E1D20,pixels)==4)?1:-1];
#endif
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memset)
#endif
void STDCALL sub_004E1D20(short x, int y, unsigned short width, unsigned short height)
{
 /* The observed signed low-WORD comparison is intentional. */
 unsigned int i=0;
 while ((int)(short)i < (int)height) {
  struct Surface004E1D20 *surface=*(struct Surface004E1D20 **)0x006cf4a8;
  int stride=surface->width;
  unsigned int color=*(unsigned char *)0x006cf4ac;
  int row=(short)((unsigned int)y+i);
  unsigned char *pixels=surface->pixels+row*stride;
#if defined(_MSC_VER) && !defined(__clang__)
  memset(pixels+x,color,width);
#else
  {
   volatile unsigned char *destination=pixels+x;
   unsigned int remaining=width;
   while (remaining) {
    *destination++=(unsigned char)color;
    --remaining;
   }
  }
#endif
  ++i;
 }
}
