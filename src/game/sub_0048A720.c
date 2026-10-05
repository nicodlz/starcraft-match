/* Preserve reviewed DWORD states, link insertion order and machine EAX value. */
typedef unsigned int u32;
typedef struct Node {struct Node *next,*previous;u32 opaque,state;u32 tail[24];} Node;
typedef char sc_node112_size[(sizeof(Node)==112)?1:-1];
extern Node g_0064B2E8[100];
extern Node *g_0064EED8,*g_0064EEDC,*g_0064DEC4,*g_0064DEAC;
extern u32 g_0064DEBC;
#define SCAN(op) \
 index=0;status=(u32)g_0064B2E8+124u; \
 do { \
  if(*(u32*)(status-112u) op 0)break; \
  if(*(u32*)status op 0){++index;break;} \
  if(*(u32*)(status+112u) op 0){index+=2;break;} \
  if(*(u32*)(status+224u) op 0){index+=3;break;} \
  if(*(u32*)(status+336u) op 0){index+=4;break;} \
  status+=560u;index+=5; \
 }while((int)status<(int)((u32)g_0064B2E8+11324u));
#pragma code_seg(".pool")
u32 sub_0048A720(void) {
 int index;u32 status,count;Node *position,*node;
 SCAN(==)
 if(index==100) {g_0064EED8=0;g_0064EEDC=0;}
 else {
  position=g_0064B2E8+index;
  g_0064EED8=position;g_0064EEDC=position;
  if(++index<100) {
   node=g_0064B2E8+index;
   do {
    if(!node->state) {
     if(g_0064EEDC==position)g_0064EEDC=node;
     node->next=position;node->previous=position->previous;
     if(position->previous)position->previous->next=node;
     position->previous=node;position=node;
    }
    ++node;
   }while((int)(u32)node<(int)0x0064DEA8u);
  }
 }
 SCAN(!=)
 if(index==100) {g_0064DEC4=0;g_0064DEAC=0;g_0064DEBC=0;return (u32)index;}
 position=g_0064B2E8+index;count=1;
 g_0064DEC4=position;g_0064DEAC=position;
 position->next=0;position->previous=0;g_0064DEBC=1;
 if(++index<100) {
  node=g_0064B2E8+index;
  do {
   if(node->state) {
    int same=g_0064DEAC==position;node->next=0;node->previous=0;
    if(same)g_0064DEAC=node;
    node->next=position;node->previous=position->previous;
    if(position->previous)position->previous->next=node;
    position->previous=node;position=node;++count;
   }
   ++node;
  }while((int)(u32)node<(int)0x0064DEA8u);
  g_0064DEBC=count;return (u32)node;
 }return (u32)index;
}
