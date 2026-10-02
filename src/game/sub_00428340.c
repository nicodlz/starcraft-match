#if defined(_MSC_VER)
#define SC_STD __stdcall
#else
#define SC_STD __attribute__((stdcall))
#endif
typedef struct { unsigned char p00[0xd0]; unsigned int value_d0; } View;
unsigned int SC_STD sub_00428340(const View *object) {
    return object->value_d0 == 0;
}
