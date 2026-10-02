#if defined(_MSC_VER)
#define SUB004AADA0_FASTCALL __fastcall
#elif defined(__i386__)
#define SUB004AADA0_FASTCALL __attribute__((fastcall))
#else
#define SUB004AADA0_FASTCALL
#endif
typedef unsigned int U32;
typedef unsigned short U16;
typedef struct View {unsigned char type, value; U16 mode;} View;
U32 SUB004AADA0_FASTCALL sub_004AADA0(const View *p)
{
 U32 flags=0;
 if(p->type==9 && p->mode==2) flags=0x10;
 else if(p->type==0x80 && p->value) {
  flags=((U32)p->value<<24)|0x00800020;
  if(p->mode==2) flags|=0x10;
 }
 if(*(U32 *)0x006D0F14) flags|=0x80;
 return flags;
}
