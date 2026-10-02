typedef struct Pair { unsigned int key; unsigned int value; } Pair;
unsigned int sub_0042D400(void)
{
    Pair *pairs = (Pair *)0x006c4a30;
    unsigned int index = *(unsigned int *)0x006c4a2c;
    Pair held = pairs[index];
    unsigned int parent = index >> 1;
    while (index > 1) {
        if (pairs[parent].key >= held.key) break;
        pairs[index] = pairs[parent];
        index = parent;
        parent >>= 1;
    }
    pairs[index].value = held.value;
    pairs[index].key = held.key;
    return parent;
}
