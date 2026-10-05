/* Checked unit references and optional links in the reviewed 112-byte record. */
#define SC_SHARED_DECODE_COMPONENT
#include "sub_00479E60.c"
typedef struct Node {View common;u32 extra0;unsigned char *first,*second;u32 extra3;} Node;
typedef char sc_record112_size[(sizeof(Node)==112)?1:-1];
extern Node g_0064B2E8[];
#pragma code_seg(".checked")
static __forceinline unsigned char *decode_checked(int value) {
 unsigned char *unit;
 if(!value)goto invalid;
 unit=(unsigned char*)&g_0059CCA8[((u32)value&0x7FFu)-1u];
 if(!*(u32*)(unit+12))goto invalid;
 if(!unit[77] && unit[78]==1)goto invalid;
 if((u32)unit[165]!=(u32)(value>>11))goto invalid;
 return unit;invalid:return 0;
}
#pragma code_seg(".record")
u32 __fastcall sub_0048A8D0(Node *node,u32 unused,u32 links) {
 u32 value;sub_00479E60(&node->common);
 node->first=decode_checked((int)node->first);
 node->second=decode_checked((int)node->second);
 value=links;if(value) {
  value=node->common.fields[0];if(value)value=(u32)&g_0064B2E8[value-1u];node->common.fields[0]=value;
  value=node->common.fields[1];if(!value){node->common.fields[1]=value;return value;}value=(u32)&g_0064B2E8[value-1u];node->common.fields[1]=value;
 }return value;
}
