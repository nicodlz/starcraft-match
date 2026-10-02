/* Opaque views for the observed pointer and coordinate accesses. */
#if defined(_MSC_VER)
#define SUB0048AAC0_FASTCALL __fastcall
#elif defined(__i386__)
#define SUB0048AAC0_FASTCALL __attribute__((fastcall))
#else
#define SUB0048AAC0_FASTCALL
#endif

typedef struct {
    unsigned char opaque[0x14];
    unsigned short x_14, y_16;
} Sub0048AAC0Image;

typedef struct {
    unsigned char opaque[0x0c];
    Sub0048AAC0Image *image_0c;
} Sub0048AAC0Target;

typedef struct Sub0048AAC0Bullet {
    unsigned char opaque[4];
    struct Sub0048AAC0Bullet *next_04;
    unsigned char opaque_08[0x50];
    unsigned short x_58, y_5a;
    Sub0048AAC0Target *target_5c;
    unsigned int opaque_60;
    Sub0048AAC0Target *other_64;
} Sub0048AAC0Bullet;

#if defined(_MSC_VER) || defined(__i386__)
typedef char Sub0048AAC0PointerWidth[(sizeof(void *) == 4) ? 1 : -1];
typedef char Sub0048AAC0BulletSize[(sizeof(Sub0048AAC0Bullet) == 0x68) ? 1 : -1];
#endif

void SUB0048AAC0_FASTCALL sub_0048AAC0(Sub0048AAC0Target *target)
{
    Sub0048AAC0Bullet *bullet = *(Sub0048AAC0Bullet **)0x0064DEC4u;
    while (bullet) {
        if (bullet->target_5c == target) {
            bullet->x_58 = target->image_0c->x_14;
            bullet->y_5a = target->image_0c->y_16;
            bullet->target_5c = 0;
        }
        if (bullet->other_64 == target) bullet->other_64 = 0;
        bullet = bullet->next_04;
    }
}
