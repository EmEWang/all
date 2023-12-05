#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include<linux/fb.h>

#define pi 3.1415926

// https://blog.csdn.net/qq_44310495/article/details/110093612
typedef struct {
    int fd;
    long size;
    unsigned char*fbp;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
}fbdev;


int min(int a, int b){
    if(a<b)return a;
    else return b;
}

int max(int a, int b){
    if(a>b)return a;
    else return b;
}

//画点函数
void draw_dot(fbdev dev, int x, int y){
    int xres=dev.vinfo.xres;
    int yres=dev.vinfo.yres;
    int bpp=dev.vinfo.bits_per_pixel;
    long offset=(y*xres+x)*bpp/8;
    *(dev.fbp+offset)=255; //设置颜色，默认为白色
    *(dev.fbp+offset+1)=255;
    *(dev.fbp+offset+2)=255;
}

//画线函数
void draw_line(fbdev dev, int x1,int y1, int x2, int y2){
    int i,j;
    if(x1==x2){
        for(j=min(y1,y2);j<=max(y1,y2);j++)
            draw_dot(dev,x1,j);
        return;
    }
    if(y1==y2){
        for(i=min(x1,x2);i<=max(x1,x2);i++)
            draw_dot(dev,i,y1);
        return;
    }
    if(x1<x2){
        for(i=x1;i<x2;i++){
            if(y1<y2){
                for(j=y1+(i-x1)*(y2-y1)/(x2-x1);j<=y1+(i+1-x1)*(y2-y1)/(x2-x1);j++)
                    draw_dot(dev,i,j);
            }
            else {
                for(j=y1+(i-x1)*(y2-y1)/(x2-x1);j>=y1+(i+1-x1)*(y2-y1)/(x2-x1);j--)
                    draw_dot(dev,i,j);
            }
        }
    }
    else{
        for(i=x1;i>x2;i--){
            if(y1<y2){
                for(j=y1+(x1-i)*(y2-y1)/(x1-x2);j<=y1+(x1-1-i)*(y2-y1)/(x1-x2);j++)
                    draw_dot(dev,i,j);
            }
            else {
                for(j=y1+(x1-i)*(y2-y1)/(x1-x2);j>=y1+(x1-1-i)*(y2-y1)/(x1-x2);j--)
                    draw_dot(dev,i,j);
            }
        }
    }
}

//画圆函数
void draw_circle(fbdev dev, int x, int y, int r){
    int i,a,b;
    for(i=0;i<360;i++){
        a=x+r*cos(i/180.0*pi);
        b=y+r*sin(i/180.0*pi);
        draw_dot(dev,a,b);
    }
}




int main(){

    fbdev dev;
    dev.fd=open("/dev/fb0",O_RDWR);

    ioctl(dev.fd,FBIOGET_VSCREENINFO,&dev.vinfo);
    ioctl(dev.fd,FBIOGET_FSCREENINFO, &dev.finfo);
    dev.size=dev.vinfo.xres*dev.vinfo.yres*dev.vinfo.bits_per_pixel/8;

    dev.fbp=(unsigned char*)mmap(0,dev.size,PROT_READ|PROT_WRITE,MAP_SHARED,dev.fd,0);
    memset(dev.fbp,0,dev.size);

    draw_dot(dev,1,1);
    // draw_line(dev,120,220,230,400);
    // draw_circle(dev,100,200,100);
    munmap(dev.fbp,dev.size);
    close(dev.fd);
    return 0;
}
