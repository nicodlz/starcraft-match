#if defined(_MSC_VER)
#define REGISTER_INPUT __fastcall
#else
#define REGISTER_INPUT __attribute__((fastcall))
#endif
typedef struct View {
    unsigned char pad[0x64]; unsigned short type;
    unsigned char pad2[0xdc-0x66]; unsigned int flags;
    unsigned char pad3[0x115-0xe0]; unsigned char boost; unsigned char slow;
} View;
#if defined(__clang__) || defined(__GNUC__)
#define VIEW_OFFSET(field) __builtin_offsetof(View, field)
#else
#define VIEW_OFFSET(field) ((unsigned int)&(((View *)0)->field))
#endif
typedef char check_type_offset[VIEW_OFFSET(type) == 0x64 ? 1 : -1];
typedef char check_flags_offset[VIEW_OFFSET(flags) == 0xdc ? 1 : -1];
typedef char check_boost_offset[VIEW_OFFSET(boost) == 0x115 ? 1 : -1];
typedef char check_slow_offset[VIEW_OFFSET(slow) == 0x116 ? 1 : -1];
/* ECX input; full EAX arithmetic result, consumed as AL by reviewed callers. */
unsigned int REGISTER_INPUT sub_0047B850(const View *unit)
{
    unsigned int type = unit->type;
    unsigned int movement = ((const unsigned char *)0x006644F8u)[type];
    unsigned int value = ((const unsigned char *)0x006C9E20u)[movement];
    int modifier = 0;
    if (unit->boost) modifier = 1;
    if (unit->flags & 0x10000000u) ++modifier;
    if (unit->slow) --modifier;
    if (modifier > 0) return value + value;
    if (modifier < 0) return value - (value >> 2);
    return value;
}
