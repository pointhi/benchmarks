#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "harness.h"

#include "bashrc-libdeep/src/globals.h"
#include "bashrc-libdeep/src/deeplearn.h"
#include "bashrc-libdeep/src/deeplearndata.h"

#define TITLE     "Concrete Slump Training"
#define DATA_FILE "bashrc-libdeep/examples/concreteslump/slump_test.data"

int __attribute__ ((noinline)) test_harness(void) {
    int no_of_outputs = 4;
    int output_field_index[] = { 7,8,9,10 };
    float error_threshold_percent[] = { 0.6f, 4.5f };
    unsigned int random_seed = 123;

    deeplearn learner;
    deeplearndata_read_csv(DATA_FILE,
                           &learner,
                           3*3, 1,
                           no_of_outputs,
                           output_field_index, 0,
                           error_threshold_percent,
                           &random_seed);

    /* set learning rate */
    deeplearn_set_learning_rate(&learner, 10.f);

    /* set percentage of dropouts */
    deeplearn_set_dropouts(&learner, 1.f);

    learner.history.interval = 900000;

    deeplearn_set_title(&learner, TITLE);

    while (deeplearndata_training(&learner) != 0);

    deeplearn_free(&learner);

    return 0;
}

int main(int argc, char* argv[]) {
    _test_harness harness = {
        .name="bashrc-libdeep",
        .description="A deep learning library for C/C++",
        .test_harness=*test_harness,
        .expected_runtime=3500L
    };
    return _execute_harness(argc, argv, harness);
}