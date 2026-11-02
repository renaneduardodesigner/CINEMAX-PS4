#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <string>
#include "graphics.h"
#include "log.h"

Scene2D::Scene2D(int w,int h,int pixelDepth) {
    width=w; height=h; depth=pixelDepth;
    frameBufferSize=width*height*depth;
    video=0; videoMem=NULL; videoMemSP=0; directMemOff=0;
    directMemAllocationSize=0; frameBuffers=NULL; frameBufferCount=0;
    activeFrameBufferIdx=0;
}
bool Scene2D::Init(size_t memSize,int numFrameBuffers) {
    video=sceVideoOutOpen(ORBIS_VIDEO_USER_MAIN,ORBIS_VIDEO_OUT_BUS_MAIN,0,0);
    videoMem=NULL;
    if(video<0) { DEBUGLOG << "Failed to open video output: " << std::string(strerror(errno)); return false; }
    if(!initFlipQueue()) return false;
    if(!allocateVideoMem(memSize,0x200000)) return false;
    if(!allocateFrameBuffers(numFrameBuffers)) return false;
    sceVideoOutSetFlipRate(video,0);
    return true;
}
bool Scene2D::initFlipQueue() {
    if(sceKernelCreateEqueue(&flipQueue,"CINEMAX flip queue")<0) return false;
    sceVideoOutAddFlipEvent(flipQueue,video,0);
    return true;
}
bool Scene2D::allocateFrameBuffers(int num) {
    if(num<=0 || (size_t)frameBufferSize*(size_t)num>directMemAllocationSize) return false;
    frameBufferCount=num;
    frameBuffers=new char*[num];
    for(int i=0;i<num;i++) frameBuffers[i]=allocateDisplayMem(frameBufferSize);
    sceVideoOutSetBufferAttribute(&attr,0x80000000,1,0,width,height,width);
    return sceVideoOutRegisterBuffers(video,0,(void**)frameBuffers,num,&attr)==0;
}
char *Scene2D::allocateDisplayMem(size_t size) {
    char *p=(char*)videoMemSP; videoMemSP+=size; return p;
}
bool Scene2D::allocateVideoMem(size_t size,int alignment) {
    directMemAllocationSize=(size+alignment-1)/alignment*alignment;
    int rc=sceKernelAllocateDirectMemory(0,sceKernelGetDirectMemorySize(),directMemAllocationSize,alignment,3,&directMemOff);
    if(rc<0) { directMemAllocationSize=0; return false; }
    rc=sceKernelMapDirectMemory(&videoMem,directMemAllocationSize,0x33,0,directMemOff,alignment);
    if(rc<0) {
        sceKernelReleaseDirectMemory(directMemOff,directMemAllocationSize);
        directMemOff=0; directMemAllocationSize=0; return false;
    }
    videoMemSP=(uintptr_t)videoMem;
    return true;
}
void Scene2D::deallocateVideoMem() {
    if(directMemAllocationSize) sceKernelReleaseDirectMemory(directMemOff,directMemAllocationSize);
    videoMem=0; videoMemSP=0; directMemOff=0; directMemAllocationSize=0;
    delete[] frameBuffers; frameBuffers=0;
}
Scene2D::~Scene2D() { deallocateVideoMem(); }
void Scene2D::SetActiveFrameBuffer(int index) {
    if(index>=0 && index<frameBufferCount) activeFrameBufferIdx=index;
}
void Scene2D::SubmitFlip(int frameID) {
    sceVideoOutSubmitFlip(video,activeFrameBufferIdx,ORBIS_VIDEO_OUT_FLIP_VSYNC,frameID);
}
void Scene2D::FrameWait(int frameID) {
    OrbisKernelEvent evt; int count=0;
    if(video==0) return;
    for(;;) {
        OrbisVideoOutFlipStatus status;
        sceVideoOutGetFlipStatus(video,&status);
        if(status.flipArg==frameID) break;
        if(sceKernelWaitEqueue(flipQueue,&evt,1,&count,0)!=0) break;
    }
}
void Scene2D::FrameBufferSwap() { activeFrameBufferIdx=(activeFrameBufferIdx+1)%frameBufferCount; }
void Scene2D::FrameBufferClear() { FrameBufferFill({0,0,0}); }
void Scene2D::FrameBufferFill(Color color) { DrawRectangle(0,0,width,height,color); }
void Scene2D::DrawPixel(int x,int y,Color color) {
    if(x<0||y<0||x>=width||y>=height||!frameBuffers) return;
    int pixel=y*width+x;
    uint32_t encoded=0x80000000u+(uint32_t(color.r)<<16)+(uint32_t(color.g)<<8)+color.b;
    ((uint32_t*)frameBuffers[activeFrameBufferIdx])[pixel]=encoded;
}
void Scene2D::DrawRectangle(int x,int y,int w,int h,Color color) {
    int x0=x<0?0:x, y0=y<0?0:y, x1=(x+w)>width?width:(x+w), y1=(y+h)>height?height:(y+h);
    for(int yy=y0;yy<y1;yy++) {
        uint32_t *row=(uint32_t*)frameBuffers[activeFrameBufferIdx]+yy*width;
        uint32_t encoded=0x80000000u+(uint32_t(color.r)<<16)+(uint32_t(color.g)<<8)+color.b;
        for(int xx=x0;xx<x1;xx++) row[xx]=encoded;
    }
}
