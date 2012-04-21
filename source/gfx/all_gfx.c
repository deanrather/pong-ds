//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .c, for easier inclusion in a project

#ifdef __cplusplus
extern "C" {
#endif

#include "all_gfx.h"


// Sprite files : 
#include "ball.c"
#include "paddle_a.c"
#include "paddle_b.c"

// Background files : 
#include "splash_pong.c"
#include "background_bottom.c"
#include "background_top.c"
#include "splash_comp2.c"
#include "splash_comp.c"
#include "splash_eclipse.c"
#include "splash_palib.c"

// Palette files : 
#include "ball.pal.c"
#include "paddle_a.pal.c"
#include "paddle_b.pal.c"
#include "splash_pong.pal.c"
#include "background_bottom.pal.c"
#include "background_top.pal.c"
#include "splash_comp2.pal.c"
#include "splash_comp.pal.c"
#include "splash_eclipse.pal.c"
#include "splash_palib.pal.c"

// Background Pointers :
PAGfx_struct splash_pong = {(void*)splash_pong_Map, 768, (void*)splash_pong_Tiles, 7744, (void*)splash_pong_Pal, (int*)splash_pong_Info };
PAGfx_struct background_bottom = {(void*)background_bottom_Map, 768, (void*)background_bottom_Tiles, 49152, (void*)background_bottom_Pal, (int*)background_bottom_Info };
PAGfx_struct background_top = {(void*)background_top_Map, 768, (void*)background_top_Tiles, 49152, (void*)background_top_Pal, (int*)background_top_Info };
PAGfx_struct splash_comp2 = {(void*)splash_comp2_Map, 768, (void*)splash_comp2_Tiles, 47936, (void*)splash_comp2_Pal, (int*)splash_comp2_Info };
PAGfx_struct splash_comp = {(void*)splash_comp_Map, 768, (void*)splash_comp_Tiles, 45504, (void*)splash_comp_Pal, (int*)splash_comp_Info };
PAGfx_struct splash_eclipse = {(void*)splash_eclipse_Map, 768, (void*)splash_eclipse_Tiles, 48000, (void*)splash_eclipse_Pal, (int*)splash_eclipse_Info };
PAGfx_struct splash_palib = {(void*)splash_palib_Map, 768, (void*)splash_palib_Tiles, 19776, (void*)splash_palib_Pal, (int*)splash_palib_Info };


#ifdef __cplusplus
}
#endif

