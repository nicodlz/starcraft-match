typedef struct { unsigned char prefix[0x64]; unsigned short kind; } Unit;
int __stdcall sub_00428860(unsigned int unused) {
 Unit **entry=(Unit **)0x597208u;
 (void)unused;
 do {
  Unit *unit=*entry;
  if(unit) {
   unsigned short kind=unit->kind;
   if(kind==0x1E || kind==0x19) return 0;
  }
  ++entry;
 } while((int)entry<0x597238);
 return 1;
}
