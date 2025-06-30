/*
 *  router.c
 *  
 *  Route paths
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "router.h"
#include "video.h"
#include "hashtable.h"
#include "utils.h"
#include "parse.h"

typedef struct {
    char* json;
    size_t offset;
} JsonBuffer;

void appendClipJson(Item* item, void* ctx)
{
    JsonBuffer* buf = ctx;
    if (buf->offset > 1) {
        buf->json[buf->offset++] = ',';
        buf->json[buf->offset++] = '\n';
    }
    int written = snprintf(buf->json + buf->offset, 16384 - buf->offset,
                           "{\"id\":\"%s\",\"filename\":\"%s\",\"size\":%zu}",
                           item->id, item->path, item->size);
    buf->offset += written;
}

void handleRequest(Table* t, int client_fd, struct Request* req)// void handleRequest(int client_fd, const char* request)
{
    const char* not_found = "HTTP/1.1 404 Not Found\r\n\r\nNot Found";
    if (req->method == GET) {
        const char* resource = req->url;
        printf("\nResource: %s\n\nLength: %lu\n", resource, strlen(resource));
        if (strncmp(resource, "/clip?id=", 9) == 0 && strlen(resource) > 16) {

            const char* idparam = strstr(resource, "id=");

            if (idparam) {

                char clip_id[256];
                char raw_id[256];
                sscanf(idparam + 3, "%255[^ \r\n]", raw_id);
                urldecode(clip_id, raw_id);
                printf("Serving video: %s\n", clip_id);
                serveVideo(t, client_fd, clip_id);
                return;
            }

        } else if (strncmp(resource, "/", 1) == 0 && strlen(resource) == 1) {

            serveFile(client_fd, "public/index.html");
            return;

        } else if (strncmp(resource, "/api/clips", 10) == 0) {

            char json[16384] = "[";
            JsonBuffer buf = { .json = json, .offset = 1 };

            iterateClips(t, appendClipJson, &buf);

            // json[buf.offset++] = '\n';
            json[buf.offset++] = ']';
            json[buf.offset] = '\0';

            char header[256];
            snprintf(header, sizeof(header),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: application/json\r\n"
                     "Content-Length: %zu\r\n"
                     "Connection: close\r\n\r\n",
                     buf.offset);

            write(client_fd, header, strlen(header));
            write(client_fd, json, buf.offset);
            close(client_fd);
            int f = open("clipslocal.json", O_WRONLY, 0644);
            write(f, json, buf.offset);
            close(f);
            // serveFile(client_fd, "public/clips.json");
            return;

        } else {

            printf("%s %s\n", not_found, resource);
            write(client_fd, not_found, strlen(not_found));
            close(client_fd);
            return;

        }
    }
    write(client_fd, not_found, strlen(not_found));
    return;
}
