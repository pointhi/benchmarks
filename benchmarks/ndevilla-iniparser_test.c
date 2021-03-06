#include "chayai.h"  // first include!

#include <assert.h>

/* We need to directly insert the .c file in order to test the */
/* static functions as well */
#include "ndevilla-iniparser/src/dictionary.h"


/** Minimal allocated number of entries in a dictionary */
#define DICTMINSZ 128

static char *get_dump(dictionary *d)
{
    FILE *fd;
    char *dump_buff;
    int dump_size;

    /* Dump the dictionary in temporary file */
    fd = tmpfile();
    if (fd == NULL)
        return NULL;
    dictionary_dump(d, fd);

    /* Retrieve the dump file */
    dump_size = ftell(fd);
    if (dump_size == -1) {
        fclose(fd);
        return NULL;
    }
    rewind(fd);

    dump_buff = (char*) calloc(1, dump_size + 1);
    if (dump_buff == NULL) {
        fclose(fd);
        return NULL;
    }
    if (fread(dump_buff, 1, dump_size, fd) != (size_t)dump_size) {
        fclose(fd);
        return NULL;
    }

    fclose(fd);
    return dump_buff;
}

BENCHMARK(ndevilla, iniparser, 10, 1) {
    int i, j;
    char sec_name[32];
    char key_name[64];

    dictionary *dic = dictionary_new(DICTMINSZ);
    assert(dic != NULL);

    /* Makes the dictionary grow */
    for (i = 1 ; i < 5001; ++i) {
        sprintf(sec_name, "sec%d", i);
        for (j = 1 ; j < 11; ++j) {
            sprintf(key_name, "%s:key%d", sec_name, j);
            dictionary_set(dic, sec_name, key_name);
        }
    }

    assert(dic->n == 5000);

    /* Shrink the dictionary */
    for (i = 1000 ; i > 0; --i) {
        sprintf(sec_name, "sec%d", i);
        for (j = 10 ; j > 0; --j) {
            sprintf(key_name, "%s:key%d", sec_name, j);
            dictionary_unset(dic, key_name);
        }
        dictionary_unset(dic, sec_name);
    }

    assert(dic->n == 4000);

    dictionary_del(dic);
}

int main(int argc, char** argv) {

    REGISTER_BENCHMARK(ndevilla, iniparser); // ini file parser

    RUN_BENCHMARKS(argc, argv);

    return 0;
}