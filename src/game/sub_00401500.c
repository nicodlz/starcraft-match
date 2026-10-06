typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct Unit {u8 bytes[336];} Unit;
#define NI __declspec(noinline)
#define B(p,n) (*(volatile u8*)((u32)(p)+(n)))
#define NB(p,n) (*(u8*)((u32)(p)+(n)))
#define W(p,n) (*(volatile u16*)((u32)(p)+(n)))
#define D(p,n) (*(volatile u32*)((u32)(p)+(n)))
#define P(p,n) ((Unit*)D(p,n))
#pragma code_seg(".h1500")
NI u32 __fastcall sub_00401500(Unit *unit){
 int slot=(int)NB(unit,0xa4)%5;Unit *other;
 return W(unit,0x98+slot*2)!=0xe4 ||
 (NB(unit,0xa6)==0x25 && (NB(unit,0xdc)&2) && (other=P(unit,0xec)) && !(NB(other,0xdc)&1)) ||
 (NB(unit,0x4d)==0x1f && (NB(unit,0xdc)&2) && (other=P(unit,0x5c)) && !(NB(other,0xdc)&1));
}
