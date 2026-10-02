#if defined(_MSC_VER) && !defined(__clang__)
#define PRIVATE_LEAF __declspec(noinline)
#else
#define PRIVATE_LEAF __attribute__((noinline))
#endif
static PRIVATE_LEAF int sub_0048E850(int x) {
 int distance = x / 32;
 int result = 0;
 unsigned char negative = 0;
 distance -= *(unsigned short *)0x0057F1D0u;
 distance -= 10;
 if (distance < 0) { negative = 1; distance = -distance; }
 if (distance > 80) result = 10000;
 else if (distance > 40) result = 5000;
 else if (distance > 20) result = 1000;
 else if (distance > 10) result = 600;
 else if (distance > 5) result = 300;
 else if (distance > 2) result = 100;
 if (negative) result = -result;
 return result;
}
/* Independent compiler context; not counted as a reconstructed routine. */
int compiler_context_0048E850(int x) { return sub_0048E850(x); }
