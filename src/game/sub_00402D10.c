/* Preserve partial clear widths, unsigned references and inter-record access order. */
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef char sc_dword_width[(sizeof(U32)==4)?1:-1];
typedef char sc_word_width[(sizeof(U16)==2)?1:-1];
extern U8 g_0059CCA8[];
#pragma code_seg(".unit")
static __forceinline U32 pack_00402D10(U32 address)
{
    U32 index;
    if (!address) return 0;
    index=(address-(U32)g_0059CCA8)/0x150+1;
    if (index>0x6a4) return 0;
    return ((U32)*(U8 *)(address+0xa5)<<11)|index;
}
#pragma code_seg(".link")
static __forceinline U32 link_00402D10(U32 address,U32 base)
{if(!address)return 0;return ((address-base)>>5)+1;}
void __cdecl _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#define PACK_NODE(unit_offset,next_offset,previous_offset) \
    fields[unit_offset]=pack_00402D10(fields[unit_offset]); \
    fields[next_offset]=link_00402D10(fields[next_offset],base); \
    fields[previous_offset]=link_00402D10(fields[previous_offset],base)
#pragma code_seg(".pool")
void __stdcall sub_00402D10(U8 *block)
{
    U32 base=(U32)block;
    U8 *node=*(U8 **)(block+32000);
    U32 *fields;
    unsigned int groups;
    while (node) {
        node[8]=0;
        *(U32 *)(node+12)=0;
        *(U16 *)(node+16)=0;
        *(U16 *)(node+18)=0;
        *(U16 *)(node+20)=0;
        *(U16 *)(node+22)=0;
        *(U16 *)(node+24)=0;
        *(U32 *)(node+28)=0;
        node=*(U8 **)node;
    }
    fields=(U32 *)(block+0x4c);
    groups=200;
    do {
        PACK_NODE(-16,-19,-18); _WriteBarrier();
        PACK_NODE(-8,-11,-10); _WriteBarrier();
        PACK_NODE(0,-3,-2); _WriteBarrier();
        PACK_NODE(8,5,6); _WriteBarrier();
        PACK_NODE(16,13,14);
        fields+=40;
    } while (--groups);
    *(U32 *)(block+32000)=link_00402D10(*(U32 *)(block+32000),base);
}
