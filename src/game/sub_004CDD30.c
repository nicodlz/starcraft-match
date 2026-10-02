typedef unsigned char U8;
typedef int I32;
typedef unsigned int U32;
typedef struct State { U32 a,b; U8 *buffer; I32 used,capacity; U8 *cursor; } State;
extern U8 data_0050286C[];
extern U8 *__stdcall sub_0041006A(I32 size,const U8 *file,U32 line,U32 flags);
extern void __stdcall sub_0041016C(U8 *destination,const U8 *source,U32 size);
extern I32 __stdcall sub_00410070(U8 *buffer,const U8 *file,U32 line,U32 flags);
#pragma code_seg(".scmatch")
static __declspec(noinline) void __stdcall sub_004CDD30(State *state) {
 if((I32)((U32)state->used+512u) >= state->capacity) {
  I32 offset = !state->cursor ? 0 : (I32)((U32)state->cursor-(U32)state->buffer);
  U8 *replacement = sub_0041006A((I32)((U32)state->capacity+10000u),data_0050286C,690,0);
  sub_0041016C(replacement,state->buffer,state->capacity);
  state->capacity = (I32)((U32)state->capacity+10000u);
  sub_00410070(state->buffer,data_0050286C,693,0);
  state->buffer = replacement;
  state->cursor = !offset ? (U8 *)0 : (U8 *)((U32)replacement+(U32)offset);
 }
}
#pragma code_seg(".scctx")
void context_004CDD30(State *state) {sub_004CDD30(state);}
