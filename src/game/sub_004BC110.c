typedef unsigned int u32;
typedef char sc_u32_must_be_4_bytes[(sizeof(u32)==4 && sizeof(int)==4) ? 1 : -1];
extern int data_006D59F4;
extern int data_006CDFE4;
extern int data_005998E8;
extern int data_005008F0[];
extern int data_006D5A0C;
extern int data_006D5E3C;
extern void sub_004BBF50(void);
void sub_004BC110(void) {
 int value;
 if (!data_006D59F4) return;
 if (data_006CDFE4) {
  data_005998E8=data_006CDFE4;
  data_006CDFE4=0;
  sub_004BBF50();
  value=data_006CDFE4;
 } else {
  value=data_005998E8;
  data_006CDFE4=value;
 }
 value=(int)((u32)value * 99u) / 100;
 data_006D5E3C=(int)((u32)data_005008F0[value] - (u32)data_006D5A0C);
}
