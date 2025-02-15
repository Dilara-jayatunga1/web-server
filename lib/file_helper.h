#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

int get_file_descriptor(const char *directory, const char *file_name);
const char *get_file_extension(const char *file_name);
const char *get_mime_type(const char *file_ext);  // Add the declaration for get_mime_type
char *url_decode(const char *src); 

#endif