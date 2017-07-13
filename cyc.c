#include<stdio.h>
#include<math.h>
#include<graphics.h>

#define LEFT -1
#define RIGHT 1
#define RAD 50.0
#define C_RADB 20.0
#define C_RADS 10.0
#define XTRA 5
#define LEG 70.0
#define MAN_HT 80
#define MAN_HD_RAD 10
#define P_RAD 30.0
#define BX 100
#define BY 250
#define BODY_HT 80
#define C_SPAN 90
#define W_SPAN 190
#define FX BX+W_SPAN
#define FY BY
#define RIMS 20
#define MAX_X 650

float bx=BX,by=BY,fx=FX,fy=FY,rimAngle=6.28/RIMS;
float sx=BX+5*XTRA,sy=BY-BODY_HT,hx=FX-5*XTRA,hy=FY-BODY_HT;
float cx=BX+C_SPAN,cy=BY;

void moveCycle(float stepDis,float vel,float dist);
void pedalLeg(int side,float stepAngle);
float square(float x);

int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    moveCycle(0.25,0.25,250);
    getchar();
    closegraph();
}
void moveCycle(float stepDis,float vel,float dist){
    float secs=stepDis/vel,stepAngle=0,rimAngle=6.28/RIMS,length,theta1,theta2;
    int i;
    while(bx-BX<=dist){
        setbkcolor(BLACK);
        setcolor(GREEN);
        line(0,by+RAD+XTRA,MAX_X,by+RAD+XTRA);
        setcolor(CYAN);

        circle(cx,cy,C_RADB);
        circle(cx,cy,C_RADB-2*XTRA);

        circle(bx,by,RAD);
        circle(bx,by,RAD+XTRA);

        circle(fx,fy,RAD);
        circle(fx,fy,RAD+XTRA);

        circle(bx,by,C_RADS-XTRA);
        circle(fx,fy,C_RADS-XTRA);
        circle(bx,by,C_RADS);
        circle(fx,fy,C_RADS);

        setcolor(MAGENTA);
        line(bx,by-C_RADS,cx,cy-C_RADB);
        line(bx,by+C_RADS,cx,cy+C_RADB);

        arc(bx,by,-170,0,RAD+2*XTRA);
        arc(fx,fy,-180,-10,RAD+2*XTRA);


        line(bx,by,sx,sy);
        line(sx,sy,hx,hy);
        line(fx,fy,hx,hy);
        line(bx,by,hx,hy);
        line(cx,cy,hx,hy);
        line(bx,by,cx,cy);

        line(hx,hy,hx-XTRA,hy-4*XTRA);
        line(hx-5*XTRA,hy-4*XTRA,hx+2*XTRA,hy-4*XTRA);

        arc(cx,cy,-90,90,C_RADB);
        arc(bx,by,-270,-90,C_RADS);

        setcolor(RED);
        line(cx+P_RAD*cos(stepAngle)-XTRA,cy+P_RAD*sin(stepAngle),cx+P_RAD*cos(stepAngle)+XTRA,cy+P_RAD*sin(stepAngle));
        line(cx-P_RAD*cos(stepAngle)-XTRA,cy-P_RAD*sin(stepAngle),cx-P_RAD*cos(stepAngle)+XTRA,cy-P_RAD*sin(stepAngle));

        setcolor(GREEN);
        line(cx,cy,cx+P_RAD*cos(stepAngle),cy+P_RAD*sin(stepAngle));
        line(cx,cy,cx-P_RAD*cos(stepAngle),cy-P_RAD*sin(stepAngle));
        setcolor(BLUE);

        circle(sx+4*XTRA,sy-2*XTRA-MAN_HT,MAN_HD_RAD);
        floodfill(sx+4*XTRA,sy-2*XTRA-MAN_HT,BLUE);

        line(sx-XTRA,sy-2*XTRA,sx+4*XTRA,sy-2*XTRA-MAN_HT);
        line((sx-XTRA+sx+4*XTRA)/2,(sy-2*XTRA+sy-2*XTRA-MAN_HT)/2,hx-5*XTRA,hy-4*XTRA);
        line((sx-XTRA+sx+4*XTRA)/2,(sy-2*XTRA+sy-2*XTRA-MAN_HT)/2,hx+2*XTRA,hy-4*XTRA);

        line(sx,sy,sx-XTRA,sy-2*XTRA);
        pedalLeg(LEFT,stepAngle);
        pedalLeg(RIGHT,stepAngle);

        setcolor(RED);
        for(i=0;i<RIMS;++i){
            line(bx,by,bx+RAD*cos(i*rimAngle+stepAngle),by+RAD*sin(i*rimAngle+stepAngle));
            line(fx,fy,fx+RAD*cos(i*rimAngle+stepAngle),fy+RAD*sin(i*rimAngle+stepAngle));
        }
        bx+=stepDis;
        fx+=stepDis;
        sx+=stepDis;
        hx+=stepDis;
        cx+=stepDis;
        stepAngle+=stepDis/RAD;
        delay(secs);
    }
}
float square(float x){
    return x*x;
}
void pedalLeg(int side,float stepAngle){
        float length,theta1,theta2;
        length=sqrt(square(sx-(cx+side*P_RAD*cos(stepAngle)))+square(sy-(cy+side*P_RAD*sin(stepAngle))));
        theta1=acos((length/2.0)/LEG);
        theta2=asin((cx+side*P_RAD*cos(stepAngle)-sx)/length);
        line(sx,sy,sx+LEG*sin(theta1+theta2),sy+LEG*cos(theta1+theta2));
        line(sx+LEG*sin(theta1+theta2),sy+LEG*cos(theta1+theta2),cx+side*P_RAD*cos(stepAngle),cy+side*P_RAD*sin(stepAngle));

}
