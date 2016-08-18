#include <pebble.h>


// pointer to main window
static Window *s_main_window;

// pointer to main window layer
static Layer *s_main_window_layer;

// pointer to canvas layer
static Layer *s_canvas_layer;



static void canvas_update_proc(Layer *this_layer, GContext *ctx) {

  // Get the size of the layer
  GRect bounds = layer_get_bounds(this_layer);
  
  // Draw the thick Outer circle
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(13)), GOvalScaleModeFitCircle, 13, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
  
  // Draw the outer black holes
  graphics_context_set_fill_color(ctx, GColorBlack);
  for (int i=0; i<120; i++){
    graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(14)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE((i*3)-1.5), DEG_TO_TRIGANGLE((i*3))); 
    
  }
  
  // Draw three 2px thick black inner circles 
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(17)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(20)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(23)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
  
  // Draw the hour markers
  graphics_context_set_fill_color(ctx, GColorWhite);
  for (int i=0; i<12; i++){
    
    if (i%3){
      // Hours 1, 2, 4, 5, 7, 8, 10, 11
      graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(13)), GOvalScaleModeFitCircle, 10, DEG_TO_TRIGANGLE((i*30)-1.5), DEG_TO_TRIGANGLE((i*30)+1.5)); 
    }
    else{
      // Hours 12, 3, 6, 9
      graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(13)), GOvalScaleModeFitCircle, 13, DEG_TO_TRIGANGLE((i*30)-2), DEG_TO_TRIGANGLE((i*30)+2)); 
    }
    
  }
  
  // Draw the 3 white inner circles
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(41)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(46)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
  graphics_fill_radial(ctx, grect_inset(bounds, GEdgeInsets(60)), GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360)); 
    
}


static void main_window_load(Window *window) {
  
  // get the main window layer
  s_main_window_layer = window_get_root_layer(s_main_window);
  
  // Get the boundaries of the main layer
  GRect s_main_window_bounds = layer_get_bounds(s_main_window_layer);
  
  // Create the layer we will draw on
  s_canvas_layer = layer_create(s_main_window_bounds);
  // Set the update procedure for our layer
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);

  // Add the layer to our main window layer
  layer_add_child(s_main_window_layer, s_canvas_layer);
 
  // Tell the watchface layer it needs to redraw
  //layer_mark_dirty(s_main_window_layer);
    
  
}


static void main_window_unload(Window *window) {
      
}


static void init(void) {
    
  // Create the main window
  s_main_window = window_create();
  
  // set the background colour
  window_set_background_color(s_main_window, GColorBlack);
  
  // set the window load and unload handlers
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  // show the window on screen
  window_stack_push(s_main_window, true);
  
}


static void deinit(void) {
  
  // Destroy the main window
  window_destroy(s_main_window);
  
}


int main(void) {
  
  init();
  app_event_loop();
  deinit();
  
}