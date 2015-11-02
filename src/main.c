#include <pebble.h>

typedef enum {
  AppKeyReady = 0
} AppKey;

static Window *s_main_window;
static TextLayer *s_text_layer;

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *ready_tuple = dict_find(iter, AppKeyReady);
  if(ready_tuple) {
    // PebbleKit JS is ready! Safe to send messages
    text_layer_set_text(s_text_layer, "PebbleKit JS is ready!");
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_text_layer = text_layer_create(PBL_IF_ROUND_ELSE(grect_inset(bounds, GEdgeInsets(20, 0)), bounds));
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(s_text_layer, "Waiting for JS...");
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));

#if defined(PBL_ROUND)
  text_layer_enable_screen_text_flow_and_paging(s_text_layer, 5);
#endif
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
}

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);

  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(64, 64);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
