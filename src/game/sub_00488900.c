extern volatile unsigned int table_582144[256];
extern volatile unsigned int table_5821A4[256];
extern volatile unsigned int table_5821D4[256];
extern volatile unsigned int table_582234[256];
extern volatile unsigned int table_582264[256];
extern volatile unsigned int table_5822C4[256];
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define B(a) (*(volatile u8 *)(a))
#define W(a) (*(volatile u16 *)(a))
#define D(a) (*(volatile u32 *)(a))
#pragma code_seg(".h900")
static __declspec(noinline) u32 __stdcall sub_00488900(u8 player,u8 category) {
 u32 first,second;
 switch(category) {
 case 0:first=table_582144[player];second=table_5821A4[player];break;
 case 1:first=table_5821D4[player];second=table_582234[player];break;
 case 2:first=table_582264[player];second=table_5822C4[player];break;
 default:return 0;
 }
 if(first<second)second=first;
 return second;
}

#pragma code_seg(".context")
u32 __stdcall context_00488900(u8 player,u8 category) {return sub_00488900(player,category);}
