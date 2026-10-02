#pragma pack(push,1)
typedef struct { unsigned char p[12]; unsigned char visible; } Sprite;
typedef struct { unsigned char p[12]; Sprite *sprite; unsigned char q[60]; unsigned char player; unsigned char r[11]; short x,y; unsigned char s[128]; unsigned int status; unsigned char t[4]; unsigned int detected; } Unit;
#pragma pack(pop)
static __declspec(noinline) unsigned int sub_004E5E30(const Unit *target, const Unit *observer) {
 unsigned int mask=1u<<observer->player;
 int x,y;
 unsigned int *tiles;
 if(target) {
  if((target->status&0x300u) && !(target->detected&mask)) return 0;
  return target->sprite->visible & (unsigned char)mask;
 }
 y=observer->y/32;
 x=observer->x/32;
 tiles=*(unsigned int **)0x6D1260u;
 return ~(tiles[y* *(unsigned short *)0x57F1D4u+x]&255u)&mask;
}
unsigned int context_004E5E30(const Unit *target, const Unit *observer) { return sub_004E5E30(target,observer); }
