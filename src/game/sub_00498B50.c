typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef struct Image Image;
typedef struct Frame { u8 unknown[8]; u16 group; u8 unknownA[2]; u16 flags; u8 unknownE[12]; u16 index; } Frame;
typedef struct Container { u8 unknown[0x18]; Frame *frame; } Container;
struct Image {
    u32 unknown0; Image *next;
    u8 unknown8[2],kind,unknownB;
    u16 flags; s8 x,y;
    u8 unknown10[0x20],state0,state1,unknown32[2];
    u32 draw,resource; Container *container;
};
typedef struct Object { u8 unknown[0x1C]; Image *head; } Object;
typedef struct Pair { u32 value,unknown; } Pair;
typedef struct Triple { u32 value0,value1,unknown; } Triple;
typedef struct Point { int x,y; } Point;
static __inline Point offsets(Frame *frame)
{
    u32 group=frame->group, index=frame->index;
    u8 *data=((u8 **)0x005211E0)[group];
    Point point;
    data+=((u32 *)(data+8))[index];
    point.x=(s8)data[0];
    if (frame->flags&2) point.x=-point.x;
    point.y=(s8)data[1];
    return point;
}
static __declspec(noinline) void __stdcall sub_00498B50(Object *object,u8 flip)
{
    Image *p=object->head;
    u16 flags;
    u8 kind;
    Frame *frame;
    u8 *base,*data;
    Point point;
    u32 index;
    while (p) {
        flags=p->flags;
        if (((flags>>1)&1)!=flip) {
            kind=p->kind;
            flags=(u16)((flags&0xFFFD)|((u16)(flip&1)<<1));
            p->flags=flags;
            p->resource=((Pair *)0x00512514)[kind].value;
            index=kind*3;
            if (flags&2) p->draw=((u32 *)0x005125A4)[index+1];
            else p->draw=((u32 *)0x005125A4)[index];
            if (kind==0x11) { p->state0=0x30; p->state1=2; }
            flags|=1;
            p->flags=flags;
            if (flags&0x80) {
                point=offsets(p->container->frame);
                if (p->x!=(s8)point.x || p->y!=(s8)point.y) {
                    flags|=1;
                    p->x=(s8)point.x; p->y=(s8)point.y;
                    p->flags=flags;
                }
            }
        }
        p=p->next;
    }
}
void experiment_00498B50(Object *object,u8 flip) { sub_00498B50(object,flip); }
