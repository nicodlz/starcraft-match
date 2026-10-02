#include <stddef.h>
struct View004B2B30 {
    unsigned char a[0x19c];
    volatile unsigned int field19c,field1a0,field1a4;
    unsigned char b[0xa4];
    volatile unsigned int field24c;
};
_Static_assert(offsetof(struct View004B2B30,field24c)==0x24c,"offset");
__attribute__((fastcall)) void sub_004B2B30(struct View004B2B30 *p,unsigned int index)
{
    p->field19c=((volatile unsigned int *)0x00581E44u)[index];
    p->field1a0=((volatile unsigned int *)0x00581EA4u)[index];
    p->field1a4=((volatile unsigned int *)0x00581E74u)[index];
    unsigned int value=((volatile unsigned int *)0x00581F04u)[index];
    value+=((volatile unsigned int *)0x00581ED4u)[index];
    p->field24c=value;
}
