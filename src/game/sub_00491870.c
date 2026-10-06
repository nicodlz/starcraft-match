/* Whole BYTE/WORD table selector; observed EAX object input, no stack arguments. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 g_00664080[];
extern u8 g_0058D2C3[];
extern u8 g_0058F32D[];
#pragma code_seg(".select")
static __declspec(noinline) u32 __stdcall sub_00491870(const u8 *object) {
 u32 type=*(const u16*)(object+100);
 if(g_00664080[4*type]&0x40)return 64000;
 switch(type) {
 case 9: {if(g_0058D2C3[(u32)object[76]*46])return 64000;break;}
 case 1: {if(g_0058D2C3[(u32)object[76]*46+2])return 64000;break;}
 case 8: {if(g_0058D2C3[(u32)object[76]*46+3])return 64000;break;}
 case 12: {if(g_0058D2C3[(u32)object[76]*46+4])return 64000;break;}
 case 45: {if(g_0058D2C3[(u32)object[76]*46+12])return 64000;break;}
 case 46: {if(g_0058D2C3[(u32)object[76]*46+13])return 64000;break;}
 case 67: {if(g_0058D2C3[(u32)object[76]*46+21])return 64000;break;}
 case 71: {if(g_0058D2C3[(u32)object[76]*46+25])return 64000;break;}
 case 60: {if(g_0058F32D[(u32)object[76]*15])return 64000;break;}
 case 34: {if(g_0058F32D[(u32)object[76]*15+4])return 64000;break;}
 case 63: {if(g_0058F32D[(u32)object[76]*15+2])return 64000;break;}
 }
 return 51200;
}
#pragma code_seg(".context")
u32 __stdcall context_00491870(const u8 *object) {return sub_00491870(object);}
