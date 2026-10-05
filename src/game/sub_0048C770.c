/* Reviewed descending traversal of all 2,000 twenty-byte records. */
typedef unsigned int u32;
typedef struct Node {u32 next,prev,p0,p1,unit;} Node;
typedef char sc_pool_node_size[(sizeof(Node)==20)?1:-1];
extern u32 g_006416A0[],g_0064B2E0;
#pragma code_seg(".unit")
static u32 unpack_unit(u32 value) {if(!value)return 0;return 0x0059CB58u+(value&0x7FFu)*336u;}
#pragma code_seg(".link")
static u32 unpack_link(u32 value) {if(!value)return 0;return (u32)g_006416A0-20u+value*20u;}
#pragma code_seg(".pool")
void sub_0048C770(void) {
 Node *cursor=(Node*)&g_0064B2E0;
 do {
  u32 value=cursor[-1].unit;--cursor;
  cursor->unit=unpack_unit(value);
  cursor->next=unpack_link(cursor->next);
  cursor->prev=unpack_link(cursor->prev);
 }while(cursor!=(Node*)g_006416A0);
}
