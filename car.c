#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<time.h>
#define WHEEL_SPAN 100
#define RIMS 5
#define MUD_RAD 25
#define TYRE_RAD 20.0
#define DISC_RAD 15.0
#define LAND_TOP 10
#define WIN_LEFT 10
#define WIN_WIDTH 500
#define WIN_TOP 100
#define WIN_HEIGHT 300
#define WIN_BORDER BROWN
#define LAND_FILL WIN_BORDER

#define CAR_WIDTH 2*(CAR_XTRA+MUD_RAD)+WHEEL_SPAN
#define CAR_HEIGHT 90
#define CAR_XTRA 10
#define CAR_BORDER GREEN
#define CAR_FILL GREEN
#define BGCOLOR WHITE
#define LX1 0
#define LY1 250
#define LX2 WIN_WIDTH
#define LY2 250
#define GAP 5

float bcx=LX1+MUD_RAD+CAR_XTRA;
float bcy=LY1-TYRE_RAD;
float fcx=LX1+3*MUD_RAD+CAR_XTRA+WHEEL_SPAN;
float fcy=LY1-TYRE_RAD;
float rshift=10;

float shift=0;
void drawrims();

void drawcontrols(){
   outtextxy(WIN_LEFT+GAP,WIN_TOP+LY1+GAP,"f=front,b=back,q=quit");
}
void drawdashed(float x1,float y1,float x2,float y2,int pixels,int toggle){
     float dx,dy,max;
     int i=1;
     int counter=0;
     dy=abs(y1-y2);
     dx=abs(x1-x2);
     max=dy>dx?dy:dx;
     dy=dy/max;
     dx=dx/max;
     while(i++<max){
         x1+=dx;
         y1+=dy;
         if(counter==pixels){
             toggle=!toggle;
             counter=0;
         }
         if(counter<=pixels&&toggle)
             putpixel(x1,y1,BLUE);
         counter++;
     }
}
void drawcar(){

    int temp=getcolor();
    setcolor(CAR_BORDER);
    line(WIN_LEFT+bcx+MUD_RAD,WIN_TOP+bcy,WIN_LEFT+fcx-MUD_RAD,WIN_TOP+fcy);
    line(WIN_LEFT+bcx-(MUD_RAD+CAR_XTRA),WIN_TOP+bcy,WIN_LEFT+bcx-MUD_RAD,WIN_TOP+bcy);
    line(WIN_LEFT+fcx+(MUD_RAD+CAR_XTRA),WIN_TOP+fcy,WIN_LEFT+fcx+MUD_RAD,WIN_TOP+fcy);

    arc(WIN_LEFT+bcx,WIN_TOP+bcy,-180,-90,MUD_RAD+CAR_XTRA);
    arc(WIN_LEFT+fcx,WIN_TOP+fcy,-90,0,MUD_RAD+CAR_XTRA);
    arc(WIN_LEFT+bcx,WIN_TOP+bcy,-180,0,MUD_RAD);
    arc(WIN_LEFT+fcx,WIN_TOP+fcy,-180,0,MUD_RAD);

    arc(WIN_LEFT+(bcx+fcx)/2,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA),-180,0,(fcx-bcx)/2);
    arc(WIN_LEFT+(bcx+fcx)/2,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA),-180,0,(fcx-bcx)/2-GAP);
    line(WIN_LEFT+bcx+GAP,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA),WIN_LEFT+fcx-GAP,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA));
    line(WIN_LEFT+(bcx+fcx)/2,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA)-((fcx-bcx)/2-GAP)
