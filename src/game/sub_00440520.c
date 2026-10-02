/* Private compiler-context hypothesis; only the static leaf is measured. */
#if defined(_MSC_VER) && !defined(__clang__)
#define LEAF static __declspec(noinline)
#define INLINE static __forceinline
#else
#define LEAF static __attribute__((noinline))
#define INLINE static __attribute__((always_inline)) inline
#endif
INLINE unsigned char ground_weapon_00440520(unsigned char *unit) {
 unsigned short type=*(unsigned short *)(unit+0x64); unsigned char weapon; unsigned char *child;
 if(type==103 && !(unit[0xdc]&0x10)) return 130;
 weapon=((unsigned char *)0x6636b8u)[type];
 if(weapon!=130) return weapon;
 child=*(unsigned char **)(unit+0x70);
 if(!child) return 130;
 return ((unsigned char *)0x6636b8u)[*(unsigned short *)(child+0x64)];
}
INLINE unsigned char air_weapon_00440520(unsigned char *unit) {
 unsigned short type=*(unsigned short *)(unit+0x64); unsigned char weapon; unsigned char *child;
 weapon=((unsigned char *)0x6616e0u)[type];
 if(weapon!=130) return weapon;
 child=*(unsigned char **)(unit+0x70);
 if(!child) return 130;
 return ((unsigned char *)0x6616e0u)[*(unsigned short *)(child+0x64)];
}
LEAF void sub_00440520(unsigned char *unit) { unsigned char ground=ground_weapon_00440520(unit); unsigned char air=air_weapon_00440520(unit); unsigned int g,a;
if(ground!=130) {
 if(air!=130) { g=((unsigned int *)0x656a18u)[ground]; a=((unsigned int *)0x656a18u)[air]; if(g<a) { *(unsigned int *)0x6955dcu=g; return; } *(unsigned int *)0x6955dcu=a; }
 else *(unsigned int *)0x6955dcu=((unsigned int *)0x656a18u)[ground];
} else if(air!=130) *(unsigned int *)0x6955dcu=((unsigned int *)0x656a18u)[air];
else *(unsigned int *)0x6955dcu=0;
 }
void compiler_context_00440520(unsigned char *unit) { sub_00440520(unit); }
