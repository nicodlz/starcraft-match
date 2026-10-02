#if defined(_MSC_VER)
#define FASTCALL __fastcall
#define NOINLINE __declspec(noinline)
#else
#define FASTCALL __attribute__((fastcall))
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int U32;
typedef unsigned char U8;
typedef struct Entry004439B0 { U8 unknown0[4]; U8 base; U8 unknown5[3]; U32 amount; U8 unknown12[36]; } Entry004439B0;
typedef char size_assert_004439B0[sizeof(Entry004439B0)==48 ? 1 : -1];
extern Entry004439B0 data_00692688[250];
extern U32 FASTCALL sub_00432320(U32 player);
#pragma code_seg(".scmatch")
static NOINLINE U32 sub_004439B0(U32 index,U32 player)
{
 Entry004439B0 *entry;
 U32 amount,current;
 entry= index && index<250 ? data_00692688+index : 0;
 if(!entry) return 0;
 amount=entry->amount/500;
 current=sub_00432320(player);
 if(amount<current) amount=entry->base;
 else {current=(U32)entry->base*2; if(amount>current) amount=current;}
 return amount;
}
#pragma code_seg(".scctx")
U32 context_004439B0(U32 index,U32 player) {return sub_004439B0(index,player);}
#pragma code_seg()
