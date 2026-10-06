typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef char dword_size[sizeof(u32)==4?1:-1];
typedef char word_size[sizeof(u16)==2?1:-1];
#define OBJECTS sub_00597208
extern u8 *sub_00597208[12];
#define POSITIONS sub_006CA94C
extern u32 sub_006CA94C[12];
#define TYPES ((u16*)0x006CAD7C)
#pragma code_seg(".scmatch")
void sub_00424540(void) {
 int i;
 for(i=0;i<12;++i) {
  u8 *object=OBJECTS[i];
  POSITIONS[i]=object?*(u32*)(object+8):0;
  TYPES[i]=object?*(u16*)(object+100):228;
 }
}
