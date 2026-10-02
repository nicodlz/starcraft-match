#if defined(_MSC_VER) && !defined(__clang__)
void *memcpy(void *destination, const void *source, unsigned int size);
#pragma intrinsic(memcpy)
#else
typedef struct __attribute__((packed, may_alias)) Sub004C3090Word {
    unsigned int value;
} Sub004C3090Word;
#endif
typedef struct Sub004C3090State {
    const unsigned char *base;
    unsigned int position;
    unsigned int unknown_08;
    unsigned int unknown_0c;
    unsigned int end;
} Sub004C3090State;
typedef char Sub004C3090StateSize[(sizeof(Sub004C3090State) == 20) ? 1 : -1];
unsigned int sub_004C3090(void *destination, const unsigned int *requested,
                        Sub004C3090State *state)
{
    unsigned int amount = *(const volatile unsigned int *)&state->end;
    unsigned int maximum = *(const volatile unsigned int *)requested;
    unsigned int position = state->position;
    amount -= position;
    if (maximum < amount)
        amount = maximum;
#if defined(_MSC_VER) && !defined(__clang__)
    memcpy(destination, state->base + position, amount);
#else
    {
        const unsigned char *source = state->base + position;
        unsigned char *output = (unsigned char *)destination;
        unsigned int words = amount / 4;
        unsigned int bytes = amount % 4;
        while (words != 0) {
            ((volatile Sub004C3090Word *)output)->value =
                ((const volatile Sub004C3090Word *)source)->value;
            source += 4;
            output += 4;
            --words;
        }
        while (bytes != 0) {
            *(volatile unsigned char *)output =
                *(const volatile unsigned char *)source;
            ++source;
            ++output;
            --bytes;
        }
    }
#endif
    state->position += amount;
    return amount;
}
