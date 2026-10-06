typedef unsigned char u8;
typedef unsigned int u32;
#define MODE (*(volatile u8 *)0x596865)
#define MAXIMUM (*(volatile u8 *)0x596875)
#pragma code_seg(".helper")
static __declspec(noinline) u8 sub_00484FC0(u8 team) {
 u8 count=0; const volatile u8 *p=(const volatile u8 *)0x57f008;
 do {u8 t=p[-34]; p-=36; if(t==team) {t=*p; if(t==6 || t==9) ++count;} }while(p!=(const volatile u8 *)0x57eee8);
 return count;
}
#pragma code_seg(".context")
u8 context_00484FC0(void) {
 u32 team;u8 total=0;
 for(team=1;team<=MAXIMUM;++team)total+=sub_00484FC0((u8)team);
 return total;
}
