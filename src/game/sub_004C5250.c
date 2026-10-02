typedef struct { unsigned char p[0x0C]; unsigned int time; unsigned char q[0x0C]; unsigned char flags; } Action;
unsigned int __fastcall sub_004C5250(Action *action) {
 unsigned int index=*(unsigned int *)0x6509B0u;
 unsigned char flag=((unsigned char *)0x6509B8u)[index];
 if(flag) return 0;
 flag=action->flags;
 if(flag&1) { action->flags=(unsigned char)(flag&0xFEu); return 1; }
 if((*((unsigned char **)0x6509ACu))[0x948]&0x10) return 1;
 ((unsigned int *)0x650980u)[index]=action->time;
 ((unsigned char *)0x6509B8u)[index]=1;
 action->flags|=1;
 return 0;
}
