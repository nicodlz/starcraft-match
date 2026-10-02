/* MSVC static compiler context infers the observed custom register ABI.
 * The ordinary C helper is experimental context, not a game function match. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
static void SC_NOINLINE sub_004977C0(unsigned char *sprite,int *out)
{
    unsigned char *image=*(unsigned char **)(sprite+0x1C);
    unsigned char *frame;
    int x,y,right,bottom;
    while(image != 0 && !(image[0xC]&0x20u)) image=*(unsigned char **)(image+4);
    if(image == 0) return;
    frame=*(unsigned char **)(image+0x2C)+*(unsigned short *)(image+0x1A)*8+6;
    out[0]=*(short *)(image+0x1C);
    out[1]=*(short *)(image+0x1E);
    out[2]=*(short *)(image+0x1C)+frame[2]-1;
    out[3]=*(short *)(image+0x1E)+frame[3]-1;
    image=*(unsigned char **)(image+4);
    while(image != 0) {
        if(image[0xC]&0x20u) {
            frame=*(unsigned char **)(image+0x2C)+*(unsigned short *)(image+0x1A)*8+6;
            x=*(short *)(image+0x1C);
            y=*(short *)(image+0x1E);
            right=x+frame[2]-1;
            bottom=y+frame[3]-1;
            if(x<out[0]) out[0]=x;
            if(right>out[2]) out[2]=right;
            if(y<out[1]) out[1]=y;
            if(bottom>out[3]) out[3]=bottom;
        }
        image=*(unsigned char **)(image+4);
    }
}
void context_004977C0(unsigned char *sprite,int *out) { sub_004977C0(sprite,out); }
