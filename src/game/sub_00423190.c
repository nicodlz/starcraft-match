/* The compiler context below is a source-shape hypothesis, not a game caller. */
#if defined(_MSC_VER)
#define SUB00423190_NOINLINE __declspec(noinline)
#else
#define SUB00423190_NOINLINE __attribute__((noinline))
#endif

typedef struct {
    unsigned char opaque[0x0e];
    unsigned char flags_0e;
} Sub00423190Image;

typedef struct Sub00423190View {
    unsigned char opaque[0x0c];
    Sub00423190Image *image_0c;
    unsigned char opaque_10[0x54];
    unsigned short field_64;
    unsigned char opaque_66[0x1a];
    struct Sub00423190View *parent_80;
} Sub00423190View;

#if defined(_MSC_VER) || defined(__i386__)
typedef char Sub00423190PointerWidth[(sizeof(void *) == 4) ? 1 : -1];
typedef char Sub00423190ViewSize[(sizeof(Sub00423190View) == 0x84) ? 1 : -1];
#endif

static SUB00423190_NOINLINE int
sub_00423190(Sub00423190View **list, Sub00423190View **output)
{
    int count = 0;
    Sub00423190View *object = *list;
    Sub00423190View *selected;
    if (object) {
        selected = *(Sub00423190View **)0x00597248u;
        do {
            if (object->field_64 == 0x23 && object->parent_80 == selected &&
                !(object->image_0c->flags_0e & 0x20)) {
                output[count] = object;
                ++count;
                if (count >= 12) break;
            }
            object = *++list;
        } while (object);
    }
    return count;
}

/* Not reconstructed, not counted: ordinary C keeps the internal leaf reachable
   so VC7.1 can choose the measured EDX/ESI argument convention. */
int source_context_00423190(Sub00423190View **list, Sub00423190View **output)
{
    return sub_00423190(list, output);
}
