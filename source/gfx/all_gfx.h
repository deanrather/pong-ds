//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char ball_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : ball_Pal
extern const unsigned char paddle_a_Sprite[512] __attribute__ ((aligned (4))) ;  // Pal : paddle_a_Pal
extern const unsigned char paddle_b_Sprite[512] __attribute__ ((aligned (4))) ;  // Pal : paddle_b_Pal

// Background files : 
extern const int splash_pong_Info[3]; // BgMode, Width, Height
extern const unsigned short splash_pong_Map[768] __attribute__ ((aligned (4))) ;  // Pal : splash_pong_Pal
extern const unsigned char splash_pong_Tiles[7744] __attribute__ ((aligned (4))) ;  // Pal : splash_pong_Pal
extern PAGfx_struct splash_pong; // background pointer

extern const int background_bottom_Info[3]; // BgMode, Width, Height
extern const unsigned short background_bottom_Map[768] __attribute__ ((aligned (4))) ;  // Pal : background_bottom_Pal
extern const unsigned char background_bottom_Tiles[49152] __attribute__ ((aligned (4))) ;  // Pal : background_bottom_Pal
extern PAGfx_struct background_bottom; // background pointer

extern const int background_top_Info[3]; // BgMode, Width, Height
extern const unsigned short background_top_Map[768] __attribute__ ((aligned (4))) ;  // Pal : background_top_Pal
extern const unsigned char background_top_Tiles[49152] __attribute__ ((aligned (4))) ;  // Pal : background_top_Pal
extern PAGfx_struct background_top; // background pointer

extern const int splash_comp2_Info[3]; // BgMode, Width, Height
extern const unsigned short splash_comp2_Map[768] __attribute__ ((aligned (4))) ;  // Pal : splash_comp2_Pal
extern const unsigned char splash_comp2_Tiles[47936] __attribute__ ((aligned (4))) ;  // Pal : splash_comp2_Pal
extern PAGfx_struct splash_comp2; // background pointer

extern const int splash_comp_Info[3]; // BgMode, Width, Height
extern const unsigned short splash_comp_Map[768] __attribute__ ((aligned (4))) ;  // Pal : splash_comp_Pal
extern const unsigned char splash_comp_Tiles[45504] __attribute__ ((aligned (4))) ;  // Pal : splash_comp_Pal
extern PAGfx_struct splash_comp; // background pointer

extern const int splash_eclipse_Info[3]; // BgMode, Width, Height
extern const unsigned short splash_eclipse_Map[768] __attribute__ ((aligned (4))) ;  // Pal : splash_eclipse_Pal
extern const unsigned char splash_eclipse_Tiles[48000] __attribute__ ((aligned (4))) ;  // Pal : splash_eclipse_Pal
extern PAGfx_struct splash_eclipse; // background pointer

extern const int splash_palib_Info[3]; // BgMode, Width, Height
extern const unsigned short splash_palib_Map[768] __attribute__ ((aligned (4))) ;  // Pal : splash_palib_Pal
extern const unsigned char splash_palib_Tiles[19776] __attribute__ ((aligned (4))) ;  // Pal : splash_palib_Pal
extern PAGfx_struct splash_palib; // background pointer


// Palette files : 
extern const unsigned short ball_Pal[33] __attribute__ ((aligned (4))) ;
extern const unsigned short paddle_a_Pal[11] __attribute__ ((aligned (4))) ;
extern const unsigned short paddle_b_Pal[11] __attribute__ ((aligned (4))) ;
extern const unsigned short splash_pong_Pal[20] __attribute__ ((aligned (4))) ;
extern const unsigned short background_bottom_Pal[141] __attribute__ ((aligned (4))) ;
extern const unsigned short background_top_Pal[141] __attribute__ ((aligned (4))) ;
extern const unsigned short splash_comp2_Pal[256] __attribute__ ((aligned (4))) ;
extern const unsigned short splash_comp_Pal[223] __attribute__ ((aligned (4))) ;
extern const unsigned short splash_eclipse_Pal[219] __attribute__ ((aligned (4))) ;
extern const unsigned short splash_palib_Pal[190] __attribute__ ((aligned (4))) ;


#endif

