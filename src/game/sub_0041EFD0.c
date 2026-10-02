typedef unsigned int U32;
typedef unsigned short U16;
typedef struct SystemTime {U16 year,month,day_of_week,day,hour,minute,second,millisecond;} SystemTime;
typedef struct VersionInfo {U32 fields[13];} VersionInfo;
__declspec(dllimport) void __stdcall api_GetLocalTime(SystemTime *time);
__declspec(dllimport) int __stdcall api_GetUserNameA(char *buffer,U32 *length);
__declspec(dllimport) int __stdcall api_GetComputerNameA(char *buffer,U32 *length);
extern void __stdcall sub_0041EB80(VersionInfo *version);
extern void sub_0041EF00(const char *format,...);
extern const char data_00505D98[];
extern const char data_006CE118[];
#pragma code_seg(".scmatch")
void sub_0041EFD0(void)
{
 struct {U32 lengths[2];SystemTime time;} clock;
 VersionInfo version;
 char user[64];
 char computer[64];
 api_GetLocalTime(&clock.time);
 clock.lengths[0]=64;
 if(!api_GetUserNameA(user,&clock.lengths[0]))user[0]=0;
 clock.lengths[1]=64;
 if(!api_GetComputerNameA(computer,&clock.lengths[1]))computer[0]=0;
 sub_0041EB80(&version);
 sub_0041EF00(data_00505D98,version.fields[4]>>16,version.fields[4]&65535u,version.fields[5]>>16,version.fields[5]&65535u,computer,user,(U32)clock.time.month,(U32)clock.time.day,(int)clock.time.year%100,(U32)clock.time.hour,(U32)clock.time.minute,(U32)clock.time.second,(U32)clock.time.millisecond,data_006CE118);
}
#pragma code_seg()
