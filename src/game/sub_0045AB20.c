typedef unsigned char u8;
typedef struct Player { u8 type; u8 unknown; u8 group; u8 rest[33]; } Player;
#define PLAYERS ((Player *)0x0057eee8)
#define MATRIX ((u8 (*)[12])0x0058d634)
void __stdcall sub_0045AB20(u8 group, u8 value)
{
 int i;
 int j;
 if (group<1 || group>4) return;
 for(i=0;i<8;++i) {
  if(PLAYERS[i].group==group && PLAYERS[i].type==2) {
   for(j=0;j<8;++j) {
    if(value || i!=j) {
     if(PLAYERS[j].group==group && PLAYERS[j].type==2) MATRIX[i][j]=value;
    }
   }
  }
 }
}
