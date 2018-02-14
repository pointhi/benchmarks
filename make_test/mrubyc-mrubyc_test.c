#include <stdio.h>
#include <stdlib.h>

#include "harness.h"

#include "mrubyc-mrubyc/src/mrubyc.h"

/*
 * def fibonacci( n )
 *   if n == 0 or n == 1
 *     return n
 *   else
 *     return fibonacci( n - 1 ) + fibonacci( n - 2 )
 *   end
 * end
 *
 * j = 0
 * while j < 100
 *   s = 0
 *   i = 0
 *   while i <= 15
 *     s += fibonacci i
 *     i += 1
 *   end
 * j += 1
 * end
 */
unsigned char mrubyc_mrubyc_mrb[] = {
        0x52, 0x49, 0x54, 0x45, 0x30, 0x30, 0x30, 0x34, 0x03, 0x8b, 0x00, 0x00,
        0x01, 0x85, 0x4d, 0x41, 0x54, 0x5a, 0x30, 0x30, 0x30, 0x30, 0x49, 0x52,
        0x45, 0x50, 0x00, 0x00, 0x01, 0x3b, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00,
        0x00, 0xab, 0x00, 0x04, 0x00, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1e,
        0x02, 0x00, 0x00, 0x48, 0x02, 0x80, 0x00, 0xc0, 0x02, 0x00, 0x00, 0x46,
        0x00, 0xbf, 0xff, 0x83, 0x00, 0x40, 0x09, 0x97, 0x01, 0x3f, 0xff, 0x83,
        0x01, 0xbf, 0xff, 0x83, 0x00, 0x40, 0x04, 0x97, 0x02, 0x00, 0x80, 0x01,
        0x02, 0x80, 0x00, 0x06, 0x03, 0x00, 0xc0, 0x01, 0x02, 0x80, 0x00, 0xa0,
        0x02, 0x00, 0x40, 0xac, 0x01, 0x01, 0x00, 0x01, 0x02, 0x00, 0xc0, 0x01,
        0x02, 0x00, 0x40, 0xad, 0x01, 0x81, 0x00, 0x01, 0x02, 0x00, 0xc0, 0x01,
        0x02, 0xc0, 0x07, 0x03, 0x02, 0x00, 0x80, 0xb4, 0x02, 0x3f, 0xf9, 0x98,
        0x02, 0x00, 0x40, 0x01, 0x02, 0x00, 0x40, 0xad, 0x00, 0x81, 0x00, 0x01,
        0x02, 0x00, 0x40, 0x01, 0x02, 0xc0, 0x31, 0x83, 0x02, 0x00, 0xc0, 0xb3,
        0x02, 0x3f, 0xf4, 0x98, 0x02, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x4a,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x09, 0x66, 0x69,
        0x62, 0x6f, 0x6e, 0x61, 0x63, 0x63, 0x69, 0x00, 0x00, 0x01, 0x2b, 0x00,
        0x00, 0x02, 0x3c, 0x3d, 0x00, 0x00, 0x01, 0x3c, 0x00, 0x00, 0x00, 0x00,
        0x8b, 0x00, 0x03, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00,
        0x02, 0x00, 0x00, 0x26, 0x01, 0x80, 0x40, 0x01, 0x02, 0x3f, 0xff, 0x83,
        0x01, 0x80, 0x00, 0xb2, 0x01, 0xc0, 0x01, 0x98, 0x01, 0x80, 0x40, 0x01,
        0x02, 0x40, 0x00, 0x03, 0x01, 0x80, 0x00, 0xb2, 0x01, 0xc0, 0x01, 0x19,
        0x00, 0x80, 0x00, 0x29, 0x00, 0x40, 0x05, 0x17, 0x01, 0x80, 0x00, 0x06,
        0x02, 0x00, 0x40, 0x01, 0x02, 0x00, 0x80, 0xaf, 0x01, 0x80, 0x40, 0xa0,
        0x02, 0x00, 0x00, 0x06, 0x02, 0x80, 0x40, 0x01, 0x02, 0x80, 0x81, 0x2f,
        0x02, 0x00, 0x40, 0xa0, 0x01, 0x80, 0xc0, 0xac, 0x01, 0x80, 0x00, 0x29,
        0x01, 0x80, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
        0x00, 0x02, 0x3d, 0x3d, 0x00, 0x00, 0x09, 0x66, 0x69, 0x62, 0x6f, 0x6e,
        0x61, 0x63, 0x63, 0x69, 0x00, 0x00, 0x01, 0x2d, 0x00, 0x00, 0x01, 0x2b,
        0x00, 0x4c, 0x56, 0x41, 0x52, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x01, 0x6a, 0x00, 0x01, 0x73, 0x00, 0x01, 0x69, 0x00, 0x01,
        0x6e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00,
        0x03, 0x00, 0x03, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x45, 0x4e, 0x44,
        0x00, 0x00, 0x00, 0x00, 0x08
};

#define MEMORY_SIZE (1024*32)
static uint8_t memory_pool[MEMORY_SIZE];
static struct VM *vm;

int __attribute__ ((noinline)) test_harness(void) {
    struct VM *vm;

    mrbc_init_alloc(memory_pool, MEMORY_SIZE);

    init_static();

    vm = mrbc_vm_open(NULL);
    if (vm == NULL) {
        printf("VM open Error\n");
        return 1;
    }

    if (mrbc_load_mrb(vm, mrubyc_mrubyc_mrb) != 0) {
        fprintf(stderr, "Error: Illegal bytecode.\n");
        return 1;
    }

    mrbc_vm_begin(vm);
    mrbc_vm_run(vm);
    mrbc_vm_end(vm);
    mrbc_vm_close(vm);

    mrbc_free_all(vm);

    return 0;
}

int main(int argc, char *argv[]) {
    _test_harness harness = {
            .name="mrubyc-mrubyc",
            .description="some small mruby implementation",
            .test_harness=*test_harness,
            .expected_runtime=240L
    };

    return _execute_harness(argc, argv, harness);
}