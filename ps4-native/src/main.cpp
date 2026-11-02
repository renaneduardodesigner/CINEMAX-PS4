#include <sstream>
#include <stdint.h>
#include <string.h>
#include <orbis/libkernel.h>
#include <orbis/Pad.h>
#include <orbis/UserService.h>
#include "graphics.h"
#include "log.h"

#define WIDTH 1280
#define HEIGHT 720
#define DEPTH 4

std::stringstream debugLogStream;

struct RGB { uint8_t r, g, b; };
static const RGB BG={10,12,22}, PANEL={20,24,40}, PANEL2={27,33,54};
static const RGB WHITE={245,247,255}, MUTED={150,160,184};
static const RGB ACCENT={124,92,255}, CYAN={57,210,220}, GOLD={255,190,92};

class Pad {
    int handle;
    int user;
    OrbisPadData data;
    uint32_t now, before;
public:
    Pad():handle(-1),user(-1),now(0),before(0) { memset(&data,0,sizeof(data)); }
    bool Init() {
        if (scePadInit()!=0) return false;
        OrbisUserServiceInitializeParams p;
        memset(&p,0,sizeof(p));
        p.priority=ORBIS_KERNEL_PRIO_FIFO_LOWEST;
        sceUserServiceInitialize(&p);
        if (sceUserServiceGetInitialUser(&user)!=0) return false;
        handle=scePadOpen(user,0,0,NULL);
        return handle>=0;
    }
    void Poll() {
        if(handle<0) return;
        before=now;
        if(scePadReadState(handle,&data)==0) now=data.buttons;
    }
    bool Hit(uint32_t mask) const { return (now&mask)!=0 && (before&mask)==0; }
};

typedef int32_t (*LaunchBrowserFn)(const char*, void*);
static bool openCatalog() {
    int32_t module=(int32_t)sceKernelLoadStartModule("libSceSystemService.sprx",0,NULL,0,NULL,NULL);
    if(module<0) return false;
    void *address=NULL;
    if(sceKernelDlsym(module,"sceSystemServiceLaunchWebBrowser",&address)!=0 || !address) return false;
    LaunchBrowserFn launch=(LaunchBrowserFn)address;
    return launch("https://renaneduardodesigner.github.io/CINEMAX-PS4/",NULL)>=0;
}

static uint8_t glyph(char c,int row) {
    static const uint8_t blank[7]={0,0,0,0,0,0,0};
    static const uint8_t letters[26][7]={
      {14,17,17,31,17,17,17},{30,17,17,30,17,17,30},{14,17,16,16,16,17,14},
      {30,17,17,17,17,17,30},{31,16,16,30,16,16,31},{31,16,16,30,16,16,16},
      {14,17,16,23,17,17,15},{17,17,17,31,17,17,17},{14,4,4,4,4,4,14},
      {7,2,2,2,18,18,12},{17,18,20,24,20,18,17},{16,16,16,16,16,16,31},
      {17,27,21,21,17,17,17},{17,25,21,19,17,17,17},{14,17,17,17,17,17,14},
      {30,17,17,30,16,16,16},{14,17,17,17,21,18,13},{30,17,17,30,20,18,17},
      {15,16,16,14,1,1,30},{31,4,4,4,4,4,4},{17,17,17,17,17,17,14},
      {17,17,17,17,17,10,4},{17,17,17,21,21,21,10},{17,17,10,4,10,17,17},
      {17,17,10,4,4,4,4},{31,1,2,4,8,16,31}
    };
    static const uint8_t digits[10][7]={
      {14,17,19,21,25,17,14},{4,12,4,4,4,4,14},{14,17,1,2,4,8,31},
      {30,1,1,14,1,1,30},{2,6,10,18,31,2,2},{31,16,16,30,1,1,30},
      {14,16,16,30,17,17,14},{31,1,2,4,8,8,8},{14,17,17,14,17,17,14},
      {14,17,17,15,1,1,14}
    };
    if(c>='A'&&c<='Z') return letters[c-'A'][row];
    if(c>='0'&&c<='9') return digits[c-'0'][row];
    switch(c) {
      case ' ': return blank[row];
      case '.': { const uint8_t a[7]={0,0,0,0,0,12,12}; return a[row]; }
      case ':': { const uint8_t a[7]={0,12,12,0,12,12,0}; return a[row]; }
      case '-': { const uint8_t a[7]={0,0,0,31,0,0,0}; return a[row]; }
      case '/': { const uint8_t a[7]={1,2,2,4,8,8,16}; return a[row]; }
      case '!': { const uint8_t a[7]={4,4,4,4,4,0,4}; return a[row]; }
      case '?': { const uint8_t a[7]={14,17,1,2,4,0,4}; return a[row]; }
      case '+': { const uint8_t a[7]={0,4,4,31,4,4,0}; return a[row]; }
      default: return blank[row];
    }
}

