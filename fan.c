#include<stdio.h>
#include<graphics.h>
#include<math.h>
void fan(){
    int shift=60,angle=0;
    while(1){
       setbkcolor(BLACK);
       setcolor(WHITE);
       line(100,100,100,140);
       line(80,140,120,140);
       setcolor(RED);
       pieslice(100,100,-110+angle,-10+angle,30);
       setcolor(GREEN);
       pieslice(100,100,-230+angle,-130+angle,30);
       setcolor(BLUE);
       pieslice(100,100,-350+angle,-250+angle,30);
       setcolor(WHITE);
       pieslice(100,100,-360,0,5);
       angle+=shift;
       delay(100);
    }
}
int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    fan();
    getchar();
    closegraph();
}
