typedef struct Node {unsigned char pad[8];struct Node *next,*prev;unsigned char x,y;} Node;
unsigned long __fastcall sub_0047D5F0(Node *node)
{
 unsigned short index=(unsigned short)((node->y*17+node->x)&0x3ff);
 Node *volatile *table=(Node *volatile *)0x00658B10;
 if(!table[index]) {
  table[index]=node;
  node->next=0;
  node->prev=0;
  return index;
 }
 node->next=table[index];
 node->prev=0;
 {Node *head=table[index]; if(head) head->prev=node;}
 table[index]=node;
 return index;
}
