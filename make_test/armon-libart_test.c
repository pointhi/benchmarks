#include <stdio.h>
#include <string.h>

#include "harness.h"

#include "armon-libart/src/art.h"

#define LOREM_IPSUM "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
#define LOREM_IPSUM10 LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM
#define LOREM_IPSUM100 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10

int __attribute__ ((noinline)) test_harness(void) {
    art_tree t;
    art_tree_init(&t);

    char* text = LOREM_IPSUM100;
    int max_len = strlen(text);

    for(int i = 0; i < max_len; i+=20) {
        char *key = text+i;
        art_insert(&t, (unsigned char *) key, max_len - i + 1, NULL);
    }

    art_tree_destroy(&t);

    return 0;
}

int main(int argc, char* argv[]) {
    _test_harness harness = {
        .name="armon-libart",
        .description="Adaptive Radix Trees",
        .test_harness=*test_harness,
        .expected_runtime=510L
    };
    return _execute_harness(argc, argv, harness);
}