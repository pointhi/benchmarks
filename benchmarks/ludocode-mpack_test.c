#include "chayai.h"  // first include!

#include <assert.h>

#include "mpack/mpack.h"

#define LOREM_IPSUM "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
#define LOREM_IPSUM10 LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM
#define LOREM_IPSUM100 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10

BENCHMARK(ludocode, mpack, 100, 1) {
    char *buf;
    size_t size;

    mpack_writer_t writer;
    mpack_writer_init_growable(&writer, &buf, &size);

    for(int i=0; i < 5000; i++) {
        mpack_write_uint(&writer, 0x0f);
        mpack_write_float(&writer, 2.718f);
        mpack_write_double(&writer, 3.14159265);

        const char utf8_valid[] = " \xCF\x80 \xe4\xb8\xad \xf0\xa0\x80\xb6";
        mpack_write_str(&writer, utf8_valid, (uint32_t) sizeof(utf8_valid) - 1);
        mpack_write_str(&writer, LOREM_IPSUM100, (uint32_t) sizeof(LOREM_IPSUM100) - 1);
    }

    mpack_error_t error = mpack_writer_destroy(&writer);
    assert(error == mpack_ok);

    assert(buf[0] == 0x0F && buf[256] == 0x20 && buf[1024] == 0x65);

    free(buf);
}

int main(int argc, char** argv) {

    REGISTER_BENCHMARK(ludocode, mpack); // message pack serialisation format

    RUN_BENCHMARKS(argc, argv);

    return 0;
}