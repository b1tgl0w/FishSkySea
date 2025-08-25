/*
  Copyright (c) 2019-2021 John Miner

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ifdef NOMUSIC
#define UkeSong1wavlen 1
Uint8 UkeSong1wav[UkeSong1wavlen];
#define JMwavlen 1
Uint8 JMwav[JMwavlen];
#endif /* NO_MUSIC */
int aiBurp;
int aiBurpTimer;
int aiBurpTimeout;
int aiBurpOffTimer;
int aiBurpOffTimeout;
Uint32 aidifficulty;
Uint32 aikeystate;
Uint32 aikeystateprev;
int aiXDist[5];
int aiYDist[5];
int badconn;
SDL_Texture *bgTexture;
char buf[256];
int clientNetVersion = 2;
Uint32 clientkeystate;
Uint32 clientkeystateprev;
SDL_Texture *cloudTexture;
SDL_Rect cloudSrcRect;
SDL_Rect cloudSrcRect2;
SDL_Rect cloudDstRect;
SDL_Rect cloudDstRect2;
float cloudX;
Uint32 controllerstate;
Uint32 controllerstateprev;
int curChannel = -1;
Uint32 curFrames;
Uint32 curTicks;
char data[8192];
SDL_Texture *fgTexture;
int fishBoolMap[1846];
int fishFlipBoolMap[1846];
int fishOutlineMap[1846];
int fishFlipOutlineMap[1846];
SDL_Texture *fishTexture;
SDL_Texture *fishGlowTexture;
SDL_Texture *fishFlipTexture;
SDL_Texture *fishGlowFlipTexture;
int fishFacing[5];
float fishGlowAlpha[5];
int fishGlowing[5];
int fishGlimmerX[5];
Uint32 fishInterval;
int fishNibble[5];
int fishNibbleTimeout[5];
int fishOn[5];
float fishPhase[5];
int fishSalmon[5];
float fishSpeed[5];
float fishSpurtPhase[5];
Uint32 fishTimeSinceAboutFace[5];
Uint32 fishNextAboutFaceTime[5];
float fishX[5];
float fishY[5];
float fishYBase[5];
int g;
int gpu;
int hostNetVersion = 1;
int hookSize;
SDL_Texture *hookTexture;
char ipbuf[256];
Uint32 keystate;
Uint32 keystateprev;
Uint32 lastTicks;
int mode;
Uint32 netTimeout;
int netTimer;
int noParam;
int noParam2;
SDL_Texture *offscreenBuffer[4] = { NULL, NULL, NULL, NULL };
int player1Cast;
int player1CaughtCount;
int player1FishOn;
SDL_Rect player1Glimmer1Rect;
SDL_Rect player1Glimmer2Rect;
int player1GlimmerReady;
int player1GlimmerTimeout;
int player1GlimmerXBase;
int player1GlimmerY;
int player1HookSet;
int player1HookRecoverTimeout;
float player1LineX1;
float player1LineX2;
float player1LineY1;
float player1LineY2;
float player1PoleX1;
float player1PoleX2;
float player1PoleY1;
SDL_Texture *player1PoleNoFishTexture;
SDL_Texture *player1PoleFishTexture;
int player2Cast;
int player2CaughtCount;
int player2FishOn;
SDL_Rect player2Glimmer1Rect;
SDL_Rect player2Glimmer2Rect;
int player2GlimmerReady;
int player2GlimmerTimeout;
int player2GlimmerXBase;
int player2GlimmerY;
int player2HookSet;
int player2HookRecoverTimeout;
float player2LineX1;
float player2LineX2;
float player2LineY1;
float player2LineY2;
float player2PoleX1;
float player2PoleX2;
float player2PoleY1;
SDL_Texture *player2PoleNoFishTexture;
SDL_Texture *player2PoleFishTexture;
int playingVictorySong;
int port;
SDL_Texture *pointFishTexture;
SDL_Rect radDstRect;
SDL_Rect radSrcRect;
float radGlowAlpha;
int radGlowing;
SDL_Texture *radTexture;
SDL_Texture *radGlowTexture;
SDL_Renderer *renderer;
int rippleFrame;
int rippleFrame2;
int rippleFrame3;
int rippleFrame4;
int rippleInterval;
int rippleInterval2;
int rippleInterval3;
int rippleInterval4;
int rippleTimeout;
int rippleTimeout2;
int rippleTimeout3;
int rippleTimeout4;
SDL_Texture *rippleTexture1;
SDL_Texture *rippleTexture2;
SDL_Texture *rippleTexture3;
SDL_Texture *rippleTexture4;
SDL_Texture *rippleTexture5;
SDL_Texture *rippleTexture6;
SDL_Texture *salmonTexture;
SDL_Texture *salmonFlipTexture;
SDL_Texture *seaHorseTexture;
SDL_Texture *seaHorseFlipTexture;
SDL_Texture *seaweed1BottomTexture;
SDL_Texture *seaweed1TopTexture;
int seaweedOffset[9];
int seaweedOffsetDirection[9];
int seaweedOffsetTimeout[9];
int seaweedOffsetTimer[9];
int seaHorseFacing;
int seaHorseGo;
float seaHorsePhase;
float seaHorseX;
float seaHorseY;
float seaHorseYBase;
SDL_Texture *seaStarTexture;
int seaStarGo;
float seaStarX;
float seaStarY;
SDL_Rect seaStarBox;
time_t seed;
IPaddress serverip;
int sharkBoolMap[14000];
int sharkFlipBoolMap[14000];
int sharkOutlineMap[14000];
int sharkFlipOutlineMap[14000];
SDL_Rect sharkBox;
float sharkGlowAlpha;
int sharkGlowing;
SDL_Rect sharkLeftBox;
SDL_Rect sharkRightBox;
SDL_Texture *sharkFinTexture;
SDL_Texture *sharkFinFlipTexture;
SDL_Texture *sharkFinGlowTexture;
SDL_Texture *sharkFinGlowFlipTexture;
SDL_Texture *sharkFlipTexture;
SDL_Texture *sharkGlowTexture;
SDL_Texture *sharkGlowFlipTexture;
SDL_Texture *sharkTexture;
float sharkSpeed;
float sharkX;
float sharkY;
int sharkFacing;
SDL_Rect sloogieBox;
int sloogieFacing;
int sloogieHide;
int sloogieHideTimeout;
int sloogieHideX;
int sloogieOffscreenTimeout;
float sloogieSpeed;
SDL_Texture *sloogieTexture;
SDL_Texture *sloogieGlowTexture;
SDL_Texture *sloogieFlipTexture;
SDL_Texture *sloogieGlowFlipTexture;
SDL_Texture *sloogieHideTexture;
SDL_Texture *sloogieHideGlowTexture;
SDL_Texture *sloogieHideFlipTexture;
SDL_Texture *sloogieHideGlowFlipTexture;
float sloogieGlowAlpha;
int sloogieGlowing;
float sloogieX;
TCPsocket sock;
TCPsocket sock2;
SDLNet_SocketSet set;
Mix_Chunk *song1;
SDL_RWops *song1rwops;
Mix_Chunk *song4;
SDL_RWops *song4rwops;
Mix_Chunk *sound_cast;
SDL_RWops *sound_castrwops;
Mix_Chunk *sound_fishcatch;
SDL_RWops *sound_fishcatchrwops;
Mix_Chunk *sound_glimmer;
SDL_RWops *sound_glimmerrwops;
Mix_Chunk *sound_sharkbite;
SDL_RWops *sound_sharkbiterwops;
Uint32 renderTimeout;
int renderTimer;
SDL_Window *screen;
unsigned long totalFrames;
unsigned long totalMs;
float volume;
float wavenumber = 0.01570795;
SDL_Rect wesDstRect;
SDL_Rect wesSrcRect;
float wesGlowAlpha;
int wesGlowing;
SDL_Texture *wesTexture;
SDL_Texture *wesGlowTexture;
int winScore;
int winTimeout;
void atExitQuit(void);
void backupConfig(void);
float calculateLinearPositionValue(float lowPoint, float highPoint,
    float lowValue, float highValue, float inputPoint);
