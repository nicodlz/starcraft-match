/* Independent C reconstruction. Callback entry corroborated by code-address dispatch. */
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned u32;
typedef int (STDCALL *Predicate)(int,int);
int STDCALL sub_00414230(unsigned direction,u16 *unused,int x,int y,u8 *bits) {
 int accepted;Predicate predicate=*(Predicate*)0x006d0c74;
 if(!predicate) {
  u32 offset=*(u32*)0x006d0f08*y+x;
  accepted=(((u16*)*(u32*)0x006d0e84)[offset]&0x7ff0)==0x10;
 }else accepted=predicate(x,y);
 if(accepted){*bits|=1u<<direction;}
 return 1;
}