,WIN_LEFT+(bcx+fcx)/2,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA));
    temp=getcolor();

    setcolor(BLACK);
    circle(WIN_LEFT+bcx,WIN_TOP+bcy,TYRE_RAD);
    circle(WIN_LEFT+fcx,WIN_TOP+fcy,TYRE_RAD);

    floodfill(WIN_LEFT+bcx+TYRE_RAD-1,WIN_TOP+bcy,BLACK);
    floodfill(WIN_LEFT+fcx+TYRE_RAD-1,WIN_TOP+fcy,BLACK);

    setcolor(RED);
    circle(WIN_LEFT+fcx,WIN_TOP+fcy,DISC_RAD);
    circle(WIN_LEFT+bcx,WIN_TOP+bcy,DISC_RAD);

    setcolor(RED);
    floodfill(WIN_LEFT+fcx,WIN_TOP+fcy,RED);
    floodfill(WIN_LEFT+bcx,WIN_TOP+bcy,RED);

    drawrims();



    setcolor(CAR_FILL);
    floodfill(WIN_LEFT+(fcx-bcx)/2+bcx,WIN_TOP+LY1-TYRE_RAD-1,CAR_BORDER);
    setcolor(BLUE);
    floodfill(WIN_LEFT+(fcx-bcx)/2+bcx+1,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA)-1,CAR_BORDER);
    floodfill(WIN_LEFT+(fcx-bcx)/2+bcx-1,WIN_TOP+LY1-(TYRE_RAD+MUD_RAD+CAR_XTRA)-1,CAR_BORDER);
    setcolor(temp); 
}
void drawrims(){
    float angle=6.28/RIMS;
    int i;
    setcolor(WHITE);
    for(i=0;i<RIMS;++i){
        line(WIN_LEFT+bcx,WIN_TOP+bcy,WIN_LEFT+bcx+DISC_RAD*cos(shift+i*angle),WIN_TOP+bcy+DISC_RAD*sin(shift+i*angle));
        line(WIN_LEFT+fcx,WIN_TOP+fcy,WIN_LEFT+fcx+DISC_RAD*cos(shift+i*angle),WIN_TOP+fcy+DISC_RAD*sin(shift+i*angle));
    }
}
void drawwindow(){
    int temp=getcolor();
    setcolor(WIN_BORDER);
    line(WIN_LEFT,WIN_TOP,WIN_LEFT+WIN_WIDTH,WIN_TOP);
    line(WIN_LEFT,WIN_TOP,WIN_LEFT,WIN_TOP+WIN_HEIGHT);
    line(WIN_LEFT+WIN_WIDTH,WIN_TOP,WIN_LEFT+WIN_WIDTH,WIN_TOP+WIN_HEIGHT);
    line(WIN_LEFT,WIN_TOP+WIN_HEIGHT,WIN_LEFT+WIN_WIDTH,WIN_TOP+WIN_HEIGHT);
    setcolor(temp);
}
void incx(int len,int *arr,float inc){
    int i;
    for(i=0;i<2*len;++i)
        if(i%2==0)
            arr[i]+=inc;
}
void drawland(){
        int temp=getcolor();
        setcolor(LAND_FILL);
        line(WIN_LEFT+LX1,WIN_TOP+LY1+2,WIN_LEFT+LX2,WIN_TOP+LY2+2);
        setcolor(LAND_FILL);
        floodfill(WIN_LEFT+LX1+1,WIN_TOP+LY1+3,LAND_FILL);
        setcolor(temp);
}
void movecar(float vel,float pixels,float secs){
    float dist=vel*secs;
    float i=0,j;
    int sign=0;
    char ch;
    int toggle=1;
    int maxleft=WIN_LEFT+bcx;
    int maxright=WIN_LEFT+WIN_WIDTH-fcx;
    while(i<=pixels){
        setbkcolor(BGCOLOR);
        drawwindow();
        drawland();
        drawcontrols();
        drawcar();
        for(j=WIN_LEFT;j+GAP<WIN_LEFT+WIN_WIDTH;j+=GAP)
            drawdashed(WIN_LEFT+j,WIN_TOP,WIN_LEFT+j+2*GAP,WIN_TOP+LY1,9,toggle=!toggle);
    
  /*  ch=getchar();
        if(ch=='f'||ch=='F')
           sign=1;
        else if(ch=='b'||ch=='B')
           sign=-1;
        else if(ch=='q'||ch=='q')
           break;
        else
           sign=0;*/
//        if(bcx>maxleft&&fcx<maxright){
           sign=1;
            bcx+=dist*sign;
            fcx+=dist*sign;
            i+=dist*sign;
            shift+=dist/TYRE_RAD*sign;
  //      }
        delay(100);
    }
}
int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    movecar(1,200,10);
    setcolor(WHITE);
    getchar();
    closegraph();
}
