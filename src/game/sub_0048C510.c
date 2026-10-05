#if defined(_MSC_VER)
#define FAST __fastcall
#elif defined(__i386__)
#define FAST __attribute__((fastcall))
#else
#define FAST
#endif
typedef struct Order { struct Order *previous,*next; unsigned char order,pad9; unsigned short type; unsigned int position; void *target; } Order;
Order * FAST sub_0048C510(unsigned char order,unsigned short type,unsigned int position,void *target) {
unsigned int count;
Order *result=*(Order**)0x0064B2E0u;
if(!result) return result;
result->order=order; result->type=type; result->position=position; result->target=target;
if(*(Order**)0x0064B2E0u==result) *(Order**)0x0064B2E0u=result->next;
if(*(Order**)0x0064B2E4u==result) *(Order**)0x0064B2E4u=result->previous;
if(result->previous) result->previous->next=result->next;
if(result->next) result->next->previous=result->previous;
count=*(unsigned int*)0x00641698u+1u;
result->previous=0; result->next=0;
*(unsigned int*)0x00641698u=count;
return result;
}
