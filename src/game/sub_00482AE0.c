typedef unsigned int u32;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned char u8;
extern volatile u16 g_0057F1D4;
extern volatile u16 g_0057F1D6;
void __fastcall sub_00482AE0(u32 unused, u32 value, u8 *grid, volatile s16 *bounds, u16 wanted) {
    {
        int bottom=bounds[3];
        int y=bounds[1];
        if(y<bottom) do {
            int x=bounds[0];
            if(x<bounds[2]) {
                int next=x+1;
                u16 *at=(u16 *)(grid+10+((u32)y*256u+(u32)x)*2u);
                do {
                    if(at[1]==wanted &&
                       ((y>0 && value==(u32)at[-255]) ||
                        (next>1 && value==(u32)at[0]) ||
                        (next<(int)g_0057F1D4 && value==(u32)at[2]) ||
                        (y+1<(int)g_0057F1D6 && value==(u32)at[257])))
                        at[1]=(u16)value;
                    ++x; ++at; ++next;
                } while(x<bounds[2]);
            }
            ++y;
        } while(y<bounds[3]);
    }
    {
        int y=bounds[1];
        while(y<bounds[3]) {
            int x=bounds[0];
            if(x<bounds[2]) {
                int next=x+1;
                u16 *at=(u16 *)(grid+10+((u32)y*256u+(u32)x)*2u);
                do {
                    if(at[1]==wanted &&
                       (((y>0 && value==(u32)at[-255]) ||
                        (next>1 && value==(u32)at[0])) ||
                        ((next<(int)g_0057F1D4 && value==(u32)at[2]) ||
                        (y+1<(int)g_0057F1D6 && value==(u32)at[257]))))
                        at[1]=(u16)value;
                    ++x; ++at; ++next;
                } while(x<bounds[2]);
            }
            ++y;
        }
    }
}