void convertXpmToBoolMap(char *xpm[], int boolmap[], int xpmWidth, int boolMapWidth, int firstRowIndex);
void convertBoolmapToOutlinemap(int boolmap[], int outlinemap[], int boolmapwidth, int outlinemapwidth);
float fishYDisplacement(float x, float phase);
float fishRandomizePhase(float phase);
int isCollision(SDL_Rect *a, SDL_Rect *b, int boolmap1[], int boolmap2[]);
int isCollisionPp(int outlinemap1[], int outlinemap2[], int minorwidth1, int minorwidth2, int majorwidth1, int majorwidth2, SDL_Rect *a, SDL_Rect *b);
void keyboard(void);
void load(void);
void load2(void);
SDL_Texture *loadTextureFromXpm(SDL_Renderer *r, char **xpm);
SDL_Texture *loadTextureFromLargeXpm(SDL_Renderer *r, char xpm[], char *arg[], const int width, const int height);
void metrics(Uint32 interval);
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
size_t mystrnlen(char *s, size_t maxlen);
void proc(Uint32 interval);
void procai(Uint32 interval);
void procnet(void);
void procseaweed(int i);
void render(void);
void renderBoolmap(int boolmap[], int xpmWidth, int boolmapwidth, int x, int y);
void update(Uint32 interval);
int wrapNumber(int n, int low, int high);
void atExitQuit(void) {
  int i = 0;
  volatile int volat = 0;
  /* TODO other stuff */
#ifdef DEBUG_MODE
  fprintf(stdout, "Total Frames = %ld\n", totalFrames);
  fprintf(stdout, "Total MS = %ld\n", totalMs);
  if (totalMs / 1000 > 0)
    fprintf(stdout, "Total Frames / (Total MS / 1000) = %ld\n", totalFrames / (totalMs / 1000));
  else
    fprintf(stdout, "(Total MS / 1000) = 0 \n");
#endif
  for (i = 0; i < 4; ++i) {
    if (volat == 0)
      volat = 1;
    if (offscreenBuffer[i] != NULL)
      SDL_DestroyTexture(offscreenBuffer[i]);
  }
  if (bgTexture != NULL)
    SDL_DestroyTexture(bgTexture);
  if (cloudTexture != NULL)
    SDL_DestroyTexture(cloudTexture);
  if (fgTexture != NULL)
    SDL_DestroyTexture(fgTexture);
  if (radTexture != NULL)
    SDL_DestroyTexture(radTexture);
  if (radGlowTexture != NULL)
    SDL_DestroyTexture(radGlowTexture);
  if (rippleTexture1 != NULL)
    SDL_DestroyTexture(rippleTexture1);
  if (rippleTexture2 != NULL)
    SDL_DestroyTexture(rippleTexture2);
  if (rippleTexture3 != NULL)
    SDL_DestroyTexture(rippleTexture3);
  if (rippleTexture4 != NULL)
    SDL_DestroyTexture(rippleTexture4);
  if (rippleTexture5 != NULL)
    SDL_DestroyTexture(rippleTexture5);
  if (rippleTexture6 != NULL)
    SDL_DestroyTexture(rippleTexture6);
  if (seaHorseTexture != NULL)
    SDL_DestroyTexture(seaHorseTexture);
  if (seaHorseFlipTexture != NULL)
    SDL_DestroyTexture(seaHorseFlipTexture);
  if (seaweed1BottomTexture != NULL)
    SDL_DestroyTexture(seaweed1BottomTexture);
  if (seaweed1TopTexture != NULL)
    SDL_DestroyTexture(seaweed1TopTexture);
  if (seaStarTexture != NULL)
    SDL_DestroyTexture(seaStarTexture);
  if (sharkGlowTexture != NULL)
    SDL_DestroyTexture(sharkGlowTexture);
  if (sharkFinGlowTexture != NULL)
    SDL_DestroyTexture(sharkFinGlowTexture);
  if (sharkFinGlowFlipTexture != NULL)
    SDL_DestroyTexture(sharkFinGlowFlipTexture);
  if (sharkGlowFlipTexture != NULL)
    SDL_DestroyTexture(sharkGlowFlipTexture);
  if (sharkTexture != NULL)
    SDL_DestroyTexture(sharkTexture);
  if (sharkFinTexture != NULL)
    SDL_DestroyTexture(sharkFinTexture);
  if (sharkFinFlipTexture != NULL)
    SDL_DestroyTexture(sharkFinFlipTexture);
  if (sharkFlipTexture != NULL)
    SDL_DestroyTexture(sharkTexture);
  if (sloogieTexture != NULL)
    SDL_DestroyTexture(sloogieTexture);
  if (sloogieFlipTexture != NULL)
    SDL_DestroyTexture(sloogieFlipTexture);
  if (sloogieGlowFlipTexture != NULL)
    SDL_DestroyTexture(sloogieGlowFlipTexture);
  if (sloogieGlowTexture != NULL)
    SDL_DestroyTexture(sloogieGlowTexture);
  if (sloogieHideTexture != NULL)
    SDL_DestroyTexture(sloogieHideTexture);
  if (sloogieHideFlipTexture != NULL)
    SDL_DestroyTexture(sloogieFlipTexture);
  if (sloogieHideGlowFlipTexture != NULL)
    SDL_DestroyTexture(sloogieHideGlowFlipTexture);
  if (sloogieHideGlowTexture != NULL)
    SDL_DestroyTexture(sloogieHideGlowTexture);
  if (wesTexture != NULL)
    SDL_DestroyTexture(wesTexture);
  if (wesGlowTexture != NULL)
    SDL_DestroyTexture(wesGlowTexture);
  if (fishTexture != NULL)
    SDL_DestroyTexture(fishTexture);
  if (fishFlipTexture != NULL)
    SDL_DestroyTexture(fishFlipTexture);
  if (fishGlowTexture != NULL)
    SDL_DestroyTexture(fishGlowTexture);
  if (fishGlowFlipTexture != NULL)
    SDL_DestroyTexture(fishGlowFlipTexture);
  if (hookTexture != NULL)
    SDL_DestroyTexture(hookTexture);
  if (player1PoleFishTexture != NULL)
    SDL_DestroyTexture(player1PoleFishTexture);
  if (player1PoleNoFishTexture != NULL)
    SDL_DestroyTexture(player1PoleNoFishTexture);
  if (player2PoleFishTexture != NULL)
    SDL_DestroyTexture(player2PoleFishTexture);
  if (player2PoleNoFishTexture != NULL)
    SDL_DestroyTexture(player2PoleNoFishTexture);
  if (pointFishTexture != NULL)
    SDL_DestroyTexture(pointFishTexture);
  if (salmonTexture != NULL)
    SDL_DestroyTexture(salmonTexture);
  if (salmonFlipTexture != NULL)
    SDL_DestroyTexture(salmonFlipTexture);
  IMG_Quit();
#ifndef NOMUSIC
  if (song1 != NULL)
    Mix_FreeChunk(song1);
  if (song4 != NULL)
    Mix_FreeChunk(song4);
  if (sound_cast != NULL)
    Mix_FreeChunk(sound_cast);
  if (sound_fishcatch != NULL)
    Mix_FreeChunk(sound_fishcatch);
  if (sound_glimmer != NULL)
    Mix_FreeChunk(sound_glimmer);
  if (sound_sharkbite != NULL)
    Mix_FreeChunk(sound_sharkbite);
  Mix_CloseAudio();
  Mix_Quit();
#endif /* NOMUSIC */
  if (set != NULL)
    SDLNet_FreeSocketSet(set);
  if (mode == 2 && sock2 != NULL)
    SDLNet_TCP_Close(sock2);
  if ((mode == 2 || mode == 3) && sock != NULL)
    SDLNet_TCP_Close(sock);
  SDLNet_Quit();
  if (renderer != NULL)
    SDL_DestroyRenderer(renderer);
  if (screen != NULL)
    SDL_DestroyWindow(screen);
  SDL_Quit();
}
void backupConfig(void) {
  int fd = open("./backup-config-fss.txt", O_CREAT | O_EXCL | O_RDWR, 00200 | 00400);
  int i = 0;
  size_t len = 0;
  ssize_t writ = 0;
  ssize_t totalwrit = 0;
  volatile int volat = 0;
  if (fd < 0)
    return;
  for (i = 0; i < backup_config_txt_len; ++i) {
    volatile int volatwhil = 0;
    volatile int volatwhil2 = 0;
    if (volat == 0)
      volat = 1;
    len = mystrnlen(backupcfgtxt[i], 256);
    totalwrit = 0;
    while (totalwrit < (ssize_t) len) {
      if (volatwhil == 0)
        volatwhil = 1;
      writ = write(fd, backupcfgtxt[i], len);
      if (writ < 0) {
        close(fd);
        return;
      }
      totalwrit += writ;
    }
    totalwrit = 0;
    while (totalwrit < 1) {
      if (volatwhil2 == 0)
        volatwhil2 = 1;
      writ = write(fd, "\n", 1);
      if (writ < 0) {
        close(fd);
        return;
      }
      totalwrit += 1;
    }
  }
  close(fd);
}
float calculateLinearPositionValue(float lowPoint, float highPoint,
    float lowValue, float highValue, float inputPoint)
{
    float ret = 0.0f;
    float a = 0.0f;
    float b = 0.0f;
    float inputHighDistance = highPoint > inputPoint ? highPoint - inputPoint :
        inputPoint - highPoint;
    float inputLowDistance = lowPoint > inputPoint ? lowPoint - inputPoint :
        inputPoint - lowPoint;
    float highLowDistance = highPoint > lowPoint ? highPoint - lowPoint :
        lowPoint - highPoint;
    if( inputHighDistance > -0.3 && inputHighDistance < 0.3 )
        return highValue;
    if( inputLowDistance > -0.3 && inputLowDistance < 0.3 )
        return lowValue;
    a = highLowDistance / inputHighDistance; 
    b = highLowDistance / inputLowDistance; 
    if ( a < 1.1 && a > -.1 ) a = 1.1;
    if ( a > -1.1 && a < 0.1 ) a = -1.1;
    if ( b < 1.1 && b > -.1 ) b = 1.1;
    if ( b > -1.1 && b < 0.1 ) b = -1.1;
    ret = lowValue / a + highValue / b;
    return ret;
}
/* xpm must be same size as boolmap */
void convertXpmToBoolMap(char *xpm[], int boolmap[], int xpmWidth, int boolMapWidth, int firstRowIndex) {
  int i = 0;
  volatile int volat = 0;
  for (i = 0; i < boolMapWidth; ++i) {
    if (volat == 0)
      volat = 1;
    if (xpm[firstRowIndex + i / xpmWidth][i % xpmWidth] != ' ')
      boolmap[i] = 1;
    else
      boolmap[i] = 0;
  }
}
/* Precondition: boolmap has no holes */
void convertBoolmapToOutlinemap(int boolmap[], int outlinemap[], int minorwidth, int majorwidth) {
  int i = 0;
  volatile int volat = 0;
  for (i = 0; i < majorwidth; ++i) {
    if (volat == 0)
      volat = 1;
    if (boolmap[i] == 0) {
      outlinemap[i] = 0;
      continue;
    }

    if (i == 0 || i % minorwidth == 0 || boolmap[i - 1] == 0)
      outlinemap[i] = 1;
    else if(i == majorwidth - 1 || i % minorwidth == minorwidth - 1 || boolmap[i + 1] == 0)
      outlinemap[i] = 1;
    else if(i < minorwidth || boolmap[i - minorwidth] == 0)
      outlinemap[i] = 1;
    else if(i > -1 + majorwidth - minorwidth || boolmap[i + minorwidth] == 0)
      outlinemap[i] = 1;
    else
      outlinemap[i] = 0;
  }
}
float fishYDisplacement(float x, float phase) {
  return 5.0 * sin(-(wavenumber * x) + phase);
}
float fishRandomizePhase(float phase) {
  return wrapNumber(phase, 0.0, 2.0 * 3.14159);
}
int isCollision(SDL_Rect *a, SDL_Rect *b, int outlinemap1[], int outlinemap2[]) {
  int coll = 0;
  if (a->x >= b->x && a->x <= b->x + b->w
      && a->y >= b->y && a->y <= b->y + b->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (a->x >= b->x && a->x <= b->x + b->w
      && a->y + a->h >= b->y && a->y + a->h <= b->y + b->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (a->x + a->w >= b->x && a->x + a->w <= b->x + b->w
      && a->y >= b->y && a->y <= b->y + b->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (a->x + a->w >= b->x && a->x + a->w <= b->x + b->w
      && a->y + a->h >= b->y && a->y + a->h <= b->y + b->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (b->x >= a->x && b->x <= a->x + a->w
      && b->y >= a->y && b->y <= a->y + a->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (b->x >= a->x && b->x <= a->x + a->w
      && b->y + b->h >= a->y && b->y + b->h <= a->y + a->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (b->x + b->w >= a->x && b->x + b->w <= a->x + a->w
      && b->y >= a->y && b->y <= a->y + a->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  if (b->x + b->w >= a->x && b->x + b->w <= a->x + a->w
      && b->y + b->h >= a->y && b->y + b->h <= a->y + a->h) {
    if (outlinemap1 == NULL || outlinemap2 == NULL)
      return 1;
    coll |= isCollisionPp(outlinemap1, outlinemap2, a->w, b->w, a->w * a->h, b->w * b->h, a, b)
      | isCollisionPp(outlinemap2, outlinemap1, b->w, a->w, b->w * b->h, a->w * a->h, b, a);
  }
  return coll;
}
/* call twice: once with outlinemap1 first then with outlinemap2 first and adjust other params */
int isCollisionPp(int outlinemap1[], int outlinemap2[], int minorwidth1, int minorwidth2, int majorwidth1, int majorwidth2,
  SDL_Rect *a, SDL_Rect *b) {
  int h = 0;
  int i = 0;
  int j = 0;
  int originX = 0;
  int originY = 0;
  volatile int volat = 0;
  for (i = 0; i < majorwidth1; ++i) {
    volatile int volat2 = 0;
    if (volat == 0)
      volat = 1;
    if (outlinemap1[i] == 0)
      continue;
    h = 0;
    originX = i % minorwidth1 + (int) a->x - (int) b->x;
    originY = i / minorwidth1 + (int) a->y - (int) b->y;
    if (originX < 0 || originX >= minorwidth2)
      continue;
    if (originY < 0 || originY >= b->h)
      continue;
    for (j = originX + originY * minorwidth2; j >= 0 && j < majorwidth2 && (j % minorwidth2) != (minorwidth2 - 1); --j) {
      if (volat2 == 0)
        volat2 = 1;
      if (outlinemap2[j] == 1)
        h = 1;
    }
    if (h == 1) {
      volatile int volat3 = 0;
      for (j = originX + originY * minorwidth2; j >= 0 && j < majorwidth2 && (j % minorwidth2) != 0; ++j) {
        if (volat3 == 0)
          volat3 = 1;
        if (outlinemap2[j] == 1)
          h = 2;
      }
    }
    if (h == 2) {
      volatile int volat4 = 0;
      for (j = originX + originY * minorwidth2; j >= 0 && j < majorwidth2; j -= minorwidth2) {
        if (volat4 == 0)
          volat4 = 1;
        if (outlinemap2[j] == 1)
          h = 3;
      }
    }
    if (h == 3) {
      volatile int volat5 = 0;
      for (j = originX + originY * minorwidth2; j >= 0 && j < majorwidth2; j += minorwidth2) {
        if (volat5 == 0)
          volat5 = 1;
        if (outlinemap2[j] == 1) {
#ifdef DEBUG_MODE
          g = 255;
          SDL_Delay(2000);
#endif /* DEBUG_MODE */
          return 1;
        }
      }
    }
  }
  return 0;
}
void keyboard(void) {
  const Uint8 *state = NULL;
  SDL_Event e;
  SDL_PumpEvents();
  SDL_PollEvent(&e);
  if (e.type == SDL_QUIT)
    exit(0);
  state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_ESCAPE])
    exit(0);
  if(((mode != 4 && mode != 3) && state[SDL_SCANCODE_LEFT]) || state[SDL_SCANCODE_A])
    keystate |= 0x1;
  else
    keystate &= ~((Uint32)0x1);
  if(((mode != 4 && mode != 3) && state[SDL_SCANCODE_RIGHT]) || state[SDL_SCANCODE_D])
    keystate |= 0x2;
  else
    keystate &= ~((Uint32)0x2);
  if(((mode != 4 && mode != 3) && state[SDL_SCANCODE_UP]) || state[SDL_SCANCODE_W])
    keystate |= 0x4;
  else
    keystate &= ~((Uint32)0x4);
  if(((mode != 4 && mode != 3) && state[SDL_SCANCODE_DOWN]) || state[SDL_SCANCODE_S])
    keystate |= 0x8;
  else
    keystate &= ~((Uint32)0x8);
  if(((mode != 4 && mode != 3) && state[SDL_SCANCODE_SPACE]) || state[SDL_SCANCODE_E])
    keystate |= 0x10;
  else
    keystate &= ~((Uint32)0x10);
  if(((mode != 4 && mode != 3) && state[SDL_SCANCODE_LCTRL]) || state[SDL_SCANCODE_Q])
    keystate |= 0x20;
  else
    keystate &= ~((Uint32)0x20);
  if((mode == 4 && state[SDL_SCANCODE_J]) || (mode == 3 && (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])))
    keystate |= 0x100;
  else
    keystate &= ~((Uint32)0x100);
  if((mode == 4 && state[SDL_SCANCODE_L]) || (mode == 3 && (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])))
    keystate |= 0x200;
  else
    keystate &= ~((Uint32)0x200);
  if((mode == 4 && state[SDL_SCANCODE_I]) ||(mode == 3 && (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])))
    keystate |= 0x400;
  else
    keystate &= ~((Uint32)0x400);
  if((mode == 4 && state[SDL_SCANCODE_K]) || (mode == 3 && (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])))
    keystate |= 0x800;
  else
    keystate &= ~((Uint32)0x800);
  if((mode == 4 && state[SDL_SCANCODE_U]) || (mode == 3 && (state[SDL_SCANCODE_E] || state[SDL_SCANCODE_SPACE])))
    keystate |= 0x1000;
  else
    keystate &= ~((Uint32)0x1000);
  if((mode == 4 && state[SDL_SCANCODE_O]) || (mode == 3 && (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_LCTRL])))
    keystate |= 0x2000;
  else
    keystate &= ~((Uint32)0x2000);
  if(state[SDL_SCANCODE_LSHIFT])
    keystate |= 0x4000;
  else
    keystate &= ~((Uint32)0x4000);
}
void load(void) {
  SDL_Rect bgfgDstRect = { 0, 0, 0, 0 };
  FILE *f;
  char cwd[256];
  int cwdlen = 0;
  int tmpHookSize = 24;
  int tmpWinScore = 17;
  int windowed = 1;
  int tmp = 0;
  int i = 0;
  volatile int volat = 0;
  badconn = 0;
  volume = 0.5f;
  mode = 1;
  port = 2020;
  getcwd(cwd, 256);
  cwdlen = mystrnlen(cwd, 256);
  if (cwd != NULL && 256 - cwdlen > 0) {
    strncat(buf, cwd, 255);
    strncat(buf, "/config.txt", 255);
    f = fopen(buf, "r");
    if (f == NULL)
      f = fopen("./config.txt", "r");
    if (f != NULL) {
      int ret = 0;
      volatile int volatwhil = 0;
      do {
        if (volatwhil == 0)
          volatwhil = 1;
        ret = fscanf(f, "%255s", buf);
        if (ret == EOF) break;
        if (buf[0] == '#') {
          char c;
          volatile int volatwhil2 = 0;
          do {
            if (volatwhil2 == 0)
              volatwhil2 = 1;
            if (feof(f))
              goto endcfg;
            c = fgetc(f);
          } while (c != '\n');
        }
        if (strncmp(buf, "hook", 256) == 0) {
          ret = fscanf(f, "%255s", buf);
          errno = 0;
          tmp = strtol(buf, NULL, 10);
          if (errno != 0) continue;
          if (tmpHookSize < 5 || tmpHookSize > 24) continue;
          tmpHookSize = tmp;
        }
        if (strncmp(buf, "score", 256) == 0) {
          ret = fscanf(f, "%255s", buf);
          errno = 0;
          tmp = strtol(buf, NULL, 10);
          if (errno != 0) continue;
          if (tmpWinScore < 5 || tmpWinScore > 48) continue;
          tmpWinScore = tmp;
        }
        if (strncmp(buf, "window", 256) == 0) {
          ret = fscanf(f, "%255s", buf);
          errno = 0;
          tmp = strtol(buf, NULL, 10);
          if (errno != 0) continue;
          windowed = tmp;
        }
        if (strncmp(buf, "volume", 256) == 0) {
          ret = fscanf(f, "%255s", buf);
          errno = 0;
          tmp = strtol(buf, NULL, 10);
          if (errno != 0) continue;
          volume = ((float) tmp) / 100.0f;
          if (volume < 0.0f)
            volume = 0.0f;
          if (volume > 1.0f)
            volume = 1.0f;
        }
        if (strncmp(buf, "gpu", 256) == 0) {
          ret = fscanf(f, "%255s", buf);
          errno = 0;
          if (errno != 0) continue;
          if (strncmp(buf, "1", 2) == 0)
            gpu = 1;
          else
            gpu = 0;
        }
        if (strncmp(buf, "mode", 256) == 0) {
          ret = fscanf(f, "%255s", ipbuf);
          errno = 0;
          if (errno != 0) continue;
          if (strncmp(ipbuf, "solitaire", 9) == 0)
            mode = 0;
          else if (strncmp(ipbuf, "ai", 2) == 0) {
            mode = 1;
            aidifficulty = 0;
          }
          else if (strncmp(ipbuf, "ai-easy", 2) == 0) {
            mode = 1;
            aidifficulty = 0;
          }
          else if (strncmp(ipbuf, "ai-normal", 2) == 0) {
            mode = 1;
            aidifficulty = 1;
          }
          else if (strncmp(ipbuf, "ai-hard", 2) == 0) {
            mode = 1;
            aidifficulty = 2;
          }
          else if (strncmp(ipbuf, "host", 4) == 0)
            mode = 2;
          else if (strncmp(ipbuf, "keyboard", 8) == 0)
            mode = 4;
          else
            mode = 3;
        }
      } while (ret != EOF);
endcfg:
      fclose(f);
    }
  }
  if (windowed != 1) {
    screen = SDL_CreateWindow("Fish Sky Sea", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
  }
  else {
    screen = SDL_CreateWindow("Fish Sky Sea", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 800, 600, 0);
  }
  if (screen == NULL) {
    fprintf(stderr, "Failed to create window\r\n");
    exit(1);
  }
  if (windowed != 1) {
    /* Workaround on Mac OSX Mojave where the letterboxing in fullscreen is a red border. Much slower rendering with this workaround */
#ifdef __APPLE__
    if (gpu == 1)
      renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    else
      renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
#else
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
#endif
  }
  else {
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  }
  if (renderer == NULL) {
    fprintf(stderr, "Failed to create renderer\r\n");
    exit(1);
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer, 800, 600);
  bgTexture = loadTextureFromLargeXpm(renderer, Scene8_xpm, Scene8_xpm_tmp, Scene8_xpm_width, Scene8_xpm_height);
  cloudTexture = loadTextureFromLargeXpm(renderer, Cloud1_xpm, Cloud1_xpm_tmp, Cloud1_xpm_width, Cloud1_xpm_height);
  curTicks = SDL_GetTicks();
  fgTexture = loadTextureFromLargeXpm(renderer, DockSupports3_xpm, DockSupports3_xpm_tmp, DockSupports3_xpm_width, DockSupports3_xpm_height);
  SDL_SetTextureBlendMode(fgTexture, SDL_BLENDMODE_BLEND);
  convertXpmToBoolMap(Fish5_xpm, fishBoolMap, 71, 1846, 5);
  convertBoolmapToOutlinemap(fishBoolMap, fishOutlineMap, 71, 1846);
  fishTexture = loadTextureFromXpm(renderer, Fish5_xpm);
  convertXpmToBoolMap(Fish5Flip_xpm, fishFlipBoolMap, 71, 1846, 5);
  convertBoolmapToOutlinemap(fishFlipBoolMap, fishFlipOutlineMap, 71, 1846);
  fishFlipTexture = loadTextureFromXpm(renderer, Fish5Flip_xpm);
  fishGlowTexture = loadTextureFromXpm(renderer, FishGlow_xpm);
  fishGlowFlipTexture = loadTextureFromXpm(renderer, FishGlowFlip_xpm);
  hookTexture = loadTextureFromXpm(renderer, FishHook_xpm);
  for (i = 0; i < 4; ++i) {
    if (volat == 0)
      volat = 1;
    offscreenBuffer[i] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
      800, 600);
    SDL_SetTextureBlendMode(offscreenBuffer[i], SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, offscreenBuffer[i]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
  }
  player1PoleNoFishTexture = loadTextureFromXpm(renderer, PoleNoFish1_xpm);
  player1PoleFishTexture = loadTextureFromXpm(renderer, PoleFish1_xpm);
  player2PoleNoFishTexture = loadTextureFromXpm(renderer, PoleNoFish1Flip_xpm);
  player2PoleFishTexture = loadTextureFromXpm(renderer, PoleFish1Flip_xpm);
  pointFishTexture = loadTextureFromXpm(renderer, PointFish_xpm);
  radTexture = loadTextureFromXpm(renderer, MowhawkFisher2_xpm);
  radGlowTexture = loadTextureFromXpm(renderer, MowhawkFisherGlow2_xpm);
  rippleTexture1 = loadTextureFromXpm(renderer, Ripple1_xpm);
  rippleTexture2 = loadTextureFromXpm(renderer, Ripple2_xpm);
  rippleTexture3 = loadTextureFromXpm(renderer, Ripple3_xpm);
  rippleTexture4 = loadTextureFromXpm(renderer, Ripple4_xpm);
  rippleTexture5 = loadTextureFromXpm(renderer, Ripple5_xpm);
  rippleTexture6 = loadTextureFromXpm(renderer, Ripple6_xpm);
  rippleTimeout = 0;
  rippleTimeout2 = 0;
  rippleTimeout3 = 0;
  rippleTimeout4 = 0;
  rippleInterval3 = 700;
  rippleInterval4 = 800;
  seaHorseTexture = loadTextureFromXpm(renderer, SeaHorse_xpm);
  seaHorseFlipTexture = loadTextureFromXpm(renderer, SeaHorseFlip_xpm);
  seaHorseYBase = 255.0;
  seaweed1BottomTexture = loadTextureFromXpm(renderer, Seaweed1Bottom_xpm);
  seaweed1TopTexture = loadTextureFromXpm(renderer, Seaweed1Top_xpm);
  volat = 0;
  for (i = 0; i < 9; ++i) {
    if (volat == 0)
      volat = 1;
    seaweedOffset[i] = 0;
    seaweedOffsetDirection[i] = (rand() % 12000 % 2 == 0) ? -1 : 1;
    seaweedOffsetTimeout[i] = rand() % 777 + 333;
    seaweedOffsetTimer[i] = seaweedOffsetTimeout[i];
  }
  seaStarTexture = loadTextureFromXpm(renderer, SeaStar_xpm);
  sharkGlowTexture = loadTextureFromXpm(renderer, SharkGlow_xpm);
  sharkFinGlowTexture = loadTextureFromXpm(renderer, SharkFinGlow_xpm);
  sharkFinGlowFlipTexture = loadTextureFromXpm(renderer, SharkFinGlowFlip_xpm);
  sharkGlowFlipTexture = loadTextureFromXpm(renderer, SharkGlowFlip_xpm);
  convertXpmToBoolMap(Shark2_xpm, sharkBoolMap, 175, 14000, 6);
  convertBoolmapToOutlinemap(sharkBoolMap, sharkOutlineMap, 175, 14000);
  sharkTexture = loadTextureFromXpm(renderer, Shark2_xpm);
  sharkFinTexture = loadTextureFromXpm(renderer, SharkFin_xpm);
  sharkFinFlipTexture = loadTextureFromXpm(renderer, SharkFinFlip_xpm);
  convertXpmToBoolMap(SharkFlip_xpm, sharkFlipBoolMap, 175, 14000, 6);
  convertBoolmapToOutlinemap(sharkFlipBoolMap, sharkFlipOutlineMap, 175, 14000);
  salmonTexture = loadTextureFromXpm(renderer, Salmon_xpm);
  salmonFlipTexture = loadTextureFromXpm(renderer, SalmonFlip_xpm);
  sharkFlipTexture = loadTextureFromXpm(renderer, SharkFlip_xpm);
  sloogieTexture = loadTextureFromXpm(renderer, Sloogie_xpm);
  sloogieFlipTexture = loadTextureFromXpm(renderer, SloogieFlip_xpm);
  sloogieGlowTexture = loadTextureFromXpm(renderer, SloogieGlow_xpm);
  sloogieGlowFlipTexture = loadTextureFromXpm(renderer, SloogieGlowFlip_xpm);
  sloogieHideTexture = loadTextureFromXpm(renderer, SloogieHide_xpm);
  sloogieHideFlipTexture = loadTextureFromXpm(renderer, SloogieHideFlip_xpm);
  sloogieHideGlowTexture = loadTextureFromXpm(renderer, SloogieHideGlow_xpm);
  sloogieHideGlowFlipTexture = loadTextureFromXpm(renderer, SloogieHideGlowFlip_xpm);
  wesTexture = loadTextureFromXpm(renderer, ElderFisher2_xpm);
  wesGlowTexture = loadTextureFromXpm(renderer, ElderFisherGlow_xpm);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderTarget(renderer, offscreenBuffer[0]);
  bgfgDstRect.x = 0;
  bgfgDstRect.y = 0;
  bgfgDstRect.w = 800;
  bgfgDstRect.h = 600;
  radSrcRect.x = 0;
  radSrcRect.y = 0;
  radSrcRect.w = 50;
  radSrcRect.h = 131;
  radDstRect.x = 90;
  radDstRect.y = 120;
  radDstRect.w = 50;
  radDstRect.h = 131;
  wesSrcRect.x = 0;
  wesSrcRect.y = 0;
  wesSrcRect.w = 50;
  wesSrcRect.h = 126;
  wesDstRect.x = 660;
  wesDstRect.y = 125;
  wesDstRect.w = 50;
  wesDstRect.h = 126;
  SDL_RenderCopy(renderer, bgTexture, NULL, &bgfgDstRect);
  SDL_SetRenderTarget(renderer, offscreenBuffer[2]);
  SDL_RenderCopy(renderer, fgTexture, NULL, &bgfgDstRect);
  SDL_RenderCopy(renderer, radTexture, &radSrcRect, &radDstRect);
  if (mode != 0)
    SDL_RenderCopy(renderer, wesTexture, &wesSrcRect, &wesDstRect);
#ifndef NOMUSIC
  song1rwops = SDL_RWFromMem(UkeSong1wav, UkeSong1wavlen);
  if (song1rwops == NULL) {
    fprintf(stderr, "song1rwops is null exiting %s\r\n", SDL_GetError());
    exit(1);
  }
  song1 = Mix_LoadWAV_RW(song1rwops, 1);
  if (song1 == NULL) {
    fprintf(stderr, "song1 is null exiting %s\r\n", Mix_GetError());
    exit(1);
  }
  Mix_VolumeChunk(song1, ((float) MIX_MAX_VOLUME) * volume);
  song4rwops = SDL_RWFromMem(JMwav, JMwavlen);
  if (song4rwops == NULL) {
    fprintf(stderr, "song4rwops is null exiting %s\r\n", SDL_GetError());
    exit(1);
  }
  song4 = Mix_LoadWAV_RW(song4rwops, 1);
  if (song4 == NULL) {
    fprintf(stderr, "song4 is null exiting %s\r\n", Mix_GetError());
    exit(1);
  }
  Mix_VolumeChunk(song4, ((float) MIX_MAX_VOLUME) * volume);
  sound_castrwops = SDL_RWFromMem(sound_castwav, sound_castwavlen);
  if (sound_castrwops == NULL) {
    fprintf(stderr, "sound_castrwops is null exiting %s\r\n", SDL_GetError());
    exit(1);
  }
  sound_cast = Mix_LoadWAV_RW(sound_castrwops, 1);
  if (sound_cast == NULL) {
    fprintf(stderr, "song4 is null exiting %s\r\n", Mix_GetError());
    exit(1);
  }
  Mix_VolumeChunk(sound_cast, ((float) MIX_MAX_VOLUME) * .35f * volume);
  sound_fishcatchrwops = SDL_RWFromMem(sound_fishcatchwav, sound_fishcatchwavlen);
  if (sound_fishcatchrwops == NULL) {
    fprintf(stderr, "sound_fishcatchrwops is null exiting %s\r\n", SDL_GetError());
    exit(1);
  }
  sound_fishcatch = Mix_LoadWAV_RW(sound_fishcatchrwops, 1);
  if (sound_fishcatch == NULL) {
    fprintf(stderr, "song4 is null exiting %s\r\n", Mix_GetError());
    exit(1);
  }
  Mix_VolumeChunk(sound_fishcatch, ((float) MIX_MAX_VOLUME) * volume);
  sound_glimmerrwops = SDL_RWFromMem(sound_glimmerwav, sound_glimmerwavlen);
  if (sound_glimmerrwops == NULL) {
    fprintf(stderr, "sound_glimmerrwops is null exiting %s\r\n", SDL_GetError());
    exit(1);
  }
  sound_glimmer = Mix_LoadWAV_RW(sound_glimmerrwops, 1);
  if (sound_glimmer == NULL) {
    fprintf(stderr, "song4 is null exiting %s\r\n", Mix_GetError());
    exit(1);
  }
  Mix_VolumeChunk(sound_glimmer, ((float) MIX_MAX_VOLUME) * .7f * volume);
  sound_sharkbiterwops = SDL_RWFromMem(sound_sharkbitewav, sound_sharkbitewavlen);
  if (sound_sharkbiterwops == NULL) {
    fprintf(stderr, "sound_sharkbiterwops is null exiting %s\r\n", SDL_GetError());
    exit(1);
  }
  sound_sharkbite = Mix_LoadWAV_RW(sound_sharkbiterwops, 1);
  if (sound_sharkbite == NULL) {
    fprintf(stderr, "sharkbite is null exiting %s\r\n", Mix_GetError());
    exit(1);
  }
  Mix_VolumeChunk(sound_sharkbite, ((float) MIX_MAX_VOLUME) * .2f * volume);
#endif /* NOMUSIC */
  if (mode == 2) {
    set = SDLNet_AllocSocketSet(1);
    if (!set) {
      fprintf(stderr, "Failed to allocate socket set.\r\n");
      exit(1);
    }
    SDLNet_ResolveHost(&serverip, NULL, port);
    sock = SDLNet_TCP_Open(&serverip);
    if (!sock) {
      fprintf(stderr, "Failed to open socket.\r\n");
      exit(1);
    }
  }
  hookSize = tmpHookSize;
  winScore = tmpWinScore;
}
void load2(void)
{
  int i = 0;
  volatile int volat = 0;
  keystate = keystateprev = aikeystate = aikeystateprev = clientkeystate = clientkeystateprev = 0;
  for (i = 0; i < 5; ++i) {
    if (volat == 0)
      volat = 1;
    fishNibble[i] = 0;
    fishNibbleTimeout[i] = 777;
    fishOn[i] = 0;
    fishX[i] = rand() % 800 + 1.0;
    fishFacing[i] = rand() % 800 % 2 == 1 ? 1 : 0;
    fishRandomizePhase(fishPhase[i]);
    fishSalmon[i] = rand() % 12 == 0 ? 1 : 0;
    fishSpurtPhase[i] = rand() % 9999;
    fishSpeed[i] = 0.0;
    fishTimeSinceAboutFace[i] = 0;
    fishNextAboutFaceTime[i] = (Uint32) rand() % 8000 + 200;
    fishY[i] = 0.0;
    fishGlimmerX[i] = -1;
    fishGlowing[i] = -1;
    fishGlowAlpha[i] = 0.2;
    aiXDist[i] = 0;
    aiYDist[i] = 0;
  }
  fishYBase[0] = 336.0;
  fishYBase[1] = 370.0;
  fishYBase[2] = 404.0;
  fishYBase[3] = 438.0;
  fishYBase[4] = 472.0;
  lastTicks = curTicks;
  aiBurp = 0;
  aiBurpTimeout = 4000;
  aiBurpTimer = aiBurpTimeout;
  aiBurpOffTimeout = 4000;
  aiBurpOffTimer = aiBurpOffTimeout;
  player1Cast = 0;
  player1CaughtCount = 0;
  player1FishOn = -1;
  player1Glimmer1Rect.x = 0;
  player1Glimmer1Rect.y = 0;
  player1Glimmer1Rect.w = 0;
  player1Glimmer1Rect.h = 0;
  player1Glimmer2Rect.x = 0;
  player1Glimmer2Rect.y = 0;
  player1Glimmer2Rect.w = 0;
  player1Glimmer2Rect.h = 0;
  player1GlimmerReady = 1;
  player1HookSet = 0;
  player1LineX1 = 127.0;
  player1LineX2 = 127.0;
  player1LineY1 = 210.0;
  player1LineY2 = 210.0;
  player1PoleX1 = 127.0;
  player1PoleX2 = 127.0;
  player1PoleY1 = 155.0;
  player2Cast = 0;
  player2CaughtCount = 0;
  player2FishOn = -1;
  player2Glimmer1Rect.x = 0;
  player2Glimmer1Rect.y = 0;
  player2Glimmer1Rect.w = 0;
  player2Glimmer1Rect.h = 0;
  player2Glimmer2Rect.x = 0;
  player2Glimmer2Rect.y = 0;
  player2Glimmer2Rect.w = 0;
  player2Glimmer2Rect.h = 0;
  player2GlimmerReady = 1;
  player2HookSet = 0;
  player2LineX1 = 800 - 127.0;
  player2LineX2 = 800 - 127.0;
  player2LineY1 = 210.0;
  player2LineY2 = 210.0;
  player2PoleX1 = 800 - 127.0;
  player2PoleX2 = 800 - 127.0;
  player2PoleY1 = 155.0;
  playingVictorySong = 0;
  radGlowAlpha = 0.2;
  radGlowing = 0;
  renderTimeout = 12;
  renderTimer = (int) renderTimeout;
  rippleFrame = 0;
  rippleFrame2 = 0;
  rippleFrame3 = 0;
  rippleFrame4 = 0;
  rippleInterval = 500;
  rippleInterval2 = 500;
  rippleInterval3 = 700;
  rippleInterval4 = 800;
  cloudDstRect.x = 0;
  cloudDstRect.y = 0;
  cloudDstRect.w = 800;
  cloudDstRect.h = 200;
  cloudSrcRect.x = 0;
  cloudSrcRect.y = 0;
  cloudSrcRect.w = 800;
  cloudSrcRect.h = 200;
  cloudDstRect2.x = 0;
  cloudDstRect2.y = 0;
  cloudDstRect2.w = 0;
  cloudDstRect2.h = 200;
  cloudSrcRect2.x = 0;
  cloudSrcRect2.y = 0;
  cloudSrcRect2.w = 0;
  cloudSrcRect2.h = 200;
  cloudX = 0;
  seaHorseX = 800;
  seaHorseYBase = 350;
  seaHorseY = seaHorseYBase;
  seaStarX = 800;
  seaStarY = 550;
  seaStarBox.x = seaStarX;
  seaStarBox.y = seaStarY;
  seaStarBox.w = 32;
  seaStarBox.h = 32;
  sharkGlowAlpha = 0.2;
  sharkGlowing = 0;
  sharkSpeed = 0.05;
  sharkX = 302;
  sharkY = 241;
  sharkBox.x = sharkX;
  sharkBox.y = sharkY;
  sharkBox.w = 175;
  sharkBox.h = 80;
  sharkLeftBox.x = sharkX;
  sharkLeftBox.y = sharkY;
  sharkLeftBox.w = 175;
  sharkLeftBox.h = 80;
  sharkRightBox.x = sharkX;
  sharkRightBox.y = sharkY;
  sharkRightBox.w = 175;
  sharkRightBox.h = 80;
  seaHorseFacing = 0;
  seaHorseGo = 0;
  seaStarGo = 0;
  fishRandomizePhase(seaHorsePhase);
  sharkFacing = rand() % 800 % 2 == 1 ? 1 : 0;
  sloogieFacing = rand() % 800 % 2 == 1 ? 1 : 0;
  sloogieGlowAlpha = 0.2;
  sloogieGlowing = 0;
  sloogieHide = 0;
  sloogieHideTimeout = 30000;
  sloogieHideX = rand() % 543 + 90;
  sloogieOffscreenTimeout = 30000;
  sloogieSpeed = 0;
  sloogieX = sloogieFacing == 1 ? -177 : 800;
  sloogieBox.w = 166.0 * (177.0 / 454.0);
  sloogieBox.h = 52.0 * (77.0 / 169.0);
  sloogieBox.x = sloogieFacing == 1 ? sloogieX + 177.0 - sloogieBox.w : sloogieX;
  sloogieBox.y = 491;
  netTimeout = 12;
  netTimer = (int) netTimeout;
  wesGlowAlpha = 0.2;
  wesGlowing = 0;
  winTimeout = 5000;
#ifndef NOMUSIC
  if (curChannel > -1)
    Mix_HaltChannel(curChannel);
  curChannel = Mix_PlayChannel(-1, song1, -1); /* TODO move this somewhere else */
#endif
}
SDL_Texture *loadTextureFromLargeXpm(SDL_Renderer *r, char xpm[], char *arg[], const int width, const int height) {
  int i = 0;
  volatile int volat = 0;
  for (i = 0; i < height; ++i) {
    if (volat == 0)
      volat = 1;
    arg[i]=&(xpm[i*width]);
  }
  return loadTextureFromXpm(r, arg);
}
SDL_Texture *loadTextureFromXpm(SDL_Renderer *r, char **xpm)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_ReadXPMFromArray(xpm);
    if (surface == NULL) {
      fprintf(stderr, "Failed to load xpm surface\r\n");
      exit(1);
    }
    texture = SDL_CreateTextureFromSurface(r, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
      fprintf(stderr, "Failed to load texture\r\n");
      exit(1);
    }
    return texture;
}
int main(void) {
  volatile int volatwhil = 0;
#ifndef _WIN32
  signal(SIGPIPE, SIG_IGN);
#endif
  backupConfig();
  seed = (time_t)time(0);
/* TODO wiki.libsdl.org create window "you must set the nshighresolutioncapable info.plist property to YES" on mac. */
  srand(seed);
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); /* TODO check return value */
  IMG_Init(IMG_INIT_PNG); /* TODO check return value */
