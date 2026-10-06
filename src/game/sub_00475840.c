extern volatile unsigned char g_006616E0[];
#pragma code_seg(".kind")
static __declspec(noinline) unsigned char __stdcall sub_00475840(unsigned char *object) {
 unsigned int next;unsigned char result=g_006616E0[*(unsigned short*)(object+100)];
 if(result==130){next=*(unsigned int*)(object+112);if(!next)return 130;return g_006616E0[*(unsigned short*)(next+100)];}
 return result;
}

#pragma code_seg(".kctx")
unsigned int __stdcall context_00475840(unsigned char *object,unsigned int n){unsigned int total=0;while(n--)total+=sub_00475840(object);return total;}
