typedef struct Pair { int marker; unsigned int key; } Pair;
typedef char PairSizeCheck[sizeof(Pair) == 8 ? 1 : -1];
int sub_00453680(const Pair *first, const Pair *second)
{
    Pair left = *first;
    Pair right = *second;
    if (left.marker == -1)
        return right.marker != -1;
    if (right.marker == -1) {
        return -1;
    } else {
        if (right.key > left.key) return -1;
        return right.key < left.key;
    }
}
