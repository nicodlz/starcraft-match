typedef unsigned int u32;
extern u32 data_006D5DC0, data_006D5DC4;
extern const char data_005055D4[];
extern u32 __stdcall sub_00410070(u32,const char*,u32,u32);
#pragma code_seg(".scmatch")
void sub_00448AD0(void)
{
    if(data_006D5DC0) {
        sub_00410070(data_006D5DC0,data_005055D4,0x59,0);
        data_006D5DC0=0;
    }
    if(data_006D5DC4) {
        sub_00410070(data_006D5DC4,data_005055D4,0x5d,0);
        data_006D5DC4=0;
    }
}
#pragma code_seg()
