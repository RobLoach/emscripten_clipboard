# emscripten_clipboard

An attempt at allowing Clipboard usage through Emscripten. Due to browser permissions, the user is required to paste directly into the application to get the clipboard contents.

## Example

``` c
#define EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION
#include "emscripten_clipboard.h"

// Create the clipboard, and initialize it.
emscripten_clipboard clipboard;
emscripten_clipboard_init(&clipboard);

// Set the contents of the clipboard.
emscripten_clipboard_set(&clipboard, "Hello, World!");

// Retrieve the contents. This can be iffy, due to browser permissions.
const char* text = emscripten_clipboard_get(&clipboard);
```

## API

``` c
void emscripten_clipboard_init(emscripten_clipboard* clipboard);
const char* emscripten_clipboard_get(emscripten_clipboard* clipboard);
void emscripten_clipboard_set(emscripten_clipboard* clipboard, const char* text);
```

## Dependencies

- Emscripten

## Development

``` bash
npm start
```

## License

[LICENSE](LICENSE)
