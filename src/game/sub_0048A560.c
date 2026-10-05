/* Reviewed private EAX input; ordinary C context induces the observed ABI. */
typedef unsigned int u32;
typedef struct Node {struct Node *next,*previous;u32 opaque,state;u32 tail[24];} Node;
typedef char sc_node112_size[(sizeof(Node)==112)?1:-1];
extern Node *g_0064DEC4,*g_0064DEAC,*g_0064EED8,*g_0064EEDC;
extern u32 g_0064DEBC;
#pragma code_seg(".release")
__declspec(noinline) static void sub_0048A560(Node *node) {
 Node *position;
 if(node->state)return;
 if(g_0064DEC4==node)g_0064DEC4=node->previous;
 if(g_0064DEAC==node)g_0064DEAC=node->next;
 if(node->next)node->next->previous=node->previous;
 if(node->previous)node->previous->next=node->next;
 node->next=0;node->previous=0;
 position=g_0064EED8;
 if(position) {
  if(g_0064EEDC==position)g_0064EEDC=node;
  node->next=position;node->previous=position->previous;
  if(position->previous)position->previous->next=node;
  position->previous=node;
 }else {g_0064EEDC=node;g_0064EED8=node;}
 --g_0064DEBC;
}
#pragma code_seg(".anchor")
Node *__stdcall compiler_anchor_0048A560(Node *node){sub_0048A560(node);return node;}
