typedef struct { unsigned int unknown; unsigned int index; unsigned int *value; unsigned int size; } Event;
void __stdcall sub_004C3C90(const Event *event) {
 unsigned int index=event->index;
 unsigned int value;
 if(index>=8u) return;
 if(!event->value || event->size<4u) value=3u;
 else { value=*event->value; if(!value) value=3u; }
 *(unsigned int *)(0x5971E4u+index*4u)=value;
}
