/* Independent complete C. The observed local writes remain observable;
   no initialization, cycle detector or bounds check is added. */
typedef unsigned int u32;
struct Node { u32 next, id; };
#pragma code_seg(".scmatch")
void sub_0042F600(void)
{
    volatile u32 visited[1024];
    struct Node *current = *(struct Node **)0x006bee84;
    if (current) {
        u32 base = *(u32 *)0x006bee8c;
        do {
            u32 next = current->next;
            visited[current->id - 1u] = 1;
            if (!next) break;
            current = (struct Node *)(base + (next << 7) - 128u);
        } while (current);
    }
}
