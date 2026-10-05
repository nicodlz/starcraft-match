/* Clear and link the reviewed 2,000-record pool; all pointer math is i386 DWORD math. */
typedef unsigned int u32;
typedef struct Node {struct Node *next,*previous;u32 payload[3];} Node;
typedef char sc_pool_node_size[(sizeof(Node)==20)?1:-1];
extern Node g_006416A0[];
extern Node *g_0064B2E0,*g_0064B2E4;
extern u32 g_00641698;
void *__cdecl memset(void*,int,u32);
#pragma intrinsic(memset)
#pragma code_seg(".insert")
static void insert(Node *node,Node *position) {
 if(position) {
  Node **slot;
  if(g_0064B2E4==position)g_0064B2E4=node;
  node->next=position;
  node->previous=position->previous;
  slot=&position->previous;
  if(*slot)(*slot)->next=node;
  *slot=node;
 }else {g_0064B2E4=node;g_0064B2E0=node;}
}
#pragma code_seg(".pool")
void sub_0048C590(void) {
 u32 node;u32 count;
 memset(g_006416A0,0,40000);
 g_0064B2E0=0;g_0064B2E4=0;
 node=(u32)g_006416A0+20u;count=400;
 do {
  insert((Node*)(node-20u),g_0064B2E0);
  insert((Node*)node,g_0064B2E0);
  insert((Node*)(node+20u),g_0064B2E0);
  insert((Node*)(node+40u),g_0064B2E0);
  insert((Node*)(node+60u),g_0064B2E0);
  node+=100u;
 }while(--count);
 g_00641698=0;
}
