typedef unsigned char Byte00437E00;
#if defined(_MSC_VER) && !defined(__clang__)
#define FASTCALL __fastcall
#define NOINLINE __declspec(noinline)
#define WORDQUALIFIER
#else
#define FASTCALL __attribute__((fastcall))
#define NOINLINE __attribute__((noinline))
#define WORDQUALIFIER volatile
#endif
static NOINLINE unsigned int FASTCALL sub_00437E00(Byte00437E00 *state) {
 Byte00437E00 *target=*(Byte00437E00 **)(state+0x1c);
 WORDQUALIFIER unsigned short kind;
 if(target!=0) {
  kind=*(unsigned short *)(target+0x64);
  if(kind!=0x59 && kind!=0x5a && kind!=0x5f && kind!=0x5e && kind!=0x5d && kind!=0x60) return 1;
 }
 target=*(Byte00437E00 **)(state+0x20);
 if(target!=0) {
  kind=*(unsigned short *)(target+0x64);
  if(kind!=0x59 && kind!=0x5a && kind!=0x5f && kind!=0x5e && kind!=0x5d && kind!=0x60) return 1;
 }
 return 0;
}

unsigned int context00437E00(Byte00437E00 *p) { return sub_00437E00(p); }
