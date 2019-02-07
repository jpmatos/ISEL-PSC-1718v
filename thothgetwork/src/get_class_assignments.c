#include "thoth.h"
#include <stdio.h>

int main(int argc, char **argv){
    int id = get_class_id(argv[1], argv[2], argv[3]);
    
    size_t size;
    Workitem* res = get_class_workitems(id, &size);
    printf("turma: %s / %s / %s\n", argv[1], argv[2], argv[3]);
    for(int i=0; i < size; i++){
        printf("enunciado: %s\n", res[i].doc_name);
    }

    return 0;
}
