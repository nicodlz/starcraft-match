#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef struct Node { unsigned char pad[20]; int key; } Node;
typedef struct Heap { Node *slots[126]; int count; } Heap;
typedef char HeapSizeCheck[sizeof(Heap) == 508 ? 1 : -1];
typedef char NodeSizeCheck[sizeof(Node) == 24 ? 1 : -1];
static NOINLINE void sub_00404920(int index, Heap *heap)
{
    int total = heap->count;
    Node *saved = heap->slots[index];
    int child;
    while (index <= total / 2) {
            child = index * 2;
            if (child < total && heap->slots[child]->key > heap->slots[child + 1]->key)
                ++child;
            if (saved->key <= heap->slots[child]->key)
                break;
            heap->slots[index] = heap->slots[child];
            total = heap->count;
            index = child;
    }
    heap->slots[index] = saved;
}
/* Hypothetical ordinary compiler context only, not a reconstructed caller. */
void context_00404920(Heap *heap, int index) { sub_00404920(index, heap); }
