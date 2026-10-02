typedef unsigned int u32;typedef unsigned short u16;typedef unsigned char u8;typedef int s32;typedef signed char s8;
#pragma pack(push,1)
typedef struct {u16 unused,id,mode;u8 unused_byte,variant;} Record;
#pragma pack(pop)
extern Record *data_005122A0[3];
extern Record *data_005122AC[3];
extern u32 __cdecl sub_0040C799(const char *text,char **end,s32 radix);
extern s32 __cdecl sub_0040A069(s32 character);
#pragma code_seg(".scmatch")
s32 __fastcall sub_004DBC60(const char *text,u32 ignored_edx,u32 table_index,u32 base,u32 alternate,u32 *out){
 char *end;u32 remaining=(u32)sub_0040C799(text,&end,10)-base;
 volatile Record *record;
 (void)ignored_edx;
 if((s32)remaining<0)return 0;
 record=(alternate?data_005122AC:data_005122A0)[table_index];
 while(record->id){
 if(!record->mode && !record->variant){if(remaining--==0)goto selected;}
 ++record;
 }
 return 0;
selected:
 if(end && *end){
 u32 steps=(u32)sub_0040A069((s32)(s8)*end)-0x61u;
 if(steps){do{
 u8 variant;
 --steps;if(!record->id)return 0;
 variant=(record+1)->variant;++record;if(!variant)return 0;
 }while(steps);}
 if(!record->id)return 0;
 }
 *out=record->id;return 1;
}
