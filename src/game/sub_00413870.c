/* Whole80-byte switch including both local tables; AX type + DWORD stack mode. */
typedef unsigned short u16;
typedef unsigned int u32;
#pragma code_seg(".helper")
static __declspec(noinline) u32 __stdcall sub_00413870(u16 type,u32 mode) {
 switch(type) {
 case 131: case 143:return mode;
 case 132: case 133: case 144: case 146:return 1;
 default:return 0;
 }
}
#pragma code_seg(".context")
u32 __stdcall context_00413870(u16 type,u32 mode){return sub_00413870(type,mode);}
