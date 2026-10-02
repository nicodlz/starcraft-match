#if defined(_MSC_VER) && !defined(__clang__)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif

unsigned int SC_STDCALL sub_0047B340(unsigned int ignored, unsigned short id, unsigned char desired, unsigned char player) {
 unsigned char old;
 if(id<46) old=((unsigned char*)0x58D2B0u)[player*46u+id];
 else old=((unsigned char*)0x58F2FEu)[player*15u+id];
 if(desired>old) {
  if(id<46) ((unsigned char*)0x58D2B0u)[player*46u+id]=desired;
  else if(*(unsigned char*)0x58F440u) ((unsigned char*)0x58F2FEu)[player*15u+id]=desired;
 }
 return 1;
}