#ifndef NOMUSIC
  Mix_Init(0); /* TODO check return value */
  SDLNet_Init(); /* TODO check return value */
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    fprintf(stderr, "Failed to open audio\r\n");
    exit(1);
  }
  if (Mix_AllocateChannels(16) == -1) {
    fprintf(stderr, "Failed to open channel\r\n");
    exit(1);
  }
  Mix_Volume(-1, MIX_MAX_VOLUME);
#endif /* NOMUSIC */
  atexit(atExitQuit);
  load();
  load2();
  while(1) {
    if (volatwhil == 0)
      volatwhil = 1;
    keyboard();
    lastTicks = curTicks;
    curTicks = SDL_GetTicks();
    if (curTicks - lastTicks > 200)
      lastTicks = curTicks - 200;
    if (curTicks >= lastTicks) /* Wraps every 43 days */
      update(curTicks - lastTicks);
    else
      update(UINT_MAX - lastTicks + curTicks);
  }
  return 0;
}
void metrics(Uint32 interval) {
  totalFrames += curFrames;
  totalMs += interval;
  curFrames = 0;
}
size_t mystrnlen(char *s, size_t maxlen) {
  size_t locali = 0;
  volatile int volat = 0;
  for (locali = 0; locali < maxlen; ++locali) {
    if (volat == 0)
      volat = 1;
    if (s[locali] == '\0')
      return locali;
  }
  if (locali == 0)
    return 0;
  return maxlen;
}
void proc(Uint32 interval) {
  SDL_Rect fishBox = { 0, 0, 0, 0 };
  SDL_Rect fishMouthBox = { 0, 0, 0, 0};
  SDL_Rect hookBox = { 0, 0, 0, 0};
  SDL_Rect hookBox2 = { 0, 0, 0, 0};
  float tmpFishX = 0.0f;
  int sharkSpotted = 0;
  int i = 0;
  int j = 0;
  volatile int volat = 0;
  if (mode != 3 && player1Cast == 0) {
    player1LineX1 = player1LineX2 = player1PoleX2 = rand() % (395 - 173) + 173;
    player1LineY2 = rand() % (550 - 245) + 245;
    player1Cast = 1;
    Mix_PlayChannel(-1, sound_cast, 0);
  }
  if ((mode == 3 && player2Cast == 0) 
      || ((mode == 4 || mode == 2) && player2Cast == 0)
      || (mode == 1 && player2Cast == 0)) {
    player2LineX1 = player2LineX2 = player2PoleX1 = rand() % (800 - 575) + 575;
    player2LineY2 = rand() % (550 - 245) + 245;
    player2Cast = 1;
    Mix_PlayChannel(-1, sound_cast, 0);
  }
  if (mode != 0 && (player1CaughtCount >= winScore || player2CaughtCount >= winScore)) {
#ifndef NOMUSIC
    if (playingVictorySong == 0) {
      playingVictorySong = 1;
      Mix_HaltChannel(curChannel);
      curChannel = Mix_PlayChannel(-1, song4, -1);
    }
#endif
    if (winTimeout > 0)
      winTimeout -= (int) interval;
    if (winTimeout <= 0 && ((clientkeystate & 0x1000) == 0x1000 || (clientkeystate & 0x10) == 0x10 || ((keystate & 0x1000) == 0x1000 || (keystate & 0x10) == 0x10)))
      load2();
    return;
  }
  player1HookRecoverTimeout -= (int) interval;
  if (player1HookRecoverTimeout < -125) {
    player1HookRecoverTimeout = -125;
  }
  if (player1HookRecoverTimeout < 0)
    player1HookSet = 0;
  else if (player1HookSet > 0)
    player1LineY2 += 0.04 * ((float) interval);
  if(mode != 3 && player1Cast == 1 && ((keystate & 0x1) == 0x1 && (keystate & 0x2) != 0x2)) {
    player1PoleX2 -= 0.1200000 * interval;
  }
  else if(mode != 3 && player1Cast == 1 && ((keystate & 0x2) == 0x2 && (keystate & 0x1) != 0x1)) {
    player1PoleX2 += 0.1200000 * interval;
  }
  if (player1PoleX2 > 400)
    player1PoleX2 = 400;
  if (player1PoleX2 < 175)
    player1PoleX2 = 175;
  if(mode != 3 && player1Cast == 1 && ((keystate & 0x1) == 0x1 && (keystate & 0x2) != 0x2)) {
    player1LineX1 -= 0.1200000 * interval;
  }
  else if(mode != 3 && player1Cast == 1 && ((keystate & 0x2) == 0x2 && (keystate & 0x1) != 0x1)) {
    player1LineX1 += 0.1200000 * interval;
  }
  if (player1LineX2 > player1LineX1) {
    player1LineX2 -= 0.07000000 * interval;

    if (player1LineX2 < player1LineX1)
      player1LineX2 = player1LineX1;
  }
  if (player1LineX2 < player1LineX1) {
    player1LineX2 += 0.07000000 * interval;

    if (player1LineX2 > player1LineX1)
      player1LineX2 = player1LineX1;
  }
  if (player1LineX1 > 395.0)
    player1LineX1 = 395.0;
  if (player1LineX1 < 173.0)
    player1LineX1 = 173.0;
  if (player1LineX2 > 395.0)
    player1LineX2 = 395.0;
  if (player1LineX2 < 173.0)
    player1LineX2 = 173.0;
  if(mode != 3 && player1Cast == 1 && ((keystate & 0x4) == 0x4 && (keystate & 0x8) != 0x8)) {
    player1LineY2 -= 0.07000000 * interval;
    if (player1FishOn > -1 && fishOn[player1FishOn])
      fishY[player1FishOn] -= 0.0500000 * interval;
  }
  else if(mode != 3 && player1Cast == 1 && ((keystate & 0x8) == 0x8 && (keystate & 0x4) != 0x4)) {
    player1LineY2 += 0.07000000 * interval; 
  }
  if (mode != 3 && (seaHorseGo != 1 && radGlowing == 1 && (keystate & 0x20) == 0x20 && (keystateprev & 0x20) != 0x20)) {
    radGlowing = 0;
    seaHorseGo = 1;
  }
  if (mode != 3 && player1Cast == 1 && (player1HookSet == 0 && player1FishOn >= 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10)) {
    fishY[player1FishOn] -= 16;
    player1HookRecoverTimeout = 777;
    player1HookSet = 1;
    player1GlimmerReady = 1;
  }
  player1GlimmerTimeout -= (int) interval;
  if (player1GlimmerTimeout < -125)
    player1GlimmerTimeout = -125;
  if (mode != 3 && player1Cast == 1 && player1GlimmerReady == 1 && (player1HookRecoverTimeout < 125 && player1HookRecoverTimeout > -125 && player1FishOn == -1 && (keystate & 0x10) != 0x10 && (keystateprev & 0x10) == 0x10)) {
    player1GlimmerXBase = player1LineX2;
    player1GlimmerY = player1LineY2;
    player1GlimmerTimeout = 500;
    Mix_PlayChannel(-1, sound_glimmer, 0);
  }
  if (player1GlimmerTimeout > -125 && player1GlimmerTimeout <= 500) {
    player1Glimmer1Rect.x = player1GlimmerXBase - 1.0 * (500.0 - ((float) player1GlimmerTimeout));
    player1Glimmer1Rect.y = player1GlimmerY;
    player1Glimmer2Rect.x = player1GlimmerXBase + 1.0 * (500.0 - ((float) player1GlimmerTimeout));
    player1Glimmer2Rect.y = player1GlimmerY;
    player1Glimmer1Rect.w = 2;
    player1Glimmer2Rect.w = 2;
    player1Glimmer1Rect.h = 2;
    player1Glimmer2Rect.h = 2;
  }
  if (player1LineY2 > 550.0)
    player1LineY2 = 550.0;
  if (player1LineY2 < 245.0)
    player1LineY2 = 245.0;
  player2HookRecoverTimeout -= (int) interval;
  if (player2HookRecoverTimeout < -125) {
    player2HookRecoverTimeout = -125;
  }
  if (player2HookRecoverTimeout < 0)
    player2HookSet = 0;
  else if (player2HookSet > 0)
    player2LineY2 += 0.04 * ((float) interval);
  if((mode == 3 && player2Cast == 1 &&(keystate & 0x1) == 0x1 && (keystate & 0x2) != 0x2)
    || (mode == 4 && player2Cast == 1 && (keystate & 0x100) == 0x100 && (keystate & 0x200) != 0x200)
    || (mode == 1 && player2Cast == 1 && (aikeystate & 0x100) == 0x100 && (aikeystate & 0x200) != 0x200) 
    || (mode == 2 && player2Cast == 1 && (clientkeystate & 0x100) == 0x100 && (clientkeystate & 0x200) != 0x200)) {
    player2PoleX1 -= 0.1200000 * interval;
  }
  else if((mode == 3 && player2Cast ==  1 && (keystate & 0x2) == 0x2 && (keystate & 0x1) != 0x1)
          || (mode == 4 && player2Cast == 1 && (keystate & 0x200) == 0x200 && (keystate & 0x100) != 0x100)
          || (mode == 1 && player2Cast == 1 && (aikeystate & 0x200) == 0x200 && (aikeystate & 0x100) != 0x100)
          || (mode == 2 && player2Cast == 1 && (clientkeystate & 0x200) == 0x200 && (clientkeystate & 0x100) != 0x100)) {
    player2PoleX1 += 0.1200000 * interval;
  }
  if (player2PoleX1 < 400)
    player2PoleX1 = 400;
  if (player2PoleX1 > 800 - 175)
    player2PoleX1 = 800 - 175;
  if((mode == 3 && player2Cast == 1 && (keystate & 0x1) == 0x1 && (keystate & 0x2) != 0x2)
     || (mode == 4 && player2Cast == 1 && (keystate & 0x100) == 0x100 && (keystate & 0x200) != 0x200)
     || (mode == 1 && player2Cast == 1 && (aikeystate & 0x100) == 0x100 && (aikeystate & 0x200) != 0x200)
     || (mode == 2 && player2Cast == 1 && (clientkeystate & 0x100) == 0x100 && (clientkeystate & 0x200) != 0x200)) {
    player2LineX1 -= 0.1200000 * interval;
  }
  else if((mode == 3 && player2Cast == 1 && (keystate & 0x2) == 0x2 && (keystate & 0x1) != 0x1)
        || (mode == 4 && player2Cast == 1 && (keystate & 0x200) == 0x200 && (keystate & 0x100) != 0x100)
        || (mode == 1 && player2Cast == 1 && (aikeystate & 0x200) == 0x200 && (aikeystate & 0x100) != 0x100)
        || (mode == 2 && player2Cast == 1 && (clientkeystate & 0x200) == 0x200 && (clientkeystate & 0x100) != 0x100)) {
    player2LineX1 += 0.1200000 * interval;
  }
  if (player2LineX2 > player2LineX1) {
    player2LineX2 -= 0.07000000 * interval;

    if (player2LineX2 < player2LineX1)
      player2LineX2 = player2LineX1;
  }
  if (player2LineX2 < player2LineX1) {
    player2LineX2 += 0.07000000 * interval;

    if (player2LineX2 > player2LineX1)
      player2LineX2 = player2LineX1;
  }
  if (player2LineX1 < 800 - 395.0)
    player2LineX1 = 800 - 395.0;
  if (player2LineX1 > 800 - 173.0)
    player2LineX1 = 800 - 173.0;
  if (player2LineX2 < 800 - 395.0)
    player2LineX2 = 800 - 395.0;
  if (player2LineX2 > 800 - 173.0)
    player2LineX2 = 800 - 173.0;
  if((mode == 3 && player2Cast == 1 && (keystate & 0x4) == 0x4 && (keystate & 0x8) != 0x8)
     || (mode == 4 && player2Cast == 1 && (keystate & 0x400) == 0x400 && (keystate & 0x800) != 0x800)
     || (mode == 1 && player2Cast == 1 && (aikeystate & 0x400) == 0x400 && (aikeystate & 0x800) != 0x800)
     || (mode == 2 && player2Cast == 1 && (clientkeystate & 0x400) == 0x400 && (clientkeystate & 0x800) != 0x800)) {
    player2LineY2 -= 0.07000000 * interval;
    if (player2FishOn > -1 && fishOn[player2FishOn])
      fishY[player2FishOn] -= 0.0500000 * interval;
  }
  else if((mode == 3 && player2Cast == 1 && (keystate & 0x8) == 0x8 && (keystate & 0x4) != 0x4)
          || (mode == 4 && player2Cast == 1 && (keystate & 0x800) == 0x800 && (keystate & 0x400) != 0x400)
          || (mode == 1 && player2Cast == 1 && (aikeystate & 0x800) == 0x800 && (aikeystate & 0x400) != 0x400)
          || (mode == 2 && player2Cast == 1 && (clientkeystate & 0x800) == 0x800 && (clientkeystate & 0x400) != 0x400)) {
    player2LineY2 += 0.07000000 * interval; 
  }
  if ((mode == 3 && seaStarGo != 1 && wesGlowing == 1 && (keystate & 0x20) == 0x20 && (keystateprev & 0x20) != 0x20) 
      || (mode == 4 && seaStarGo != 1 && wesGlowing == 1 && (keystate & 0x2000) == 0x2000 && (keystateprev & 0x2000) != 0x2000)
      || (mode == 1 && seaStarGo != 1 && wesGlowing == 1 && (aikeystate & 0x2000) == 0x2000 && (aikeystateprev & 0x2000) != 0x2000)
      || (mode == 2 && seaStarGo != 1 && wesGlowing == 1 && (clientkeystate & 0x2000) == 0x2000 && (clientkeystateprev & 0x2000) != 0x2000)) {
    wesGlowing = 0;
    seaStarGo = 1;
  }
  if ((mode == 3 && player2Cast == 1 && player2HookSet == 0 && player2FishOn >= 0 && player2Cast == 1 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10) 
     || (mode == 4 && player2Cast == 1 && player2HookSet == 0 && player2FishOn >= 0 && player2Cast == 1 && (keystate & 0x1000) == 0x1000 && (keystateprev & 0x1000) != 0x1000)
     || (mode == 1 && player2Cast == 1 && player2HookSet == 0 && player2FishOn >= 0 && player2Cast == 1 && (aikeystate & 0x1000) == 0x1000 && (aikeystateprev & 0x1000) != 0x1000)
     || (mode == 2 && player2Cast == 1 && player2HookSet == 0 && player2FishOn >= 0 && player2Cast == 1 && (clientkeystate & 0x1000) == 0x1000 && (clientkeystateprev & 0x1000) != 0x1000)) {
    fishY[player2FishOn] -= 16;
    player2HookRecoverTimeout = 777;
    player2HookSet = 1;
    player2GlimmerReady = 1;
  }
  player2GlimmerTimeout -= (int) interval;
  if (player2GlimmerTimeout < -125)
    player2GlimmerTimeout = -125;
  if ((mode == 3 && player2Cast == 1 && player2GlimmerReady == 1 && player2HookRecoverTimeout < 125 && player2HookRecoverTimeout > -125 && player2FishOn == -1 && (keystate & 0x10) != 0x10 && (keystateprev & 0x10) == 0x10)
      || (mode == 4 && player2Cast == 1 && player2GlimmerReady == 1 && player2HookRecoverTimeout < 125 && player2HookRecoverTimeout > -125 && player2FishOn == -1 && (keystate & 0x1000) != 0x1000 && (keystateprev & 0x1000) == 0x1000)
      || (mode == 1 && player2Cast == 1 && player2GlimmerReady == 1 && player2HookRecoverTimeout < 125 && player2HookRecoverTimeout > -125 && player2FishOn == -1 && (aikeystate & 0x1000) != 0x1000 && (aikeystateprev & 0x1000) == 0x1000)
      || (mode == 2 && player2Cast == 1 && player2GlimmerReady == 1 && player2HookRecoverTimeout < 125 && player2HookRecoverTimeout > -125 && player2FishOn == -1 && (clientkeystate & 0x1000) != 0x1000 && (clientkeystateprev & 0x1000) == 0x1000)) {
    player2GlimmerXBase = player2LineX2;
    player2GlimmerY = player2LineY2;
    player2GlimmerTimeout = 500;
    Mix_PlayChannel(-1, sound_glimmer, 0);
  }
  if (player2GlimmerTimeout > -125 && player2GlimmerTimeout <= 500) {
    player2Glimmer1Rect.x = player2GlimmerXBase - 1.0 * (500.0 - ((float) player2GlimmerTimeout));
    player2Glimmer1Rect.y = player2GlimmerY;
    player2Glimmer2Rect.x = player2GlimmerXBase + 1.0 * (500.0 - ((float) player2GlimmerTimeout));
    player2Glimmer2Rect.y = player2GlimmerY;
    player2Glimmer1Rect.w = 2;
    player2Glimmer2Rect.w = 2;
    player2Glimmer1Rect.h = 2;
    player2Glimmer2Rect.h = 2;
  }
  if (player2LineY2 > 550.0)
    player2LineY2 = 550.0;
  if (player2LineY2 < 245.0)
    player2LineY2 = 245.0;
  rippleTimeout += (int) interval;
  if (rippleTimeout > rippleInterval && rippleInterval >= 1) {
    rippleTimeout %= rippleInterval;
    rippleFrame++;
    rippleFrame %= 3;
  }
  rippleTimeout2 += (int) interval;
  if (rippleTimeout2 > rippleInterval2 && rippleInterval2 >= 1) {
    rippleTimeout2 %= rippleInterval2;
    rippleFrame2++;
    rippleFrame2 %= 3;
  }
  rippleTimeout3 += (int) interval;
  if (rippleTimeout3 > rippleInterval3 && rippleInterval3 >= 1) {
    rippleTimeout3 %= rippleInterval3;
    rippleFrame3++;
    rippleFrame3 %= 3;
  }
  rippleTimeout4 += (int) interval;
  if (rippleTimeout4 > rippleInterval4 && rippleInterval4 >= 1) {
    rippleTimeout4 %= rippleInterval4;
    rippleFrame4++;
    rippleFrame4 %= 3;
  }
  if (mode != 3 && player1Cast == 1 && (player1HookSet == 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10)) {
    player1LineY2 -= 31;
    if (player1LineY2 < 245.0)
      player1LineY2 = 245.0;
  }
  if ((mode == 3 && player2Cast == 1 && (player2HookSet == 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10))
      || (mode == 4 && player2Cast == 1 && (player2HookSet == 0 && (keystate & 0x1000) == 0x1000 && (keystateprev & 0x1000) != 0x1000))
      || (mode == 1 && player2Cast == 1 && (player2HookSet == 0 && (aikeystate & 0x1000) == 0x1000 && (aikeystateprev & 0x1000) != 0x1000))
      || (mode == 2 && player2Cast == 1 && (player2HookSet == 0 && (clientkeystate & 0x1000) == 0x1000 && (clientkeystateprev & 0x1000) != 0x1000))) {
    player2LineY2 -= 31;
    if (player2LineY2 < 245.0)
      player2LineY2 = 245.0;
  }
  sharkX += sharkSpeed * ((float) interval) * (sharkFacing == 0 ? -1.0 : 1.0);
  sharkBox.x = sharkX;
  sharkBox.y = sharkY;
  sharkLeftBox.x = 0;
  sharkLeftBox.w = sharkX;
  sharkRightBox.x = sharkX + 175;
  sharkRightBox.w = 800 - (sharkX + 175);
  if (sharkX < 116)
    sharkFacing = 1;
  if (sharkX > 519)
    sharkFacing = 0;
  for (i = 0; i < 5; ++i) {
    if (volat == 0)
      volat = 1;
    if (mode != 3 && player1Cast == 1 && (player1HookSet == 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10)) {
      if (player1FishOn != i && fishNibble[i] == 1) {
        volatile int volat2 = 0;
        player1PoleY1 = 155;
        player1FishOn = i;
        fishOn[i] = 1;
        rippleInterval = 300;
        for (j = 0; j < 5; ++j) {
          if (volat2 == 0)
            volat2 = 1;
          if (fishNibble[j] == 1)
            fishNibble[j] = 0;
        }
      }
    }
    if ((mode == 3 && player2Cast == 1 && player2HookSet == 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10)
        || (mode == 4 && player2Cast == 1 && player2HookSet == 0 && (keystate & 0x1000) == 0x1000 && (keystateprev & 0x1000) != 0x1000)
        || (mode == 1 && player2Cast == 1 && player2HookSet == 0 && (aikeystate & 0x1000) == 0x1000 && (aikeystateprev & 0x1000) != 0x1000)
        || (mode == 2 && player2Cast == 1 && player2HookSet == 0 && (clientkeystate & 0x1000) == 0x1000 && (clientkeystateprev & 0x1000) != 0x1000)) {
      if (player2FishOn != i && fishNibble[i] == 2) {
        volatile int volat2 = 0;
        player2PoleY1 = 155;
        player2FishOn = i;
        fishOn[i] = 2;
        rippleInterval2 = 300;
        for (j = 0; j < 5; ++j) {
          if (volat2 == 0)
            volat2 = 1;
          if (fishNibble[j] == 2)
            fishNibble[j] = 0;
        }
      }
    }
    if ((fishOn[i] == 0 && fishTimeSinceAboutFace[i] >= fishNextAboutFaceTime[i])
        || (fishOn[i] != 0 && fishTimeSinceAboutFace[i] >= fishNextAboutFaceTime[i] / 5)) {
      fishSpurtPhase[i] = 0.0;
      fishTimeSinceAboutFace[i] = 0;
      fishNextAboutFaceTime[i] = (Uint32) rand() % 8000 + 200;
      if (fishFacing[i] != 0 && (fishNibble[i] == 0 || fishOn[i] != 0))
        fishFacing[i] = 0;
      else if (fishNibble[i] == 0 || fishOn[i] != 0)
        fishFacing[i] = 1;
    }
    else
      fishTimeSinceAboutFace[i] += interval;
    if (fishOn[i] == 1) {
      if (fishX[i] < player1LineX1 - MAX(50, (player1LineY2 - 267) / 12) && player1LineX1 - MAX(50, (player1LineY2 - 267) / 12) - fishX[i] > player1LineY2 - 267)
        fishFacing[i] = 1;
      if (fishX[i] + 71 > player1LineX1 + MAX(50, (player1LineY2 - 267) / 12 ) && fishX[i] + 71 - player1LineX1 - MAX(50, (player1LineY2 - 267) / 12) > player1LineY2 - 267)
        fishFacing[i] = 0;
    }
    if (fishOn[i] == 2) {
      if (fishX[i] < player2LineX1 - MAX(50, (player2LineY2 - 267) / 12) && player2LineX1 - MAX(50, (player2LineY2 - 267) / 12) - fishX[i] > player2LineY2 - 267)
        fishFacing[i] = 1;
      if (fishX[i] + 71 > player2LineX1 + MAX(50, (player2LineY2 - 267) / 12) && fishX[i] + 71 - player2LineX1 - MAX(50, (player2LineY2 - 267) / 12) > player2LineY2 - 267)
        fishFacing[i] = 0;
    }
    if (player1FishOn != i && player2FishOn != i && seaHorseGo == 1 && seaHorseX <= 500) {
      if (fishX[i] > seaHorseX)
        fishFacing[i] = 0;
      else
        fishFacing[i] = 1;
    }
    fishSpurtPhase[i] += interval;
    fishSpurtPhase[i] = wrapNumber(fishSpurtPhase[i], 0, 640);
    fishSpeed[i] = calculateLinearPositionValue(0.0, 640.0, 0.28125, 0.078125, fishSpurtPhase[i]);
    if (fishSalmon[i] != 0)
      fishSpeed[i] = calculateLinearPositionValue(0.0, 640.0, 0.33125, 0.128125, fishSpurtPhase[i]);
    if (fishOn[i] != 0)
      fishSpeed[i] = 0.5;
    fishMouthBox.x = fishFacing[i] == 0 ? fishX[i] : fishX[i] + 70;
    fishMouthBox.y = fishY[i] + 9;
    fishMouthBox.w = hookSize;
    fishMouthBox.h = hookSize;
    hookBox.x = player1LineX2;
    hookBox.y = player1LineY2;
    hookBox.w = hookSize;
    hookBox.h = hookSize;
    hookBox2.x = player2LineX2;
    hookBox2.y = player2LineY2;
    hookBox2.w = hookSize;
    hookBox2.h = hookSize;
    if (isCollision(&fishMouthBox, &hookBox, NULL, NULL) && fishOn[i] == 0 && player1FishOn == -1) {
      if (fishNibble[i] == 0)
        fishNibbleTimeout[i] = 777;
      fishNibble[i] = 1;
      fishGlimmerX[i] = -1;
      fishNibbleTimeout[i] -= (int) interval;
      fishX[i] = fishFacing[i] == 0 ? hookBox.x : hookBox.x - 71;
      if (fishOn[i] == 0)
        fishY[i] = hookBox.y - 9;
    }
    if (isCollision(&fishMouthBox, &hookBox2, NULL, NULL) && fishOn[i] == 0 && player2FishOn == -1) {
      if (fishNibble[i] == 0)
        fishNibbleTimeout[i] = 777;
      fishNibble[i] = 2;
      fishNibbleTimeout[i] -= (int) interval;
      fishX[i] = fishFacing[i] == 0 ? hookBox2.x : hookBox2.x - 71;
      if (fishOn[i] == 0)
        fishY[i] = hookBox2.y - 9;
    }
    if (((!isCollision(&fishMouthBox, &hookBox, NULL, NULL) && fishNibble[i] == 1)
        || (fishNibbleTimeout[i] < 0 && fishNibble[i] != 0)) &&
      ((!isCollision(&fishMouthBox, &hookBox2, NULL, NULL) && fishNibble[i] == 2)
        || (fishNibbleTimeout[i] < 0 && fishNibble[i] != 0)))
    {
      int a = rand() % 777 % 2;
      fishX[i] += a == 0 ? -15 : 15;
      fishFacing[i] = a;
      fishNibble[i] = 0;
    }
    if (fishNibble[i] != 0)
      fishSpeed[i] = 0;
    fishBox.x = fishX[i];
    fishBox.y = fishY[i];
    fishBox.w = 71;
    fishBox.h = 26;
    if (seaHorseGo != 1 && isCollision(&fishBox, &player1Glimmer1Rect, NULL, NULL) && player1GlimmerTimeout > -125 && fishOn[i] == 0 && fishGlimmerX[i] == -1) {
      fishFacing[i] = 1;
      fishGlimmerX[i] = player1LineX2;
      player1GlimmerTimeout = -125;
    }
    if (seaHorseGo != 1 && isCollision(&fishBox, &player1Glimmer2Rect, NULL, NULL) && player1GlimmerTimeout > -125 && fishOn[i] == 0 && fishGlimmerX[i] == -1) {
      fishFacing[i] = 0;
      fishGlimmerX[i] = player1LineX2;
      player1GlimmerTimeout = -125;
    }
    if (seaHorseGo != 1 && isCollision(&fishBox, &player2Glimmer1Rect, NULL, NULL) && player2GlimmerTimeout > -125 && fishOn[i] == 0 && fishGlimmerX[i] == -1) {
      fishFacing[i] = 1;
      fishGlimmerX[i] = player2LineX2;
      player2GlimmerTimeout = -125;
    }
    if (seaHorseGo != 1 && isCollision(&fishBox, &player2Glimmer2Rect, NULL, NULL) && player2GlimmerTimeout > -125 && fishOn[i] == 0 && fishGlimmerX[i] == -1) {
      fishFacing[i] = 0;
      fishGlimmerX[i] = player2LineX2;
      player2GlimmerTimeout = -125;
    }
    if (fishFacing[i] == 0 && fishX[i] <= fishGlimmerX[i])
        fishGlimmerX[i] = -1;
    if (fishFacing[i] == 1 && fishX[i] + 71 >= fishGlimmerX[i])
        fishGlimmerX[i] = -1;
    tmpFishX = fishX[i];
    fishX[i] += fishSpeed[i] * ((float) interval) * (fishFacing[i] == 0 ? -1.0 : 1.0);
 
    if (player1FishOn != i && player2FishOn != i && seaHorseGo == 1 && seaHorseX <= 500.0 ) {
      if (tmpFishX > seaHorseX && fishX[i] < seaHorseX)
        fishX[i] = seaHorseX + 1.0;
    }

    if (fishX[i] < -71.0)
      fishX[i] = 800.0;
    if (fishX[i] > 871.0)
      fishX[i] = -71.0;
    if (fishNibble[i] == 0 && fishOn[i] == 0)
      fishY[i] = fishYBase[i] + fishYDisplacement(fishX[i], fishPhase[i]);
    if (fishOn[i] == 1) {
      player1LineX2 = fishX[i] + (fishFacing[i] == 1 ? 70 : 0);
      player1LineY2 = fishY[i] + 9;
    }
    if (fishOn[i] == 2) {
      player2LineX2 = fishX[i] + (fishFacing[i] == 1 ? 70 : 0);
      player2LineY2 = fishY[i] + 9;
    }
    if (mode != 3 && i == player1FishOn && fishY[i] <= player1PoleY1 + 54) {
      Mix_PlayChannel(-1, sound_fishcatch, 0);
      player1Cast = 0;
      player1CaughtCount++;
      if (fishSalmon[i] == 1)
        player1CaughtCount++;
      fishY[i] = fishYBase[i] + fishYDisplacement(fishX[i], fishPhase[i]);
      fishOn[i] = 0;
      fishNibble[i] = 0;
      fishSalmon[i] = rand() % 12 == 0 ? 1 : 0;
      player1FishOn = -1;
      player1LineX2 = player1LineX1;
      rippleInterval = 500;
      /* player1HookSet = 0; Setting this to 0 here causes the hook to be automatically set after catch... at least as of now*/
      player1HookRecoverTimeout = -125;
      if (fishGlowing[i] == 1) {
        radGlowing = 1;
        fishGlowing[i] = -1;
      }
    }
    if ((mode == 3 && i == player2FishOn && fishY[i] <= player2PoleY1 + 54)
        || ((mode == 4 || mode == 2) && i == player2FishOn && fishY[i] <= player2PoleY1 + 54)
        || (mode == 1 && i == player2FishOn && fishY[i] <= player2PoleY1 + 54)) {
      Mix_PlayChannel(-1, sound_fishcatch, 0);
      player2Cast = 0;
      player2CaughtCount++;
      if (fishSalmon[i] == 1)
        player2CaughtCount++;
      fishY[i] = fishYBase[i] + fishYDisplacement(fishX[i], fishPhase[i]);
      fishOn[i] = 0;
      fishNibble[i] = 0;
      fishSalmon[i] = rand() % 12 == 0 ? 1 : 0;
      player2FishOn = -1;
      player2LineX2 = player2LineX1;
      rippleInterval2 = 500;
      /* player2HookSet = 0; Setting this to 0 here causes the hook to be automatically set after catch... at least as of now*/
      player2HookRecoverTimeout = -125;
      if (fishGlowing[i] == 1) {
        wesGlowing = 1;
        fishGlowing[i] = -1;
      }
    }
    if (sharkGlowing != 0)
      sharkSpeed = .22;
    else if (sharkFacing == 0 && isCollision(&fishBox, &sharkLeftBox, NULL, NULL)) {
      sharkSpeed = .20;
      sharkSpotted = 1;
    }
    else if (sharkFacing == 1 && isCollision(&fishBox, &sharkRightBox, NULL, NULL)) {
      sharkSpeed = .20;
      sharkSpotted = 1;
    }
    if (mode != 0 && player1FishOn == i && (isCollision(&sharkBox, &fishBox, sharkFacing == 0 ? sharkOutlineMap : sharkFlipOutlineMap, fishFacing[player1FishOn] == 0 ? fishOutlineMap : fishFlipOutlineMap) || isCollision(&seaStarBox, &fishBox, NULL, NULL))) {
      Mix_PlayChannel(-1, sound_sharkbite, 0);
      player1Cast = 0;
      fishY[i] = fishYBase[i] + fishYDisplacement(fishX[i], fishPhase[i]);
      player1LineX1 = 127.0;
      player1LineX2 = 127.0;
      player1LineY1 = 210.0;
      player1LineY2 = 210.0;
      player1PoleX1 = 127.0;
      player1PoleX2 = 127.0;
      player1PoleY1 = 155.0;
      fishOn[i] = 0;
      fishNibble[i] = 0;
      player1FishOn = -1;
      player1LineX2 = player1LineX1;
      rippleInterval = 500;
      player1HookSet = 0;
      player1HookRecoverTimeout = -125;
      if (fishGlowing[i] == 1)
        sharkGlowing = 1;
      else
        sharkGlowing = 0;
      fishGlowing[i] = -1;
      fishSalmon[i] = rand() % 12 == 0 ? 1 : 0;
    }
    if (mode != 0 && player2FishOn == i && isCollision(&sharkBox, &fishBox, sharkFacing == 0 ? sharkOutlineMap : sharkFlipOutlineMap, fishFacing[player2FishOn] == 0 ? fishOutlineMap : fishFlipOutlineMap))  {
      Mix_PlayChannel(-1, sound_sharkbite, 0);
      player2Cast = 0;
      fishY[i] = fishYBase[i] + fishYDisplacement(fishX[i], fishPhase[i]);
      player2LineX1 = 800 - 127.0;
      player2LineX2 = 800 - 127.0;
      player2LineY1 = 210.0;
      player2LineY2 = 210.0;
      player2PoleX1 = 800 - 127.0;
      player2PoleX2 = 800 - 127.0;
      player2PoleY1 = 155.0;
      fishOn[i] = 0;
      fishNibble[i] = 0;
      player2FishOn = -1;
      player2LineX2 = player2LineX1;
      rippleInterval2 = 500;
      player2HookSet = 0;
      player2HookRecoverTimeout = -125;
      if (fishGlowing[i] == 1)
        sharkGlowing = 1;
      else
        sharkGlowing = 0;
      fishGlowing[i] = -1;
      fishSalmon[i] = rand() % 12 == 0 ? 1 : 0;
    }
    if (isCollision(&fishBox, &sloogieBox, NULL, NULL) && sloogieGlowing == 1 && sloogieHide == 0) {
      fishGlowing[i] = 1;
      sloogieGlowing = 0;
    }
    if (fishGlowing[i] == 1)
      fishGlowAlpha[i] += 0.1 * interval;
    else
      fishGlowAlpha[i] = 0.2;
    if (fishGlowAlpha[i] > 254.0)
      fishGlowAlpha[i] = 0.2;
  }
  if (sharkSpotted == 0 && sharkGlowing == 0)
    sharkSpeed = 0.10;
  if (mode != 3 && player1Cast == 1 && (player1HookSet == 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10)) {
    player1HookRecoverTimeout = 777;
    player1HookSet = 1;
    player1GlimmerReady = 1;
  }
  if ((mode == 3 && player2Cast == 1 && player2HookSet == 0 && (keystate & 0x10) == 0x10 && (keystateprev & 0x10) != 0x10)
      || (mode == 4 && player2Cast == 1 && player2HookSet == 0 && (keystate & 0x1000) == 0x1000 && (keystateprev & 0x1000) != 0x1000)
      || (mode == 1 && player2Cast == 1 && player2HookSet == 0 && (aikeystate & 0x1000) == 0x1000 && (aikeystateprev & 0x1000) != 0x1000)
      || (mode == 2 && player2Cast == 1 && player2HookSet == 0 && (clientkeystate & 0x1000) == 0x1000 && (clientkeystateprev & 0x1000) != 0x1000)) {
    player2HookRecoverTimeout = 777;
    player2HookSet = 1;
    player2GlimmerReady = 1;
  }
  sloogieOffscreenTimeout -= (int) interval;
  if (sloogieOffscreenTimeout < 1) {
    sloogieOffscreenTimeout = 0;
    sloogieSpeed = sloogieFacing ? 0.02 : -0.02;
  }
  if ((sloogieFacing != 0 && sloogieX > sloogieHideX) ||
    (sloogieFacing == 0 && sloogieX < sloogieHideX)) {
    if (sloogieHide != 1) {
      sloogieHideTimeout = 30000;
      sloogieGlowing = 0;
    }
    sloogieHide = 1;
    sloogieSpeed = 0;
  }
  else
    sloogieX += sloogieSpeed * (float) interval;
  sloogieBox.x = sloogieFacing == 1 ? sloogieX + 177.0 - sloogieBox.w : sloogieX;
  if (sloogieHide == 1)
    sloogieHideTimeout -= (int) interval;
  if (sloogieHideTimeout < 0) {
    int lastSloogieHideX = sloogieHideX;
    volatile int volatwhil = 0;
    sloogieHide = 0;
    sloogieHideTimeout = 30000;
    lastSloogieHideX = sloogieHideX;
    while (abs(sloogieHideX - lastSloogieHideX) < 100) {
      if (volatwhil == 0)
        volatwhil = 1;
      sloogieHideX = rand() % 543 + 90;
    }
    if (sloogieHideX < sloogieX)
      sloogieFacing = 0;
    else
      sloogieFacing = 1;
  }
  if (sloogieHideTimeout < 12000)
    sloogieGlowing = 1;
  if (sloogieX > 623)
    sloogieFacing = 0;
  if (sloogieX < 0)
    sloogieFacing = 1;
  if (sloogieGlowing)
    sloogieGlowAlpha += 0.1 * interval;
  else
    sloogieGlowAlpha = 0.2;
  if (sloogieGlowAlpha > 254.0)
    sloogieGlowAlpha = 0.2;
  if (sharkGlowing != 0)
    sharkGlowAlpha += 0.1 * interval;
  else
    sharkGlowAlpha = 0.2;
  if (sharkGlowAlpha > 254.0)
    sharkGlowAlpha = 0.2;
  if (radGlowing)
    radGlowAlpha += 0.1 * interval;
  else
    radGlowAlpha = 0.2;
  if (radGlowAlpha > 254.0)
    radGlowAlpha = 0.2;
  if (wesGlowing)
    wesGlowAlpha += 0.1 * interval;
  else
    wesGlowAlpha = 0.2;
  if (wesGlowAlpha > 254.0)
    wesGlowAlpha = 0.2;
  if (seaHorseGo == 1) {
    seaHorseX -= 0.07 * interval;
    seaHorseY = seaHorseYBase + fishYDisplacement(seaHorseX, seaHorsePhase);
  }
  else
    seaHorseX = 800;
  if (seaHorseX < -40)
    seaHorseGo = 0;
  if (seaStarGo == 1 && player1FishOn >= 0) {
    if (seaStarX > fishX[player1FishOn] && seaStarY > 267) {
      float delX = (seaStarX - fishX[player1FishOn]) * 0.0007 * interval;
      float delY = (MAX(seaStarY, fishY[player1FishOn]) - MIN(fishY[player1FishOn], seaStarY)) * 0.0007 * interval;
      if (delX < 1 || fabs(delY) < 1) {
        delX = (seaStarX - fishX[player1FishOn]) / (MAX(seaStarY, fishY[player1FishOn]) - MIN(fishY[player1FishOn], seaStarY)) * 0.07 * interval;
        delY = (MAX(seaStarY, fishY[player1FishOn]) - MIN(fishY[player1FishOn], seaStarY)) / (seaStarX - fishX[player1FishOn]) * 0.07 * interval;
      }
      seaStarX -= delX;
      seaStarY += delY * (seaStarY < fishY[player1FishOn] ? 1 : -1);
    }
    else {
      seaStarX -= 0.07 * interval;
    }
  }
  else if (seaStarGo == 1 && player1FishOn < 0) {
    if (seaStarX > player1LineX2 && seaStarY > 267) {
      float delX = (seaStarX - player1LineX2) * 0.0007 * interval;
      float delY = (MAX(seaStarY, player1LineY2) - MIN(player1LineY2, seaStarY)) * 0.0007 * interval;
      if (delX < 1 || fabs(delY) < 1) {
        delX = (seaStarX - player1LineX2) / (MAX(seaStarY, player1LineY2) - MIN(player1LineY2, seaStarY)) * 0.07 * interval;
        delY = (MAX(seaStarY, player1LineY2) - MIN(player1LineY2, seaStarY)) / (seaStarX - player1LineX2) * 0.07 * interval;
      }
      seaStarX -= delX;
      seaStarY += delY * (seaStarY < player1LineY2 ? 1 : -1);
    }
    else {
      seaStarX -= 0.07 * interval;
    }
  }
  else if (seaStarGo != 1) {
    seaStarX = 800;
    seaStarY = 500;
  }
  seaStarBox.x = seaStarX;
  seaStarBox.y = seaStarY;
  if (seaStarX < -32 || seaStarX > 800 || seaStarY < -32 || seaStarY > 600)
    seaStarGo = 0;
  cloudX += 0.01 * interval;
  if (cloudX >= 1600)
    cloudX = 0.1;
  if (mode != 3 && player1Cast == 1 && (keystate & 0x10) != 0x10)
    player1GlimmerReady = 0;
  if ((mode == 3 && player2Cast == 1 && (keystate & 0x10) != 0x10)
      || (mode == 4 && (keystate & 0x1000) != 0x1000)
      || (mode == 1 && (aikeystate & 0x1000) != 0x1000)
      || (mode == 2 && (clientkeystate & 0x1000) != 0x1000))
    player2GlimmerReady = 0;
}
void procai(Uint32 interval) {
  int i = 0;
  int minYIndex = -1;
  volatile int volat = 0;
  aikeystateprev = aikeystate;
  aikeystate = 0;
  if (minYIndex >= 0 && minYIndex < 5)
    aiYDist[minYIndex] = 999;
  if (player2Cast == 0 && (aikeystateprev & 0x1000) != 0x1000)
    aikeystate |= 0x1000;
  for (i = 0; i < 5; ++i) {
    if (volat == 0)
      volat = 1;
    if (fishNibble[i] == 2 && (aikeystateprev & 0x1000) != 0x1000)
      aikeystate |= 0x1000;
    if (player2FishOn == -1) {
      aiYDist[i] = MAX(player2LineY2, fishY[i]) - MIN(player2LineY2, fishY[i]);
      aiXDist[i] = MAX(player2LineX2, fishX[i]) - MIN(player2LineX2, fishX[i]);
      if (minYIndex == -1 || (aiYDist[i] < aiYDist[minYIndex] && fishX[i] > 400))
        minYIndex = i;
    }
  }
  if (player2FishOn == -1) {
    if (minYIndex != -1 && player2LineY2 < (fishY[minYIndex] + 12))
      aikeystate |= 0x800;
    if (minYIndex != -1 && player2LineY2 > (fishY[minYIndex] + 12))
      aikeystate |= 0x400;
    if (minYIndex != -1 && player2LineX2 < (fishX[minYIndex] + 12))
      aikeystate |= 0x200;
    if (minYIndex != -1 && player2LineX2 > (fishX[minYIndex] + 12))
      aikeystate |= 0x100;
    if (minYIndex == -1) {
      aikeystate |= 0x200;
      if (player2LineY2 > 333)
        aikeystate |= 0x400;
    }
  }
  else if (player2FishOn >= 0) {
    aikeystate |= 0x200;
    if (fishY[player2FishOn] > 333) {
      aikeystate |= 0x400;
      aikeystate |= 0x1000;
    }
    else if ((sharkFacing == 0 && sharkX < 300) || fishY[player2FishOn] < 310) {
      aikeystate |= 0x400;
      aikeystate |= 0x1000;
    }
  }
  if (wesGlowing == 1 && (aikeystateprev & 0x2000) != 0x2000)
    aikeystate |= 0x2000;
  if (aiBurp == 1) {
    aiBurpTimer -= (int) interval & 0x7fffffff;
    if (aiBurpTimer < 0) {
      if (aidifficulty == 0)
        aiBurpTimeout = rand() % 12500 + 12500;
      else if (aidifficulty == 1)
        aiBurpTimeout = rand() % 1500 + 2000;
      aiBurpTimer = (int) aiBurpTimeout & 0x7fffffff;
      aiBurp = 0;
    }
  }
  else {
    aiBurpOffTimer -= (int) interval & 0x7fffffff;
    if (aiBurpOffTimer < 0) {
      aiBurpOffTimer = (int) aiBurpOffTimeout & 0x7fffffff;
      aiBurp = 1;
    }
  }
  if (player2LineY2 > 333) {
    if (aiBurp == 1 && aidifficulty != 2)
      aikeystate = 0;
  }
}
void procnet(void) {
  int index = 0;
  int index2 = 0;
  int result = 0;
  int i = 0;
  static int num = 0;
  static int lastnum = 0;
  if (mode == 3 && sock != NULL) {
    char cnum[4] = { '\0', '\0', '\0', '\0' };
    int numready = 0;
    volatile int volatwhil = 0;
    numready = SDLNet_CheckSockets(set, 0);
    while(numready > 0) {
      if (volatwhil == 0)
        volatwhil = 1;
      if (SDLNet_SocketReady(sock)) {
        result = SDLNet_TCP_Recv(sock, &cnum[index++], 1);
        if (result != 1) {
          badconn = 1;
          /* TODO handle error */
          break;
        }
        badconn = 0;
        if (index == 4) {
          volatile int volat3 = 0;
#pragma GCC diagnostic ignored "-Wsign-conversion"
          num=SDLNet_Read32(cnum);
          if (lastnum == 0x20200000 + index2) {
            hostNetVersion = num;
          }
          ++index2;
          for (i = 0; i < 5; ++i) {
            if (volat3 == 0)
              volat3 = 1;
            if (lastnum == 0x20200000 + index2) {
              fishFacing[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishNibble[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishNibbleTimeout[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishOn[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishPhase[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishSpurtPhase[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) { 
              fishTimeSinceAboutFace[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishX[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishY[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishYBase[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishSalmon[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishGlimmerX[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishGlowing[i] = num;
            }
            ++index2;
            if (lastnum == 0x20200000 + index2) {
              fishGlowAlpha[i] = num;
            }
            ++index2;
          }
          if (lastnum == 0x20200000 + index2) {
            cloudX = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            fishInterval = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            hookSize = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1CaughtCount = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Cast = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer1Rect.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer1Rect.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer1Rect.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer1Rect.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer2Rect.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer2Rect.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer2Rect.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1Glimmer2Rect.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1GlimmerTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1GlimmerXBase = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1GlimmerY = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1GlimmerReady = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1HookSet = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1HookRecoverTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1LineX1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1LineX2 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1LineY1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1LineY2 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1PoleX1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1PoleX2 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1PoleY1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2CaughtCount = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Cast = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer1Rect.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer1Rect.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer1Rect.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer1Rect.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer2Rect.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer2Rect.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer2Rect.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2Glimmer2Rect.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2GlimmerTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2GlimmerXBase = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2GlimmerY = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2GlimmerReady = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2HookSet = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2HookRecoverTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2LineX1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2LineX2 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2LineY1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2LineY2 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2PoleX1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2PoleX2 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2PoleY1 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            radGlowAlpha = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            radGlowing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            wesGlowAlpha = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            wesGlowing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleFrame = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleInterval = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleFrame3 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleInterval3 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleTimeout3 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleFrame4 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleInterval4 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            rippleTimeout4 = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaHorseFacing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaHorseGo = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaHorsePhase = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaHorseX = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaHorseY = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaHorseYBase = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarGo = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarX = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarY = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarBox.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarBox.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarBox.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            seaStarBox.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkBox.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkBox.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkBox.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkBox.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkGlowAlpha = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkGlowing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkLeftBox.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkLeftBox.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkLeftBox.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkLeftBox.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkRightBox.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkRightBox.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkRightBox.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkRightBox.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkSpeed = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkX = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkY = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sharkFacing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieBox.x = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieBox.y = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieBox.w = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieBox.h = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieFacing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieHide = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieHideTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieHideX = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieOffscreenTimeout = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieSpeed = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieGlowAlpha = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieGlowing = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            sloogieX = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            winScore = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player1FishOn = num;
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            player2FishOn = num;
          }
          index = 0;
          index2 = 0;
          lastnum = num;
        }
      }
      else {
        break;
      }
      numready = SDLNet_CheckSockets(set, 0);
    }
    index = 0;
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = clientNetVersion;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = keystate;
    SDLNet_Write32(num, &data[index++ * 4]);
    result = SDLNet_TCP_Send(sock, data, index * 4);
    if (result != (index - 1) * 4) {
      /* TODO error: close socket open it back up */
    }
  }
  else if (mode == 3 && mystrnlen(ipbuf, 256) > 1 && sock == NULL) {
    Uint32 ipfixendian = 0;
    if (set == NULL) {
      set = SDLNet_AllocSocketSet(1);
      if (!set) {
        fprintf(stderr, "Failed to allocate socket set.\r\n");
        exit(1);
      }
    }
    SDLNet_ResolveHost(&serverip, ipbuf, port);
    ipfixendian = SDLNet_Read32(&(serverip.host));
    if ((ipfixendian >= 0x0a000000 && ipfixendian <= 0x0affffff)
      || (ipfixendian >= 0xac100000 && ipfixendian < 0xac200000) /* < intended */
      || (ipfixendian >= 0xc0a80000 && ipfixendian <= 0xc0a8ffff)
      || (ipfixendian >= 0x7f000000 && ipfixendian <= 0x7fffffff)) {
    }
    else {
      fprintf(stderr, "Internet multiplayer is not supported. However LAN multiplayer is supported.\r\n");
      exit(1);
    }
    sock = SDLNet_TCP_Open(&serverip);
    SDLNet_TCP_AddSocket(set, sock);
  }
  else if (mode == 2 && sock2 != NULL) {
    char cnum[4] = { '\0', '\0', '\0', '\0' };
    int numready = SDLNet_CheckSockets(set, 0);
    volatile int volatwhil = 0;
    volatile int volat = 0;
    while(numready > 0) {
      if (volatwhil == 0)
        volatwhil = 1;
      if (SDLNet_SocketReady(sock2)) {
        result = SDLNet_TCP_Recv(sock2, &cnum[index++], 1);
        if (result != 1) {
          badconn = 1;
          /* TODO handle error */
          break;
        }
        badconn = 0;
        if (index == 4) {
          num=SDLNet_Read32(cnum);
          if (lastnum == 0x20200000 + index2) {
            clientNetVersion = num;
#ifdef DEBUG_MODE
              fprintf(stdout, "clientNetVersion num = %d index2 = %d\n", num, index2);
#endif
          }
          ++index2;
          if (lastnum == 0x20200000 + index2) {
            clientkeystateprev = clientkeystate;
            clientkeystate = num;
#ifdef DEBUG_MODE
              fprintf(stdout, "clientkeystate num = %d index2 = %d\n", num, index2);
#endif
          }
          ++index2;
          index = 0;
          index2 = 0;
          lastnum = num;
        }
      }
      else {
        break;
      }
      numready = SDLNet_CheckSockets(set, 0);
    }
    index = 0;
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = hostNetVersion;
    SDLNet_Write32(num, &data[index++ * 4]);
    for (i = 0; i < 5; ++i) {
      if (volat == 0)
        volat = 1;
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishFacing[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishNibble[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishNibbleTimeout[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishOn[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishPhase[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishSpurtPhase[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishTimeSinceAboutFace[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishX[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishY[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishYBase[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishSalmon[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishGlimmerX[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishGlowing[i];
      SDLNet_Write32(num, &data[index++ * 4]);
      num = 0x20200000 + index / 2;
      SDLNet_Write32(num, &data[index++ * 4]);
      num = fishGlowAlpha[i];
      SDLNet_Write32(num, &data[index++ * 4]);
    }
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = cloudX;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = fishInterval;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = hookSize;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1CaughtCount;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Cast;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer1Rect.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer1Rect.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer1Rect.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer1Rect.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer2Rect.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer2Rect.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer2Rect.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1Glimmer2Rect.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1GlimmerTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1GlimmerXBase;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1GlimmerY;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1GlimmerReady;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1HookSet;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1HookRecoverTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1LineX1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1LineX2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1LineY1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1LineY2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1PoleX1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1PoleX2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1PoleY1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2CaughtCount;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Cast;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer1Rect.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer1Rect.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer1Rect.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer1Rect.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer2Rect.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer2Rect.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer2Rect.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2Glimmer2Rect.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2GlimmerTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2GlimmerXBase;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2GlimmerY;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2GlimmerReady;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2HookSet;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2HookRecoverTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2LineX1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2LineX2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2LineY1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2LineY2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2PoleX1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2PoleX2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2PoleY1;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = radGlowAlpha;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = radGlowing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = wesGlowAlpha;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = wesGlowing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleFrame;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleInterval;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleFrame3;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleInterval3;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleTimeout3;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleFrame4;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleInterval4;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = rippleTimeout4;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaHorseFacing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaHorseGo;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaHorsePhase;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaHorseX;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaHorseY;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaHorseYBase;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarGo;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarX;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarY;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarBox.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarBox.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarBox.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = seaStarBox.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkBox.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkBox.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkBox.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkBox.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkGlowAlpha;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkGlowing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkLeftBox.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkLeftBox.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkLeftBox.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkLeftBox.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkRightBox.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkRightBox.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkRightBox.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkRightBox.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkSpeed;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkX;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkY;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sharkFacing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieBox.x;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieBox.y;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieBox.w;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieBox.h;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieFacing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieHide;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieHideTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieHideX;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieOffscreenTimeout;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieSpeed;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieGlowAlpha;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieGlowing;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = sloogieX;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = winScore;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player1FishOn;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = 0x20200000 + index / 2;
    SDLNet_Write32(num, &data[index++ * 4]);
    num = player2FishOn;
    SDLNet_Write32(num, &data[index++ * 4]);
    result = SDLNet_TCP_Send(sock2, data, index * 4);
#pragma GCC diagnostic warning "-Wsign-conversion"
    if (result != (index - 1) * 4) {
      /* TODO error: close socket open it back up */
    }
  }
  else if (mode == 2 && sock2 == NULL) {
    sock2 = SDLNet_TCP_Accept(sock);
    if (sock2 != NULL)
      load2();
    SDLNet_TCP_AddSocket(set, sock2);
  }
  if ((mode == 2 || mode == 3) && clientNetVersion != hostNetVersion) {
    fprintf(stderr, "Client/host network protocol version mismatch.\r\n");
    exit(1);
  }
}
void procseaweed(int i) {
  seaweedOffset[i] += seaweedOffsetDirection[i];
  if (seaweedOffset[i] < -2 || seaweedOffset[i] > 2)
    seaweedOffsetDirection[i] *= -1;
}
void render(void) {
  SDL_Rect fishSrcRect = { 0, 0, 0, 0};
  SDL_Rect fishDstRect = { 0, 0, 0, 0};
  SDL_Rect bgfgDstRect = { 0, 0, 0, 0};
  SDL_Rect player1PoleDstRect = { 0, 0, 0, 0};
  SDL_Rect hookSrcRect = { 0, 0, 0, 0};
  SDL_Rect hookDstRect = { 0, 0, 0, 0};
  SDL_Rect rippleDstRect = { 0, 0, 0, 0};
  SDL_Rect player2PoleDstRect = { 0, 0, 0, 0};
  SDL_Rect hookSrcRect2 = { 0, 0, 0, 0};
  SDL_Rect hookDstRect2 = { 0, 0, 0, 0};
  SDL_Rect rippleDstRect2 = { 0, 0, 0, 0};
  SDL_Rect rippleDstRect3 = { 0, 0, 0, 0};
  SDL_Rect rippleDstRect4 = { 0, 0, 0, 0};
  SDL_Rect seaHorseDstRect = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect1 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect2 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect3 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect4 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect5 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect6 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect7 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect8 = { 0, 0, 0, 0};
  SDL_Rect seaweed1DstRect9 = { 0, 0, 0, 0};
  SDL_Rect seaStarDstRect = { 0, 0, 0, 0};
  SDL_Rect sharkDstRect = { 0, 0, 0, 0};
  SDL_Rect sharkSrcRect = { 0, 0, 0, 0};
  SDL_Rect sharkFinDstRect = { 0, 0, 0, 0};
  SDL_Rect sloogieDstRect = { 0, 0, 0, 0};
  SDL_Rect sloogieHideDstRect = { 0, 0, 0, 0};
  SDL_Rect pointFishDstRect = { 0, 0, 0, 0};
  float a = player1LineY2 - player1LineY1;
  float b = 0.0f;
  float player1LineSeg1X = 0.0f;
  float player1LineSeg2X = 0.0f;
  float c = player2LineY2 - player2LineY1;
  float d = 0.0f;
  float player2LineSeg1X = 0.0f;
  float player2LineSeg2X = 0.0f;
  int i = 0;
  volatile int volat = 0;
  volatile int volat2 = 0;
  if (a > -1.1 && a < 0.1) a = -1.1;
  if (a < 1.1 && a > -0.1) a = 1.1;
  player1LineSeg1X = (245.0 - player1LineY1) / a * (player1LineX2 - player1LineX1) + player1LineX1;
  b = player1LineY1 - 245.0; 
  if (b > -1.1 && b < 0.1) b = -1.1;
  if (b < 1.1 && b > -0.1) b = 1.1;
  player1LineSeg2X = (267.0 - 245.0) / b * (player1LineX1 - player1LineSeg1X) + player1LineSeg1X;
  if (c > -1.1 && c < 0.1) c = -1.1;
  if (c < 1.1 && c > -0.1) c = 1.1;
  player2LineSeg1X = (245.0 - player2LineY1) / c * (player2LineX2 - player2LineX1) + player2LineX1;
  d = player2LineY1 - 245.0; 
  if (d > -1.1 && d < 0.1) d = -1.1;
  if (d < 1.1 && d > -0.1) d = 1.1;
  player2LineSeg2X = (267.0 - 245.0) / d * (player2LineX1 - player2LineSeg1X) + player2LineSeg1X;
  SDL_SetRenderTarget(renderer, offscreenBuffer[1]);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  fishSrcRect.x = 0;
  fishSrcRect.y = 0;
  fishSrcRect.w = 71;
  fishSrcRect.h = 26;
  fishDstRect.w = 71;
  fishDstRect.h = 26;
  bgfgDstRect.x = 0;
  bgfgDstRect.y = 0;
  bgfgDstRect.w = 800;
  bgfgDstRect.h = 600;
  rippleDstRect.x = player1LineSeg1X - 9;
  rippleDstRect.y = 234;
  rippleDstRect.w = 20;
  rippleDstRect.h = 20;
  rippleDstRect2.x = player2LineSeg1X - 9;
  rippleDstRect2.y = 234;
  rippleDstRect2.w = 20;
  rippleDstRect2.h = 20;
  rippleDstRect3.x = 114;
  rippleDstRect3.y = 249;
  rippleDstRect3.w = 26;
  rippleDstRect3.h = 8;
  rippleDstRect4.x = 660;
  rippleDstRect4.y = 250;
  rippleDstRect4.w = 26;
  rippleDstRect4.h = 8;
  if (player1GlimmerTimeout > -125 && player1Glimmer1Rect.y > 267) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1Glimmer1Rect);
    SDL_RenderDrawRect(renderer, &player1Glimmer2Rect);
  }
  if (player1FishOn == -1 || (player1FishOn >= 0 && fishY[player1FishOn] > 245)) {
    if (rippleFrame == 0)
      SDL_RenderCopy(renderer, rippleTexture1, NULL, &rippleDstRect);
    if (rippleFrame == 1)
      SDL_RenderCopy(renderer, rippleTexture2, NULL, &rippleDstRect);
    if (rippleFrame == 2)
      SDL_RenderCopy(renderer, rippleTexture3, NULL, &rippleDstRect);
  }
  if (player2GlimmerTimeout > -125 && player2Glimmer1Rect.y > 267) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player2Glimmer1Rect);
    SDL_RenderDrawRect(renderer, &player2Glimmer2Rect);
  }
  if (mode != 0 && (player2FishOn == -1 || (player2FishOn >= 0 && fishY[player2FishOn] > 245))) {
    if (rippleFrame2 == 0)
      SDL_RenderCopy(renderer, rippleTexture1, NULL, &rippleDstRect2);
    if (rippleFrame2 == 1)
      SDL_RenderCopy(renderer, rippleTexture2, NULL, &rippleDstRect2);
    if (rippleFrame2 == 2)
      SDL_RenderCopy(renderer, rippleTexture3, NULL, &rippleDstRect2);
  }
  if (rippleFrame3 == 0)
    SDL_RenderCopy(renderer, rippleTexture4, NULL, &rippleDstRect3);
  if (rippleFrame3 == 1)
    SDL_RenderCopy(renderer, rippleTexture5, NULL, &rippleDstRect3);
  if (rippleFrame3 == 2)
    SDL_RenderCopy(renderer, rippleTexture6, NULL, &rippleDstRect3);
  if (rippleFrame4 == 0 && mode != 0)
    SDL_RenderCopy(renderer, rippleTexture4, NULL, &rippleDstRect4);
  if (rippleFrame4 == 1 && mode != 0)
    SDL_RenderCopy(renderer, rippleTexture5, NULL, &rippleDstRect4);
  if (rippleFrame4 == 2 && mode != 0)
    SDL_RenderCopy(renderer, rippleTexture6, NULL, &rippleDstRect4);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  if (player1FishOn > -1 && fishY[player1FishOn] <= 245) {
    float e = (player1LineY2 - player1LineY1);
    if (e > -1.1 && e < -0.1) e = -1.1;
    if (e < 1.1 && e > 0.1) e = 1.1;
    player1LineSeg1X = (fishY[player1FishOn] - player1LineY1) / e * (player1LineX2 - player1LineX1) + player1LineX1;
    SDL_RenderDrawLine(renderer, player1LineX1, player1LineY1, player1LineSeg1X, fishY[player1FishOn]);
  }
  else
    SDL_RenderDrawLine(renderer, player1LineX1, player1LineY1, player1LineSeg1X, 245);
  if (player1LineY2 > 267)
    SDL_RenderDrawLine(renderer, player1LineSeg2X, 267, player1LineX2, player1LineY2 > 267 ? player1LineY2 : 267);
  if (mode != 0 && player2FishOn > -1 && fishY[player2FishOn] <= 245) {
    float e = (player2LineY2 - player2LineY1);
    if (e > -1.1 && e < -0.1) e = -1.1;
    if (e < 1.1 && e > 0.1) e = 1.1;
    player2LineSeg1X = (fishY[player2FishOn] - player2LineY1) / e * (player2LineX2 - player2LineX1) + player2LineX1;
    SDL_RenderDrawLine(renderer, player2LineX1, player2LineY1, player2LineSeg1X, fishY[player2FishOn]);
  }
  else if (mode != 0)
    SDL_RenderDrawLine(renderer, player2LineX1, player2LineY1, player2LineSeg1X, 245);
  if (mode != 0 && player2LineY2 > 267)
    SDL_RenderDrawLine(renderer, player2LineSeg2X, 267, player2LineX2, player2LineY2 > 267 ? player2LineY2 : 267);
  if (player1FishOn == -1) {
    hookDstRect.x = player1LineX2 - 6;
    hookDstRect.y = player1LineY2 - 7;
    hookSrcRect.x = 0; 
    hookSrcRect.y = hookDstRect.y < 270 ? 270 - hookDstRect.y : 0;
    if (hookSrcRect.y > 10)
      hookSrcRect.y = 10;
    hookSrcRect.w = 8;
    hookSrcRect.h = 10 - hookSrcRect.y;
    hookDstRect.w = 8;
    hookDstRect.h = hookSrcRect.h;
    hookDstRect.y = player1LineY2 - 7.0 * ((float) hookSrcRect.h) / 15.0;
    SDL_RenderCopy(renderer, hookTexture, &hookSrcRect, &hookDstRect);
  }
  if (mode != 0 && player2FishOn == -1) {
    hookDstRect2.x = player2LineX2 - 6;
    hookDstRect2.y = player2LineY2 - 7;
    hookSrcRect2.x = 0; 
    hookSrcRect2.y = hookDstRect2.y < 270 ? 270 - hookDstRect2.y : 0;
    if (hookSrcRect2.y > 10)
      hookSrcRect2.y = 10;
    hookSrcRect2.w = 8;
    hookSrcRect2.h = 10 - hookSrcRect2.y;
    hookDstRect2.w = 8;
    hookDstRect2.h = hookSrcRect2.h;
    hookDstRect2.y = player2LineY2 - 7.0 * ((float) hookSrcRect2.h) / 15.0;
    SDL_RenderCopy(renderer, hookTexture, &hookSrcRect2, &hookDstRect2);
  }
  for (i = 0; i < 5; ++i) {
    if (volat == 0)
      volat = 1;
    if (i == 4) {
  seaweed1DstRect1.x = 149 + seaweedOffset[0];
  seaweed1DstRect1.y = 456;
  seaweed1DstRect1.w = 22;
  seaweed1DstRect1.h = 48;
  seaweed1DstRect2.x = 438 + seaweedOffset[1];
  seaweed1DstRect2.y = 460;
  seaweed1DstRect2.w = 22;
  seaweed1DstRect2.h = 48;
  seaweed1DstRect3.x = 507 + seaweedOffset[2];
  seaweed1DstRect3.y = 451;
  seaweed1DstRect3.w = 22;
  seaweed1DstRect3.h = 48;
  seaweed1DstRect4.x = 592 + seaweedOffset[3];
  seaweed1DstRect4.y = 455;
  seaweed1DstRect4.w = 22;
  seaweed1DstRect4.h = 48;
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect1);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect2);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect3);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect4);
  seaweed1DstRect1.x -= seaweedOffset[0];
  seaweed1DstRect2.x -= seaweedOffset[1];
  seaweed1DstRect3.x -= seaweedOffset[2];
  seaweed1DstRect4.x -= seaweedOffset[3];
  seaweed1DstRect1.y += 48;
  seaweed1DstRect2.y += 48;
  seaweed1DstRect3.y += 48;
  seaweed1DstRect4.y += 48;
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect1);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect2);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect3);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect4);
    }
    fishDstRect.x = fishX[i];
    fishDstRect.y = fishY[i];
    fishSrcRect.y = fishDstRect.y < 269 ? 269 - fishDstRect.y : 0;
    if (fishSrcRect.y > 26)
      fishSrcRect.y = 26;
    fishSrcRect.h = 26 - fishSrcRect.y;
    fishDstRect.h = 26 - fishSrcRect.y;
    if (fishY[i] < 247) {
      fishSrcRect.y = 0;
      fishSrcRect.h = 247 - fishY[i];
      fishDstRect.h = 247 - fishY[i];
      if (fishSrcRect.h > 26)
        fishSrcRect.h = 26;
      if (fishDstRect.h > 26)
        fishDstRect.h = 26;
    }
    else
      fishDstRect.y += fishSrcRect.y; 
    if (fishFacing[i] == 0) {
      if (fishSalmon[i] == 0)
        SDL_RenderCopy(renderer, fishTexture, &fishSrcRect, &fishDstRect);
      else
        SDL_RenderCopy(renderer, salmonTexture, &fishSrcRect, &fishDstRect);
      if (fishGlowing[i] == 1) {
        SDL_SetTextureAlphaMod(fishGlowTexture, fishGlowAlpha[i]);
        SDL_RenderCopy(renderer, fishGlowTexture, NULL, &fishDstRect);
      }
    }
    else {
      if (fishSalmon[i] == 0)
        SDL_RenderCopy(renderer, fishFlipTexture, &fishSrcRect, &fishDstRect);
      else
        SDL_RenderCopy(renderer, salmonFlipTexture, &fishSrcRect, &fishDstRect);
      if (fishGlowing[i] == 1) {
        SDL_SetTextureAlphaMod(fishGlowFlipTexture, fishGlowAlpha[i]);
        SDL_RenderCopy(renderer, fishGlowFlipTexture, NULL, &fishDstRect);
      }
    }
  }
  seaHorseDstRect.x = seaHorseX;
  seaHorseDstRect.y = seaHorseY;
  seaHorseDstRect.w = 40;
  seaHorseDstRect.h = 89;
  if (seaHorseFacing == 0)
    SDL_RenderCopy(renderer, seaHorseTexture, NULL, &seaHorseDstRect);
  else
    SDL_RenderCopy(renderer, seaHorseFlipTexture, NULL, &seaHorseDstRect);
  seaStarDstRect.x = seaStarX;
  seaStarDstRect.y = seaStarY;
  seaStarDstRect.w = 32;
  seaStarDstRect.h = 32;
  SDL_RenderCopy(renderer, seaStarTexture, NULL, &seaStarDstRect);
  sharkSrcRect.x = 0;
  sharkSrcRect.y = 28;
  sharkSrcRect.w = 175;
  sharkSrcRect.h = 52;
  sharkDstRect.x = sharkX;
  sharkDstRect.y = sharkY + 28;
  sharkDstRect.w = 175;
  sharkDstRect.h = 52;
  sharkFinDstRect.x = sharkX + (sharkFacing == 0 ? 71 : 89);
  sharkFinDstRect.y = 237;
  sharkFinDstRect.w = 13;
  sharkFinDstRect.h = 10;
  if (mode != 0 && sharkFacing == 0) {
    SDL_RenderCopy(renderer, sharkTexture, &sharkSrcRect, &sharkDstRect);
    SDL_RenderCopy(renderer, sharkFinTexture, NULL, &sharkFinDstRect);
    SDL_SetTextureAlphaMod(sharkGlowTexture, sharkGlowAlpha);
    SDL_RenderCopy(renderer, sharkGlowTexture, &sharkSrcRect, &sharkDstRect);
    SDL_SetTextureAlphaMod(sharkFinGlowTexture, sharkGlowAlpha);
    SDL_RenderCopy(renderer, sharkFinGlowTexture, NULL, &sharkFinDstRect);
  }
  else if (mode != 0) {
    SDL_RenderCopy(renderer, sharkFlipTexture, &sharkSrcRect, &sharkDstRect);
    SDL_RenderCopy(renderer, sharkFinFlipTexture, NULL, &sharkFinDstRect);
    SDL_SetTextureAlphaMod(sharkGlowFlipTexture, sharkGlowAlpha);
    SDL_RenderCopy(renderer, sharkGlowFlipTexture, &sharkSrcRect, &sharkDstRect);
    SDL_SetTextureAlphaMod(sharkFinGlowFlipTexture, sharkGlowAlpha);
    SDL_RenderCopy(renderer, sharkFinGlowFlipTexture, NULL, &sharkFinDstRect);
  }
  sloogieDstRect.x = sloogieX;
  sloogieDstRect.y = 491;
  sloogieDstRect.w = 177;
  sloogieDstRect.h = 77;
  sloogieHideDstRect.x = sloogieX +(sloogieFacing == 0 ? 82 : 15);
  sloogieHideDstRect.y = 513;
  sloogieHideDstRect.w = 80;
  sloogieHideDstRect.h = 57;
  if (sloogieFacing == 0 && sloogieHide == 0) {
    SDL_RenderCopy(renderer, sloogieTexture, NULL, &sloogieDstRect);
    SDL_SetTextureAlphaMod(sloogieGlowTexture, sloogieGlowAlpha);
    SDL_RenderCopy(renderer, sloogieGlowTexture, NULL, &sloogieDstRect);
  }
  else if (sloogieFacing != 0 && sloogieHide == 0) {
    SDL_RenderCopy(renderer, sloogieFlipTexture, NULL, &sloogieDstRect);
    SDL_SetTextureAlphaMod(sloogieGlowFlipTexture, sloogieGlowAlpha);
    SDL_RenderCopy(renderer, sloogieGlowFlipTexture, NULL, &sloogieDstRect);
  }
  if (sloogieFacing == 0 && sloogieHide != 0) {
    SDL_RenderCopy(renderer, sloogieHideTexture, NULL, &sloogieHideDstRect);
    SDL_SetTextureAlphaMod(sloogieHideGlowTexture, sloogieGlowAlpha);
    SDL_RenderCopy(renderer, sloogieHideGlowTexture, NULL, &sloogieHideDstRect);
  }
  else if (sloogieFacing != 0 && sloogieHide != 0) {
    SDL_RenderCopy(renderer, sloogieHideFlipTexture, NULL, &sloogieHideDstRect);
    SDL_SetTextureAlphaMod(sloogieHideGlowFlipTexture, sloogieGlowAlpha);
    SDL_RenderCopy(renderer, sloogieHideGlowFlipTexture, NULL, &sloogieHideDstRect);
  }
  seaweed1DstRect5.x = 187 + seaweedOffset[4];
  seaweed1DstRect5.y = 488;
  seaweed1DstRect5.w = 22;
  seaweed1DstRect5.h = 48;
  seaweed1DstRect6.x = 347 + seaweedOffset[5];
  seaweed1DstRect6.y = 475;
  seaweed1DstRect6.w = 22;
  seaweed1DstRect6.h = 48;
  seaweed1DstRect7.x = 482 + seaweedOffset[6];
  seaweed1DstRect7.y = 480;
  seaweed1DstRect7.w = 22;
  seaweed1DstRect7.h = 48;
  seaweed1DstRect8.x = 660 + seaweedOffset[7];
  seaweed1DstRect8.y = 485;
  seaweed1DstRect8.w = 22;
  seaweed1DstRect8.h = 48;
  seaweed1DstRect9.x = 287 + seaweedOffset[8];
  seaweed1DstRect9.y = 491;
  seaweed1DstRect9.w = 22;
  seaweed1DstRect9.h = 48;
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect5);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect6);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect7);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect8);
  SDL_RenderCopy(renderer, seaweed1TopTexture, NULL, &seaweed1DstRect9);
  seaweed1DstRect5.x -= seaweedOffset[4];
  seaweed1DstRect6.x -= seaweedOffset[5];
  seaweed1DstRect7.x -= seaweedOffset[6];
  seaweed1DstRect8.x -= seaweedOffset[7];
  seaweed1DstRect9.x -= seaweedOffset[8];
  seaweed1DstRect5.y += 48;
  seaweed1DstRect6.y += 48;
  seaweed1DstRect7.y += 48;
  seaweed1DstRect8.y += 48;
  seaweed1DstRect9.y += 48;
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect5);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect6);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect7);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect8);
  SDL_RenderCopy(renderer, seaweed1BottomTexture, NULL, &seaweed1DstRect9);
  cloudSrcRect.x = cloudX;
  cloudSrcRect.y = 0;
  cloudSrcRect.w = 800 - (cloudX <= 800 ? 0 : cloudX - 800);
  cloudSrcRect.h = 200;
  cloudDstRect.x = 0;
  cloudDstRect.y = 0;
  cloudDstRect.w = cloudSrcRect.w;
  cloudDstRect.h = 200;
  cloudSrcRect2.x = cloudSrcRect.x + cloudSrcRect.w + 1;
  if (cloudSrcRect2.x >= 1600)
    cloudSrcRect2.x -= 1600;
  cloudSrcRect2.y = 0;
  cloudSrcRect2.w = 800 - (cloudSrcRect2.x <= 800 ? 0 : cloudSrcRect2.x - 800);
  cloudSrcRect2.h = 200;
  cloudDstRect2.x = cloudDstRect.x + cloudDstRect.w;
  cloudDstRect2.y = 0;
  cloudDstRect2.w = cloudSrcRect2.w;
  cloudDstRect2.h = 200;
  SDL_RenderCopy(renderer, cloudTexture, &cloudSrcRect, &cloudDstRect);
  SDL_RenderCopy(renderer, cloudTexture, &cloudSrcRect2, &cloudDstRect2);
  pointFishDstRect.w = 9;
  pointFishDstRect.h = 23;
  if (mode != 0) {
    volatile int volat3 = 0;
    volatile int volat4 = 0;
    for (i = 0; i < player1CaughtCount && i < 48; ++i) {
      if (volat3 == 0)
        volat3 = 1;
      pointFishDstRect.x = 5 + (i % 12 * 14);
      pointFishDstRect.y = 5 + (i / 12 * 28);
      SDL_RenderCopy(renderer, pointFishTexture, NULL, &pointFishDstRect);
    }
    for (i = 0; i < player2CaughtCount && i < 48; ++i) {
      if (volat4 == 0)
        volat4 = 1;
      pointFishDstRect.x = 800 - 14 - (i % 12 * 14);
      pointFishDstRect.y = 5 + (i / 12 * 28);
      SDL_RenderCopy(renderer, pointFishTexture, NULL, &pointFishDstRect);
    }
  }
  player1PoleDstRect.x = player1PoleX1;
  player1PoleDstRect.y = player1PoleY1;
  player1PoleDstRect.w = player1PoleX2 - player1PoleX1;
  if (player1FishOn == -1 && player1HookRecoverTimeout < 1.0) {
    player1PoleDstRect.h = 54;
    player1PoleDstRect.w -= 1 + ((float) player1PoleX2 - (float) player1PoleX1) / 77.0;
    SDL_RenderCopy(renderer, player1PoleNoFishTexture, NULL, &player1PoleDstRect);
  }
  else {
    player1PoleDstRect.h = 54;
    player1PoleDstRect.w += ((float) player1PoleX2 - (float) player1PoleX1) / 17.0;
    SDL_RenderCopy(renderer, player1PoleFishTexture, NULL, &player1PoleDstRect);
  }
  player2PoleDstRect.x = player2PoleX1;
  player2PoleDstRect.y = player2PoleY1;
  player2PoleDstRect.w = player2PoleX2 - player2PoleX1;
  if (mode != 0 && player2FishOn == -1 && player2HookRecoverTimeout < 1.0) {
    player2PoleDstRect.h = 54;
    player2PoleDstRect.x += 1 + ((float) player2PoleX2 - (float) player2PoleX1) / 77.0;
    SDL_RenderCopy(renderer, player2PoleNoFishTexture, NULL, &player2PoleDstRect);
  }
  else if (mode != 0) {
    player2PoleDstRect.h = 54;
    player2PoleDstRect.x += ((float) player2PoleX1 - (float) player2PoleX2) / 17.0;
    player2PoleDstRect.w -= ((float) player2PoleX1 - (float) player2PoleX2) / 17.0;
    SDL_RenderCopy(renderer, player2PoleFishTexture, NULL, &player2PoleDstRect);
  }
  SDL_SetRenderTarget(renderer, offscreenBuffer[2]);
  SDL_RenderCopy(renderer, radTexture, &radSrcRect, &radDstRect);
  if (radGlowing == 1) {
    SDL_SetTextureAlphaMod(radGlowTexture, radGlowAlpha);
    SDL_RenderCopy(renderer, radGlowTexture, &radSrcRect, &radDstRect);
  }
  if (mode != 0)
    SDL_RenderCopy(renderer, wesTexture, &wesSrcRect, &wesDstRect);
  if (mode != 0 && wesGlowing == 1) {
    SDL_SetTextureAlphaMod(wesGlowTexture, wesGlowAlpha);
    SDL_RenderCopy(renderer, wesGlowTexture, &wesSrcRect, &wesDstRect);
  }
  SDL_SetRenderTarget(renderer, offscreenBuffer[3]);
  for (i = 0; i < 3; ++i) {
    if (volat2 == 0)
      volat2 = 1;
    SDL_RenderCopy(renderer, offscreenBuffer[i], NULL, &bgfgDstRect);
  }
  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, offscreenBuffer[3], NULL, &bgfgDstRect);
  if (mode != 0 && player1CaughtCount >= winScore) {
    SDL_Rect tmpRect = { 0, 0, 0, 0};
    SDL_SetRenderTarget(renderer, NULL);
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = 800;
    tmpRect.h = 600;
    SDL_RenderCopy(renderer, bgTexture, NULL, &tmpRect);
    SDL_RenderCopy(renderer, fgTexture, NULL, &tmpRect);
    tmpRect.w = 26;
    tmpRect.h = 71;
    tmpRect.x = 387;
    tmpRect.y = 37;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
  }
  else if (mode != 0 && player2CaughtCount >= winScore) {
    SDL_Rect tmpRect = { 0, 0, 0, 0};
    SDL_SetRenderTarget(renderer, NULL);
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = 800;
    tmpRect.h = 600;
    SDL_RenderCopy(renderer, bgTexture, NULL, &tmpRect);
    SDL_RenderCopy(renderer, fgTexture, NULL, &tmpRect);
    tmpRect.w = 26;
    tmpRect.h = 71;
    tmpRect.x = 491;
    tmpRect.y = 37;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.x = 283;
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.y += 71;
    SDL_RenderCopy(renderer, pointFishTexture, NULL, &tmpRect);
    tmpRect.w = 71;
    tmpRect.h = 26;
    tmpRect.x = 283;
    tmpRect.y = 37;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x += 71;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x += 71;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x = 283;
    tmpRect.y = 250;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x += 71;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x += 71;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x = 283;
    tmpRect.y = 463;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x += 71;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
    tmpRect.x += 71;
    SDL_RenderCopy(renderer, fishTexture, NULL, &tmpRect);
  }
#ifdef DEBUG_MODE
  if (sharkFacing == 0)
    renderBoolmap(sharkOutlineMap, 175, 14000, sharkX, sharkY);
  else
    renderBoolmap(sharkFlipOutlineMap, 175, 14000, sharkX, sharkY);
  if (player1FishOn > -1 && fishFacing[player1FishOn] == 0)
    renderBoolmap(fishOutlineMap, 71, 1846, fishX[player1FishOn], fishY[player1FishOn]);
  else if (player1FishOn > -1 && fishFacing[player1FishOn] == 1)
    renderBoolmap(fishFlipOutlineMap, 71, 1846, fishX[player1FishOn], fishY[player1FishOn]);
  g = 0;
#endif /* DEBUG_MODE */
}
void renderBoolmap(int boolmap[], int xpmWidth, int boolmapwidth, int x, int y) {
  SDL_Rect r = { 0, 0, 0, 0};
  int i = 0;
  volatile int volat = 0;
  r.w = r.h = 2;
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 255, g, 255, 25);
  for (i = 0; i < boolmapwidth; ++i) {
    if (volat == 0)
      volat = 1;
    if (boolmap[i] == 1) {
      r.x = x + i % xpmWidth;
      r.y = y + i / xpmWidth;
      SDL_RenderDrawRect(renderer, &r);
    }
  }
}
void update(Uint32 interval) {
  int i = 0;
  volatile int volat = 0;
#ifdef DEBUG_MODE
  static int slow = 0;
  if (mode != 3 && (slow++ % 24 == 0 || (keystate & 0x4000) != 0x4000)) {
#endif /* DEBUG_MODE */
    proc(interval);
#ifdef DEBUG_MODE
  }
#endif /* DEBUG_MODE */
  if (mode == 1)
    procai(interval);
  netTimer -= (int) interval & 0x7fffffff;
  if (netTimer < 0) {
    netTimer = (int) netTimeout & 0x7fffffff;
    procnet();
  }
  for (i = 0; i < 9; ++i) {
    if (volat == 0)
      volat = 1;
    seaweedOffsetTimer[i] -= (int) interval & 0x7fffffff;
    if (seaweedOffsetTimer[i] < 0) {
      seaweedOffsetTimer[i] = (int) seaweedOffsetTimeout[i] & 0x7fffffff;
      procseaweed(i);
    }
  }
  renderTimer -= (int) interval & 0x7fffffff;
  if (renderTimer < 0) {
    renderTimer = (int) renderTimeout & 0x7fffffff;
    render();
    SDL_RenderPresent(renderer);
    curFrames++;
  }
  keystateprev = keystate;
  metrics(interval);
  /*controllerstateprev = controllerstate;*/
}
int wrapNumber(int n, int low, int high) {
  int rangeLength = high - low;
  if(rangeLength==0)
      return high;
  return (n-low<0)?high-(-(n-low)%rangeLength):
      (n-low)%rangeLength+low;
}
