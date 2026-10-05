/* Target i386 compilation retains the original SHL count behavior. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Player {u32 id;u8 type, pad, group;u8 rest[29];} Player;
extern Player g_0057EEE4[];
extern u16 g_0057F1DA;
typedef char Player_size_must_be_36[(sizeof(Player) == 36) ? 1 : -1];
#pragma code_seg(".mark")
__declspec(noinline) static void __fastcall sub_0048FC70(u32 group) {
#define MARK(n) if (g_0057EEE4[n].type == 2 && (u32)g_0057EEE4[n].group == group) g_0057F1DA |= (u16)(1u << (g_0057EEE4[n].id));
 MARK(0) MARK(1) MARK(2) MARK(3) MARK(4) MARK(5) MARK(6) MARK(7)
#undef MARK
}
#pragma code_seg(".anchor")
void __fastcall compiler_anchor_0048FC70(u32 group) {sub_0048FC70(group);}
