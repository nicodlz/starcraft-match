#pragma pack(push,1)
typedef struct {
    unsigned char pad0[24];
    unsigned int flags;
    unsigned char pad1[6];
    unsigned short field22;
    unsigned char pad2[14];
    unsigned char *parent;
} Object;
#pragma pack(pop)
static __declspec(noinline) void __stdcall sub_004180D0(Object *object, unsigned int value)
{
    unsigned char *base = (unsigned char *)object;
    if (object->field22 != 0) base = object->parent;
    if (*(unsigned int *)(base + 24) & 0x20000000u) value = 0;
    *(unsigned int *)(base + 62) = value;
}
void context_004180D0(Object *object, unsigned int value)
{
    sub_004180D0(object,value);
}
