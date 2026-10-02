#if defined(_MSC_VER)
#define SC __stdcall
#define FAST __fastcall
#define NOINLINE __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define FAST __attribute__((fastcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32; typedef int I32; typedef unsigned char U8; typedef short I16;
typedef struct Point { I16 x,y; } Point;
typedef struct Entry { Point position; U8 unknown4[44]; } Entry;
typedef char stride48_check[sizeof(Entry)==48?1:-1];
extern U8 data_00690100[];
extern U32 data_00695568;
extern Point data_0058D720[];
extern Entry data_00692688[];
extern U32 FAST sub_0040C360(I32 x,I32 other_x,I32 y,I32 other_y);
#pragma code_seg(".scmatch")
static NOINLINE U32 SC sub_00443A20(U32 player,U32 x,volatile I32 y)
{
 I32 position_x,position_y; U32 chosen, best, index;
 Entry *entry;
 if(data_00690100[player*1256U]&0x20) {position_x=(I32)x;position_y=y;x=data_00695568;}
 else {position_x=data_0058D720[player].x;position_y=data_0058D720[player].y;x=8;}
 y=position_y;
 chosen=0; index=1; best=99999999U;
 if(index<=x) {
 entry=data_00692688+1;
 do {
  I32 point_y=((volatile Point *)&entry->position)->y;
  I32 query_y=y;
  I32 point_x=((volatile Point *)&entry->position)->x;
  U32 measured=sub_0040C360(position_x,point_x,query_y,point_y);
  if(measured<=best) {chosen=index;best=measured;}
 } while(++index,++entry,index<=x);
 }
 return chosen;
}
#pragma code_seg(".scctx")
U32 SC context_00443A20(U32 player,U32 x,I32 y) {return sub_00443A20(player,x,y);}
