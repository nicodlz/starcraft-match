#ifdef _MSC_VER
#define SC_NOINLINE __declspec(noinline)
#define SC_STDCALL __stdcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_STDCALL __attribute__((stdcall))
#endif
static SC_NOINLINE int SC_STDCALL sub_004AAE20(unsigned int *remaining, char *buffer, char **cursor, unsigned int capacity)
{
    unsigned int initial = *remaining;
    unsigned int i = 0, j;
    char *source = *cursor;
    while (i < *remaining && *source != '"') { source++; i++; }
    if (i >= initial) return 0;
    source++; i++;
    j = 0;
    while (i < *remaining && j < capacity && *source != '"') {
        buffer[j] = *source;
        j++; source++; i++;
    }
    if (i >= *remaining || j >= capacity) return 0;
    buffer[j] = 0;
    *cursor = source+1;
    *remaining -= i+1;
    return 1;
}
int context_004AAE20(unsigned int *remaining, char *buffer, char **cursor, unsigned int capacity) { return sub_004AAE20(remaining,buffer,cursor,capacity); }
