/* MSVC static compiler context infers the observed custom register ABI.
 * The ordinary C helper is experimental context, not a game function match. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
typedef union { unsigned int words[2]; struct {short left,top,right,bottom;} sides; } Bounds;
static unsigned int SC_NOINLINE sub_0041A1B0(unsigned char *dialog,unsigned char *event)
{
    unsigned short type=*(unsigned short *)(dialog+0x22);
    unsigned char *origin=dialog;
    unsigned char *auxiliary;
    int extra=0;
    short x,y;
    Bounds bounds;
    if(type!=0) origin=*(unsigned char **)(dialog+0x32);
    x=(short)(*(short *)(event+0xE)-*(short *)(origin+4));
    y=(short)(*(short *)(event+0x10)-*(short *)(origin+6));
    auxiliary=*(unsigned char **)(dialog+0x36);
    if(auxiliary!=0 && (auxiliary[0x18]&8u)) extra=*(short *)(auxiliary+8)-*(short *)(auxiliary+4);
    bounds.words[0]=*(unsigned int *)(dialog+4);
    bounds.words[1]=*(unsigned int *)(dialog+8);
    bounds.sides.right=(short)(bounds.sides.right-extra);
    if(type==13) {
        if(dialog[0x4C]&1u) bounds.sides.bottom=(short)(bounds.sides.bottom-dialog[0x49]);
        else bounds.sides.top=(short)(bounds.sides.top+dialog[0x49]);
    }
    return x>=bounds.sides.left && x<=bounds.sides.right && y>=bounds.sides.top && y<=bounds.sides.bottom;
}
unsigned int context_0041A1B0(unsigned char *dialog,unsigned char *event) { return sub_0041A1B0(dialog,event); }
