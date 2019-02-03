#include <stdio.h>
#include <stdlib.h>

#include "thoth.h"
int main(int argc, char** argv) {
    size_t data_size;
    char *ptr = http_get_data(argv[1], &data_size);
    FILE *file_stream = fopen(argv[2], "w");
    fwrite(ptr, 1, data_size, file_stream);
    fclose(file_stream);
    return 0;
}

