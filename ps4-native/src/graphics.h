#include <stdint.h>
#include <orbis/libkernel.h>
#include <orbis/VideoOut.h>
#include <orbis/Sysmodule.h>
#ifndef GRAPHICS_H
#define GRAPHICS_H
struct Color { uint8_t r,g,b; };
class Scene2D {
    int width,height,depth,video;
    off_t directMemOff;
    size_t directMemAllocationSize;
    uintptr_t videoMemSP;
    void *videoMem;
    char **frameBuffers;
    OrbisKernelEqueue flipQueue;
    OrbisVideoOutBufferAttribute attr;
    int frameBufferSize,frameBufferCount,activeFrameBufferIdx;
    bool initFlipQueue();
    bool allocateFrameBuffers(int num);
    char *allocateDisplayMem(size_t size);
    bool allocateVideoMem(size_t size,int alignment);
    void deallocateVideoMem();
public:
    Scene2D(int w,int h,int pixelDepth);
    ~Scene2D();
    bool Init(size_t memSize,int numFrameBuffers);
    void SetActiveFrameBuffer(int index);
    void SubmitFlip(int frameID);
    void FrameWait(int frameID);
    void FrameBufferSwap();
    void FrameBufferClear();
    void FrameBufferFill(Color color);
    void DrawPixel(int x,int y,Color color);
    void DrawRectangle(int x,int y,int w,int h,Color color);
};
#endif
