#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

#define URL "https://adeetc.thothapp.com/api/v1/classes"
#define LIST_URL "https://adeetc.thothapp.com/api/v1/classes/%u/workitems" 
#define WORKITEM_URL "https://adeetc.thothapp.com/api/v1/workitems/%u"

struct MemoryStruct {
  char *memory;
  size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}

struct MemoryStruct chunk;
char *http_get_data(const char *url, size_t *data_size){
  CURL *curl_handle;
  CURLcode res;
  chunk.memory = malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
  
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  res = curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);
  
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    free(chunk.memory);
    curl_global_cleanup();
    return NULL;
  }
  else {
    curl_global_cleanup();
    *data_size = chunk.size;
    return chunk.memory;
  }
}

int get_class_id(char *ucShortName, char *lectiveSemester, char *className){
    size_t data_size;
    char* ptr = http_get_data(URL, &data_size);
  
    json_error_t error;
    json_t *root = json_loads(ptr, 0, &error);
    json_t *classes = json_object_get(root, "classes");
    free(ptr);
  
    
    char *classToFind;
    asprintf(&classToFind, "%s / %s / %s", ucShortName, lectiveSemester, className);
    json_t *data, *fullName, *id;
    const char *fullName_text;
    int id_int = 0;
    for(int i = 0; i < (int)json_array_size(classes); i++){
      
        data = json_array_get(classes, i);
        fullName = json_object_get(data, "fullName");
        fullName_text = json_string_value(fullName);
        if(strcmp(fullName_text, classToFind) == 0){
            id = json_object_get(data, "id");
            id_int = (int)json_integer_value(id);
            return id_int;
        }
    }
    return 0;
}



typedef struct workitem{
    int workitem_id;
    const char *doc_name;
    const char *attach_name;
} Workitem;

Workitem res[16];
Workitem *get_class_workitems(int class_id, size_t *workitems_size){
    char *workItemsURL;
    size_t data_size;
    asprintf(&workItemsURL, LIST_URL, class_id);
    char* ptr = http_get_data(workItemsURL, &data_size);
    
    json_error_t error;
    json_t *root = json_loads(ptr, 0, &error);
    json_t *workItems = json_object_get(root, "workItems");
    free(ptr);
    
    
    json_t *data, *id, *title, *_links, *self;
    int i;
    for(i = 0; i < (int)json_array_size(workItems); i++){
        data = json_array_get(workItems, i);
        id = json_object_get(data, "id");
        title = json_object_get(data, "title");
        _links = json_object_get(data, "_links");
        self = json_object_get(_links, "self");
        
        
        Workitem current;
        current.workitem_id = json_integer_value(id);
        current.doc_name = json_string_value(title);
        current.attach_name = json_string_value(self);
        res[i] = current;
    }
    *workitems_size = i;
    return res;
}