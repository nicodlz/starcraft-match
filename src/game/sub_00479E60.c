/* Reviewed i386 reference conversions; opaque fields retain their observed widths. */
typedef unsigned int u32;
typedef struct Unit {unsigned char bytes[336];} Unit;
typedef struct Sprite {unsigned char bytes[36];} Sprite;
typedef struct View {u32 fields[24];} View;
typedef char sc_shared_size[(sizeof(View)==96)?1:-1];
typedef char sc_shared_unit_stride[(sizeof(Unit)==336)?1:-1];
typedef char sc_shared_sprite_stride[(sizeof(Sprite)==36)?1:-1];
extern Unit g_0059CCA8[];
extern Sprite g_00629D98[];
#pragma code_seg(".unit")
static u32 unpack_unit(u32 value) {return value?(u32)&g_0059CCA8[(value&0x7FFu)-1u]:0;}
#pragma code_seg(".restore")
__declspec(noinline) static void __fastcall sub_00479E60(View *state) {
 u32 value=state->fields[3];
 if(value)value=(u32)&g_00629D98[value-1u];
 state->fields[3]=value;
 state->fields[5]=unpack_unit(state->fields[5]);
 state->fields[23]=unpack_unit(state->fields[23]);
}

#ifndef SC_SHARED_DECODE_COMPONENT
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_00479E60(View *state) {sub_00479E60(state);}
#endif
