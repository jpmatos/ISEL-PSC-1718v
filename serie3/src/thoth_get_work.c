#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

#include "thoth.h"

#define ASSIGNMENT_URL "https://adeetc.thothapp.com/classes/%s/%s/%s/workitems/%d/document"
#define ATTACHMENT_URL "https://adeetc.thothapp.com/classes/%s/%s/%s/workitems/%d/attachment"

int main(int argc, char** argv) {
    size_t size, data_size_assignment, data_size_attachment;
    int id = get_class_id(argv[1], argv[2], argv[3]);
    Workitem* res = get_class_workitems(id, &size);
    
    char *zip_filename;
    asprintf(&zip_filename, "%s_%s_%s.zip", argv[1], argv[2], argv[3]);
    zip_source_t *zip_source;
    zip_t *zip_file = zip_open(zip_filename, ZIP_CREATE, NULL);
    
    char **filesToDelete;
    filesToDelete = malloc((size*2) * sizeof(char*));
    
    char *assignmentURL, *assignmentName, *attachmentURL, *attachmentName;
    char *ptr_assignment, *ptr_attachment;
    FILE *assignment_stream, *attachment_stream;
    for (int i = 0; i<size; i++){
        asprintf(&assignmentURL, ASSIGNMENT_URL, argv[1], argv[2], argv[3], res[i].workitem_id);
        asprintf(&attachmentURL, ATTACHMENT_URL, argv[1], argv[2], argv[3], res[i].workitem_id);
        asprintf(&assignmentName, "%s.pdf", res[i].doc_name);
        asprintf(&attachmentName, "%s.zip", res[i].doc_name);
        
        ptr_assignment = http_get_data(assignmentURL, &data_size_assignment);
        ptr_attachment = http_get_data(attachmentURL, &data_size_attachment);

        assignment_stream = fopen(assignmentName, "w");
        fwrite(ptr_assignment, 1, data_size_assignment, assignment_stream);
        fclose(assignment_stream);
        attachment_stream = fopen(attachmentName, "w");
        fwrite(ptr_attachment, 1, data_size_attachment, attachment_stream);
        fclose(attachment_stream);
        
        zip_source = zip_source_file_create(assignmentName, 0, 0, NULL);
        zip_file_add(zip_file, assignmentName, zip_source, ZIP_FL_OVERWRITE);
        zip_source = zip_source_file_create(attachmentName, 0, 0, NULL);
        zip_file_add(zip_file, attachmentName, zip_source, ZIP_FL_OVERWRITE);
        
        filesToDelete[i] = malloc((256+1)*sizeof(char));
        filesToDelete[(size*2)-i-1] = malloc((256+1)*sizeof(char));
        strcpy(filesToDelete[i], assignmentName);
        strcpy(filesToDelete[(size*2)-i-1], attachmentName);
    }
    zip_close(zip_file);
    
    for(int i=0; i<size*2; i++){
        remove(filesToDelete[i]);
        free(filesToDelete[i]);
    }
    free(filesToDelete);
    
    return 0;
}