static void text(Scene2D* s,int x,int y,const char* value,int scale,RGB color) {
    for(int i=0; value[i]; ++i) {
        char c=value[i];
        for(int ry=0;ry<7;++ry) {
            uint8_t bits=glyph(c,ry);
            for(int rx=0;rx<5;++rx) if(bits&(1<<(4-rx)))
                s->DrawRectangle(x+i*6*scale+rx*scale,y+ry*scale,scale,scale,{color.r,color.g,color.b});
        }
    }
}
static void rect(Scene2D* s,int x,int y,int w,int h,RGB c) {
    s->DrawRectangle(x,y,w,h,{c.r,c.g,c.b});
}
static void card(Scene2D* s,int x,int y,int w,int h,bool active,const char* title,const char* desc) {
    rect(s,x,y,w,h,active?ACCENT:PANEL2);
    rect(s,x+4,y+4,w-8,h-8,active?RGB{37,31,78}:PANEL);
    rect(s,x+22,y+22,42,5,active?CYAN:GOLD);
    text(s,x+22,y+56,title,3,WHITE);
    text(s,x+22,y+104,desc,2,active?WHITE:MUTED);
    if(active) rect(s,x+22,y+h-18,w-44,4,CYAN);
}
static void draw(Scene2D* s,int selected,const char* status) {
    s->FrameBufferFill({BG.r,BG.g,BG.b});
    rect(s,0,0,WIDTH,8,ACCENT);
    text(s,64,48,"CINEMAX",5,WHITE);
    text(s,890,65,"PS4 HOME EDITION",2,CYAN);
    rect(s,64,126,1152,248,PANEL);
    rect(s,64,126,9,248,ACCENT);
    text(s,104,166,"SEU CINEMA",5,WHITE);
    text(s,104,226,"SUA DESCOBERTA",5,CYAN);
    text(s,106,302,"FILMES  SERIES  ANIMES  EM UMA TELA",2,MUTED);
    card(s,64,410,350,190,selected==0,"ABRIR CATALOGO","ENTRAR NO CINEMAX");
    card(s,465,410,350,190,selected==1,"DESCOBRIR","FILMES E SERIES");
    card(s,866,410,350,190,selected==2,"MINHA LISTA","FAVORITOS E HISTORICO");
    rect(s,64,632,1152,2,{48,56,82});
    text(s,64,652,"SETAS SELECIONAM   X ABRE   O VOLTA",2,MUTED);
    text(s,760,652,status,2,GOLD);
}

int main() {
    setvbuf(stdout,NULL,_IONBF,0);
    Scene2D scene(WIDTH,HEIGHT,DEPTH);
    if(!scene.Init(0xC000000,2)) {
        DEBUGLOG << "CINEMAX: falha ao inicializar video";
        for(;;) sceKernelUsleep(1000000);
    }
    Pad pad;
    if(!pad.Init()) {
        DEBUGLOG << "CINEMAX: controle nao inicializado";
    }
    int selected=0;
    int frame=0;
    const char* status="ONLINE";
    for(;;) {
        pad.Poll();
        if(pad.Hit(ORBIS_PAD_BUTTON_LEFT)) { selected=(selected+2)%3; }
        if(pad.Hit(ORBIS_PAD_BUTTON_RIGHT)) { selected=(selected+1)%3; }
        if(pad.Hit(ORBIS_PAD_BUTTON_CROSS)) {
            status=openCatalog()?"ABRINDO CATALOGO":"NAO FOI POSSIVEL ABRIR";
            if(status[0]=='A' && status[1]=='B') {
                // The system browser takes foreground when the launch request succeeds.
            }
        }
        if(pad.Hit(ORBIS_PAD_BUTTON_CIRCLE)) status="CINEMAX PS4";
        draw(&scene,selected,status);
        scene.SubmitFlip(frame);
        scene.FrameWait(frame);
        scene.FrameBufferSwap();
        ++frame;
        sceKernelUsleep(16000);
    }
    return 0;
}
