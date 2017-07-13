#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<time.h>
void showclock(int x,int y,int rad){
    int i,j=0;
    char text[3];
    int secs=0,hrs=0,mins=0;
    double step=6.28/60.0,secangle=0,minangle=0,hourangle=0,toggle=1;
    while(j++<1000){
        setbkcolor(BLACK);
        for(i=0;i<12;++i){
             sprintf(text,"%d",i+1);
             outtextxy(x+rad*cos(i*6.28/12.0-3.14/3.0)-5,y+rad*sin(i*6.28/12.0-3.14/3.0)-3,text);
        }
        secs+=1;
        if(secs==60){
            minangle+=step;
            secs=0;
            mins++;
        }
        if(mins==60){
            hourangle+=step;
            mins=0;
            hrs+=1;
        }
        setcolor(GREEN);
        line(x,y,x+rad/2.5*cos(i*6.28/12.0-1.57+hourangle),y+rad/2.5*sin(i*6.28/12.0-1.57+hourangle));
        setcolor(RED);
        line(x,y,x+rad/2*cos(i*6.28/12.0-1.57+minangle),y+rad/2*sin(i*6.28/12.0-1.57+minangle));
        setcolor(BROWN);
        line(x,y,x+rad*cos(i*6.28/12.0-1.57+secangle),y+rad*sin(i*6.28/12.0-1.57+secangle));
        circle(x,y,rad+10);
        circle(x,y,rad+15);
        circle(x,y,2);
        line(x,y+rad+15,x+toggle*20,y+rad+100);
        circle(x+toggle*20,y+rad+100,20);
        floodfill(x+toggle*20+1,y+rad+100+1,BROWN);
        toggle*=-1;
        secangle+=step;
        if(secangle>6.28)
            secangle-=6.28;
        delay(1000);
    }
}
int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    showclock(100,100,50);
/*    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current local time and date: %s", asctime (timeinfo) );
*/
    closegraph();
}
