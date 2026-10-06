typedef short s16;
typedef struct R {s16 x,y,r,b,w,h;} R;
#ifdef _MSC_VER
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
static NI int sub_0041CF60(R *s,R *d) {
 if(s->x>=s->w || s->y>=s->h || s->r<0 || s->b<0) return 1;
 if(s->x<0) {d->x-=s->x;s->x=0;}
 if(s->r>=s->w) s->r=s->w-1;
 if(s->y<0) {d->y-=s->y;s->y=0;}
 if(s->b>=s->h) s->b=s->h-1;
 if(d->x<0) {s->x-=d->x;d->x=0;} else if(d->x>=d->w) return 1;
 if(d->y<0) {s->y-=d->y;d->y=0;} else if(d->y>=d->h) return 1;
 d->r=s->r-s->x+d->x;d->b=s->b-s->y+d->y;
 if(d->r<0 || d->b<0) return 1;
 d->r=d->r-d->w+1;
 if(d->r>0) s->r-=d->r;
 d->b=d->b-d->h+1;
 if(d->b>0) s->b-=d->b;
 s->h=s->b-s->y+1;s->w=s->r-s->x+1;
 return 0;
}
int context(R *s,R *d) {return sub_0041CF60(s,d);}
