#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned char U8;
typedef unsigned int U32;
typedef struct { U8 unknown[0x34]; int maximum; volatile int current; U32 unknown3c; int vx; int vy; U8 unknown48[2]; U8 direction; } State;
static NOINLINE void sub_00402180(State *state,int delta)
{
    int value=(int)((U32)state->current+(U32)delta);
    unsigned int direction;
    if(value>state->maximum) {
        if(state->current!=state->maximum) {
            direction=(U32)state->direction<<3;
            state->current=state->maximum;
            state->vx=((int)((U32)*(int *)(0x00512d28+direction)*(U32)state->maximum))>>8;
            state->vy=((int)((U32)*(int *)(0x00512d2c+direction)*(U32)state->maximum))>>8;
        }
        return;
    }
    if(value<0) {
        if(state->current!=0) {
            state->current=0;
            state->vx=0;
            state->vy=0;
        }
        return;
    }
    if(state->current!=value) {
        direction=(U32)state->direction<<3;
        state->current=value;
        state->vx=((int)((U32)*(int *)(0x00512d28+direction)*(U32)value))>>8;
        state->vy=((int)((U32)*(int *)(0x00512d2c+direction)*(U32)value))>>8;
    }
}
typedef char assert_state_size[sizeof(State)==0x4c?1:-1];
State *context_00402180(State *state,int delta)
{
    sub_00402180(state,delta);
    return state;
}
