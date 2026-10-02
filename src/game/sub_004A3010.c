typedef unsigned int u32;
typedef unsigned char u8;
extern u32 __stdcall sub_004101A8(u32 index,u32 reason);
extern u32 __stdcall sub_0041026E(u32 reason);
#define FLAGS(i) (*(volatile u32 *)(0x57F0B8u+4u*(i)))
#define COUNT(i) flags=FLAGS(i);if(flags&0x10000u){++active;if(!(flags&0x40000u))++other;}
#pragma code_seg(".scmatch")
void sub_004A3010(void) {
    u32 flags=FLAGS(0);
    int active=0,other=0,i;
    volatile u32 *cursor;
    if(flags&0x10000u){active=1;if(!(flags&0x40000u))other=1;}
    COUNT(1) COUNT(2) COUNT(3) COUNT(4) COUNT(5) COUNT(6) COUNT(7)
    active-=other;
    if(active==other) *(volatile u8*)0x581D61u=1;
    else if(active<other) {
        *(volatile u8*)0x581D61u=2;
        sub_0041026E(0x40000006u);
        return;
    }
    cursor=(volatile u32*)0x57F0B8u;
    for(i=0;i<8;++i,++cursor){
        flags=*cursor;
        if((flags&0x10000u)&&!(flags&0x40000u)){
            if((u32)i<8u)sub_004101A8((u32)i,0x40000006u);
        }
    }
}
