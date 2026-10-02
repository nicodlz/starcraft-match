typedef unsigned int u32;
extern u32 __stdcall sub_00411E4E(u32,u32,u32*,u32*,u32);
extern u32 __stdcall sub_00411E54(u32,u32,u32,u32,u32);
extern u32 __stdcall sub_00411E48(u32,u32,u32,u32);
#pragma code_seg(".scmatch")
void sub_0041D420(void) {
    u32 object,height;
    if(sub_00411E4E(0,0,&object,&height,0)) {
        sub_00411E54(object,*(volatile u32*)0x6CEFF4u,height,640,*(volatile u32*)0x6D5E18u);
        sub_00411E48(0,object,0,0);
    }
}
