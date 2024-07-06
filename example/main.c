#include <stdio.h>

#include <emscripten.h>
#include <emscripten/console.h>
#include <emscripten/html5.h>

#define EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION
#include "../emscripten_clipboard.h"

emscripten_clipboard clipboard;

void emscripten_main_loop() {
    // Nothing.
}

EM_BOOL mouse_clicked(int eventType, const EmscriptenMouseEvent* mouseEvent, void* userData) {
    emscripten_clipboard* clipboard = userData;
    if (mouseEvent->button == 0) {
        printf("Clipboard: %s\n", emscripten_clipboard_get(clipboard));
    }
    else {
        emscripten_clipboard_set(clipboard, "Hello, clipboard!");
    }
    return EMSCRIPTEN_RESULT_SUCCESS;
}

int main() {
    emscripten_clipboard_init(&clipboard);

    emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &clipboard, 0, mouse_clicked);

    //emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &clipboard, 0, 0);

    emscripten_set_main_loop(emscripten_main_loop, 30, 1);
    return 0;
}
