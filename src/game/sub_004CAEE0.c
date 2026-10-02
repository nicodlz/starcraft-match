#if defined(_MSC_VER) && !defined(__clang__)
void *__cdecl memset(void *, int, unsigned int);
void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memset, memcpy)
#endif
typedef struct { unsigned int limit; unsigned int source; unsigned int unknown; unsigned int size; } Context;
unsigned int __stdcall sub_004CAEE0(const Context *context, unsigned int size, unsigned char *output) {
 unsigned int count, source, limit;
 if(size>20u) return 0;
 output+=4;
 #if defined(_MSC_VER) && !defined(__clang__)
 memset(output,0,20);
#else
 {
  unsigned int i;
  for(i=0;i<5u;++i) ((unsigned int *)output)[i]=0u;
 }
#endif
 count=context->size;
 source=context->source;
 limit=context->limit;
 if(source+count<=limit) {
  #if defined(_MSC_VER) && !defined(__clang__)
  memcpy(output,(const void *)source,count);
#else
  {
   unsigned int words=count/4u, bytes=count%4u;
   unsigned char *destination=output;
   const unsigned char *input=(const unsigned char *)source;
   while(words) {
    *(unsigned int *)destination=*(const unsigned int *)input;
    destination+=4;
    input+=4;
    --words;
   }
   while(bytes) {
    *destination++=*input++;
    --bytes;
   }
  }
#endif
  return 1;
 }
 return 0;
}
