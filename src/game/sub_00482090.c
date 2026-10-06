/* Complete WORD-neighbor leaf; private EAX out/EBX x/ECX y, DWORD stack board. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
extern u16 g_0057F1D4;
extern u16 g_0057F1D6;
#pragma code_seg(".near")
static __declspec(noinline) void __stdcall sub_00482090(u16 *out,int x,int y,const u8 *board) {
 const u16 *tile=(const u16*)(board+12+2*((u32)y*256+(u32)x));
 int next_x,next_y;
 out[0]=y>0?tile[-256]:8191;
 out[1]=x>0?tile[-1]:8191;
 next_x=(int)((u32)x+1);
 out[2]=next_x<(int)g_0057F1D4?tile[1]:8191;
 next_y=(int)((u32)y+1);
 out[3]=next_y<(int)g_0057F1D6?tile[256]:8191;
 out[4]=y>0&&x>0?tile[-257]:8191;
 out[5]=y>0&&next_x<(int)g_0057F1D4?tile[-255]:8191;
 out[6]=next_y<(int)g_0057F1D6&&x>0?tile[255]:8191;
 out[7]=next_y<(int)g_0057F1D6&&next_x<(int)g_0057F1D4?tile[257]:8191;
}
#pragma code_seg(".context")
void __stdcall context_00482090(u16 *out,int x,int y,const u8 *board){sub_00482090(out,x,y,board);}
