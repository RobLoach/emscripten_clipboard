#include <assert.h>
#include <stdio.h>
#include <string.h>

#define EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION
#include "../emscripten_clipboard.h"

static int tests_run = 0;
static int tests_passed = 0;

#define TEST(name) void test_##name()
#define RUN(name) do { tests_run++; test_##name(); tests_passed++; printf("PASS: " #name "\n"); } while(0)
#define ASSERT(cond) do { if (!(cond)) { printf("FAIL: %s\n", #cond); return; } } while(0)

TEST(init_sets_defaults) {
    emscripten_clipboard clipboard;
    emscripten_clipboard_init(&clipboard);
    ASSERT(clipboard.text[0] == '\0');
    ASSERT(clipboard.user_data == NULL);
    emscripten_clipboard_deinit(&clipboard);
}

TEST(deinit_null_safe) {
    emscripten_clipboard_deinit(NULL);
}

TEST(deinit_clears_state) {
    emscripten_clipboard clipboard;
    emscripten_clipboard_init(&clipboard);
    emscripten_clipboard_set(&clipboard, "hello");
    emscripten_clipboard_deinit(&clipboard);
    ASSERT(clipboard.text[0] == '\0');
    ASSERT(clipboard.user_data == NULL);
}

TEST(deinit_allows_reinit) {
    emscripten_clipboard clipboard;
    emscripten_clipboard_init(&clipboard);
    emscripten_clipboard_set(&clipboard, "first");
    emscripten_clipboard_deinit(&clipboard);
    emscripten_clipboard_init(&clipboard);
    ASSERT(clipboard.text[0] == '\0');
    emscripten_clipboard_deinit(&clipboard);
}

TEST(get_returns_set_text) {
    emscripten_clipboard clipboard;
    emscripten_clipboard_init(&clipboard);
    emscripten_clipboard_set(&clipboard, "test text");
    ASSERT(strcmp(emscripten_clipboard_get(&clipboard), "test text") == 0);
    emscripten_clipboard_deinit(&clipboard);
}

TEST(get_null_safe) {
    ASSERT(emscripten_clipboard_get(NULL) == NULL);
}

int main() {
    RUN(init_sets_defaults);
    RUN(deinit_null_safe);
    RUN(deinit_clears_state);
    RUN(deinit_allows_reinit);
    RUN(get_returns_set_text);
    RUN(get_null_safe);
    printf("%d/%d tests passed\n", tests_passed, tests_run);
    return tests_passed == tests_run ? 0 : 1;
}
