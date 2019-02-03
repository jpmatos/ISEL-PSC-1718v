#ifndef thoth_h__
#define thoth_h__
#include <string.h>

typedef struct workitem{
    int workitem_id;
    const char *doc_name;
    const char *attach_name;
} Workitem;

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
char *http_get_data(const char *url, size_t *data_size);
int get_class_id(char *ucShortName, char *lectiveSemester, char *className);
Workitem *get_class_workitems(int class_id, size_t *workitems_size);

#endif  // foo_h__