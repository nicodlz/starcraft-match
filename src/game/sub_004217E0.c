typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { short x, y; } point;
typedef struct { point position; u8 flags, special; short pad; } entry;
typedef struct {
    u8 pad00[0x38];
    point current;
    u8 pad3c[4];
    point target;
    u32 rectangle_active;
    short left, top, right, bottom;
    u8 pad50[0x20];
    short count;
    u8 special, pad73;
    entry entries[32];
} view;
static __declspec(noinline) void __stdcall sub_004217E0(view *p, short x, short y, u8 flags)
{
    int hit, i;
    point pair;
    if (x == p->current.x && y == p->current.y) return;
    hit = 0;
    if (p->rectangle_active &&
        (((x == p->left || x == p->right) && y >= p->top && y <= p->bottom) ||
         ((y == p->top || y == p->bottom) && x >= p->left && x <= p->right)) ||
        (x == p->target.x && y == p->target.y)) {
        flags = 255;
        hit = 1;
        p->special = 1;
    }
    if (p->count >= 32) return;
    if (!hit) {
        pair.x = x;
        pair.y = y;
        for (i = 0; i < p->count; ++i) {
            if (*(u32 *)&pair == *(u32 *)&p->entries[i].position) {
                p->entries[i].flags &= flags;
                return;
            }
        }
    }
    p->entries[p->count].position.x = x;
    p->entries[p->count].position.y = y;
    p->entries[p->count].flags = flags;
    p->entries[p->count].special = (u8)hit;
    ++p->count;
}
void __stdcall context_004217E0(view *p, short x, short y, u8 flags)
{
    sub_004217E0(p, x, y, flags);
}
