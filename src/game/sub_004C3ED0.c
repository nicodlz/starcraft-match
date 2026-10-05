/* Reviewed 12-player initialization, 8-player group calls and 11-player mode15. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Player {u8 kind,opaque,group,tail[33];} Player;
#define PLAYERS ((Player*)0x0057EEE8u)
#define MATRIX ((u8(*)[12])0x0058D634u)
#define MASKS ((u32*)0x0057F1ECu)
#define BYTE_AT(a) (*(volatile u8*)(a))
extern void __stdcall sub_0045AB20(u8 group,u8 value);
extern void __fastcall sub_0045A9B0(u32 unused,u8 group,u8 enabled);
#pragma intrinsic(memset)
void * __cdecl memset(void*,int,unsigned int);
#pragma code_seg(".rel")
void sub_004C3ED0(void) {
 int i,j;u32 bit;u8 group,value,enabled,flag;
 memset(MATRIX,0,144);
 for(i=7;i>=0;--i)MATRIX[i][i]=1;
 for(i=11;i>=0;--i) {
  u8 mode=BYTE_AT(0x596874u);
  MATRIX[11][i]=1;MATRIX[i][11]=1;
  if(mode==1 && BYTE_AT(0x596877u)==0) {
   for(j=7;j>=0;--j) {
    if(i!=j && PLAYERS[i].kind==1 && PLAYERS[j].kind==1) {
     MATRIX[i][j]=2;MATRIX[j][i]=2;
    }
   }
  }
 }
 bit=1;
 for(i=0;i<12;++i) {
  MASKS[i]=bit;
  if(PLAYERS[i].kind==3 || PLAYERS[i].kind==7) {
   for(j=0;j<12;++j) {MATRIX[i][j]=1;MATRIX[j][i]=1;}
  }
  bit<<=1;
 }
 if(!BYTE_AT(0x59686Du) && !BYTE_AT(0x596871u) && !BYTE_AT(0x596877u)) {
  for(group=1;group<=4;++group) {
   flag=BYTE_AT(0x58D5B7u+group);
   value=(flag&2)?(u8)(1+((flag&4)!=0)):0;
   enabled=BYTE_AT(0x58D5B7u+group)&8;
   sub_0045AB20(group,value);
   sub_0045A9B0(0,group,enabled);
  }
 }
 if(BYTE_AT(0x596865u)==15) {
  for(i=0;i<11;++i) {
   for(j=0;j<11;++j) {
    if(PLAYERS[i].kind && PLAYERS[j].kind) {
     int same=PLAYERS[i].group==PLAYERS[j].group;
     MATRIX[i][j]=(u8)(same?2:0);
     if(same)MASKS[i]|=1u<<j;
    }
   }
  }
 }
}
