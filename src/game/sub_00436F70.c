#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned char u8;
typedef int i32;
typedef struct Unit Unit;
typedef struct Link Link;
struct Unit { u8 p0[0x34]; i32 speed; u8 p38[0xa4]; unsigned int status; };
struct Link { Link *next; u8 p4[8]; Unit *unit; };
typedef struct Group { u8 p0[4]; u8 player; u8 p5[0x1f]; Unit *captain; u8 p28[8]; Link *members; } Group;
#if defined(_MSC_VER) && !defined(__clang__)
#define OFFSET(T,F) ((unsigned int)&((T *)0)->F)
#else
#define OFFSET(T,F) __builtin_offsetof(T,F)
#endif
typedef char speed_width[(sizeof(i32) == 4) ? 1 : -1];
typedef char group_player_offset[(OFFSET(Group,player) == 4) ? 1 : -1];
typedef char group_captain_offset[(OFFSET(Group,captain) == 0x24) ? 1 : -1];
typedef char group_members_offset[(OFFSET(Group,members) == 0x30) ? 1 : -1];
typedef char unit_speed_offset[(OFFSET(Unit,speed) == 0x34) ? 1 : -1];
typedef char unit_status_offset[(OFFSET(Unit,status) == 0xdc) ? 1 : -1];
typedef char link_unit_offset[(OFFSET(Link,unit) == 0xc) ? 1 : -1];
void STDCALL sub_00436F70(Group *group)
{
    Unit *ground, *air, *unit;
    Link *link;
    i32 ground_speed;
    volatile i32 air_speed;
    if (!(*(u8 *)(0x690100 + (unsigned int)group->player * 0x4e8) & 0x20)) return;
    ground = 0;
    ground_speed = 99999999;
    air = 0;
    air_speed = 99999999;
    if (group->captain) {
        if (group->captain->status & 4) { air = group->captain; air_speed = air->speed; }
        else { ground = group->captain; ground_speed = ground->speed; }
    }
    link = group->members;
    while (link) {
        unit = link->unit;
        if (unit->status & 4) {
            if (unit->speed < air_speed) { air_speed = unit->speed; air = unit; }
        } else {
            if (unit->speed < ground_speed) { ground_speed = unit->speed; ground = unit; }
        }
        link = link->next;
    }
    if (!ground) ground = air;
    group->captain = ground;
}
