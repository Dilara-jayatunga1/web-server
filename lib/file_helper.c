#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int get_file_descriptor(const char *directory, const char *file_name)
{
    char src_file[100];
    strcpy(src_file, directory);
    strcat(src_file, file_name);

    int file_descriptor = open(src_file, O_RDONLY);

    return file_descriptor;
}

const char *get_file_extension(const char *file_name)
{
    const char *dot = strrchr(file_name, '.');

    if(!dot || dot == file_name)
    {
        return "";
    }

    return dot + 1;

    

}

const char *get_mime_type(const char *file_ext) {
    if (strcaseicmp(file_ext, "html") == 0 || strcaseicmp(file_ext, "htm") == 0) {
        return "text/html";
    } else if (strcaseicmp(file_ext, "txt") == 0) {
        return "text/plain";
    } else if (strcaseicmp(file_ext, "jpg") == 0 || strcaseicmp(file_ext, "jpeg") == 0) {
        return "image/jpeg";
    } else if (strcaseicmp(file_ext, "png") == 0) {
        return "image/png";
    } else {
        return "application/octet-stream";
    }
}

char *url_decode(const char *src) {
    size_t src_len = strlen(src);
    char *decoded = malloc(src_len + 1);  // Allocate memory for the decoded string
    size_t decoded_len = 0;

    // Decode %xx to hex
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] == '%' && i + 2 < src_len) {
            int hex_val;
            sscanf(src + i + 1, "%2x", &hex_val);
            decoded[decoded_len++] = hex_val;
            i += 2;
        } else {
            decoded[decoded_len++] = src[i];
        }
    }

    // Add null terminator at the end of the decoded string
    decoded[decoded_len] = '\0';
    return decoded;
}