typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Record {volatile u32 index,rank;volatile u8 state,preference,team;u8 tail[25];} Record;
typedef char record36[sizeof(Record)==36?1:-1];
extern Record g_0057EEE0[12],g_0059BDB0[12];
extern volatile u8 g_0066FF34[],g_0057F1B4[],g_0057F1C0[],g_0058D5B0[];
extern volatile u8 g_0057F0B4,g_00596875,g_00596865,g_0059686D,g_00596871,g_00596877;
void *memcpy(void *,const void *,u32);
void *memset(void *,int,u32);
#pragma intrinsic(memcpy,memset)
void sub_004AA190(void);
#define COPY(k) do{if(old[k].state==6){memcpy(&g_0057EEE0[count++],&old[k],36);}}while(0)
#pragma code_seg(".root")
void sub_004AA620(void)
{
 Record old[8];int i,count;Record *out;
 if(!g_0057F0B4)return;
 if(g_00596875 || (!g_0059686D && !g_00596871 && !g_00596877)){sub_004AA190();return;}
 for(i=8;i!=0;){u8 state;--i;state=g_0057EEE0[i].state;if(state==2)g_0057EEE0[i].state=6;else if(state==1)g_0057EEE0[i].state=5;}
 memcpy(old,g_0057EEE0,288);memset(g_0057EEE0,0,432);count=0;
 COPY(0);COPY(1);COPY(2);COPY(3);COPY(4);COPY(5);COPY(6);COPY(7);
 out=&g_0057EEE0[count];
 for(i=0;i<8;++i){u8 state=old[i].state;if(state==5||state==3||state==4||state==7){memcpy(out,&old[i],36);g_0066FF34[(u8)count]=(u8)i;++count;++out;}}
 for(i=12;i!=0;){--i;g_0057EEE0[i].index=i;g_0057EEE0[i].rank=0xFFFFFFFFu;g_0057EEE0[i].team=0;}
 memset(g_0059BDB0,0,432);
 for(i=12;i!=0;){u8 team;--i;g_0059BDB0[i].preference=g_0057EEE0[i].preference;g_0059BDB0[i].state=g_0057EEE0[i].state;team=g_0057EEE0[i].team;g_0059BDB0[i].index=i;g_0059BDB0[i].rank=0xFFFFFFFFu;g_0059BDB0[i].team=team;}
}
