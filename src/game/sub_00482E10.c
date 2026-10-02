#pragma pack(push,1)
typedef struct Region {
 unsigned short kind,flags,weight;
 unsigned char unused6,edge_count;
 unsigned char unused8[4];
 const unsigned short *edges;
 unsigned char unused10[8];
 short xmin,ymin,xmax,ymax;
 unsigned char unused20[32];
} Region;
typedef struct Context { short count; unsigned char pad[10]; unsigned short tiles[256*256]; unsigned char unused[0x449FC-12-256*256*2]; Region regions[1]; } Context;
#pragma pack(pop)
void __stdcall sub_00482E10(Context *context) {
 int threshold=4;
 int index,active;
 Region *region;
 do {
  int count=context->count;
  threshold+=2;
  index=count-1;
  region=(Region *)((unsigned int)context+(count<<6)+0x449BCu);
  if(index>=0) do {
   Region *best;
   unsigned int edge;
   int best_index,x,y;
   if(!region->weight || region->flags>=0x4000u || region->weight>=threshold || !region->edge_count) goto next;
   best=0;
   for(edge=0;edge<region->edge_count;++edge) {
    Region *neighbor=context->regions+region->edges[edge];
    if(neighbor->weight && neighbor->flags<0x4000u && region->kind==neighbor->kind && (!best || neighbor->weight<best->weight)) best=neighbor;
   }
   if(!best) goto next;
   best_index=((int)((unsigned int)best-(unsigned int)context-0x449FCu))>>6;
   for(y=region->ymin/32;y<region->ymax/32;++y) {
    for(x=region->xmin/32;x<region->xmax/32;++x) {
     unsigned short *tile=context->tiles+y*256+x;
     if(*tile==index) *tile=(unsigned short)best_index;
    }
   }
   best->weight+=region->weight;
   region->weight=0;
   region->kind=0x1FFF;
   if(region->ymin<best->ymin) best->ymin=region->ymin;
   if(region->ymax>best->ymax) best->ymax=region->ymax;
   if(region->xmin<best->xmin) best->xmin=region->xmin;
   if(region->xmax>best->xmax) best->xmax=region->xmax;
 next:
   --region;
  } while(--index>=0);
  active=0;
  for(index=0;index<context->count;++index) if(context->regions[index].weight>0) ++active;
 } while(active>=2500);
}
