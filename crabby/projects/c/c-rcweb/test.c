#include <stdio.h>
#include <string.h>

int main(void)
{
    char* clip_id = "RUSTT2024.22.31.4-4.44.DVR-Trim";
    char vidurl[256];
    snprintf(vidurl, sizeof(vidurl), "/clip?id=%s", clip_id);

    char html[4096];
    snprintf(html, sizeof(html),
             "<!DOCTYPE html>"
             "<html lang='en'>"
             "<head>"
             "<meta charset='UTF-8'>"
             "<title>Clip Viewer</title>"
             "<style>"
             "body { font-family: sans-serif; background: #121212; color: #eee; padding: 1em; }"
             "nav { background-color: #333; color: white; }"
             "nav a { color: white; text-decoration: none; }"
             ".container { display: flex; justify-content: center; align-items: center; padding: 2rem; }"
             "video { width: 100%%; height: auto; border: 2px solid #ccc; border-radius: 8px; }"
             "</style>"
             "</head>"
             "<body>"
             "<nav><a href='/'>Home</a></nav>"
             "<h1>Now Playing</h1>"
             "<div class='container'>"
             "<video controls autoplay>"
             "<source src='%s' type='video/mp4'>"
             "Your browser does not support the video tag."
             "</video>"
             "</div>"
             "</body></html>", vidurl);

    size_t bodylen = strlen(html);

    char header[512];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %zu\r\n"
             "Connection: keep-alive\r\n\r\n", bodylen);
    printf("bodylen: %ld\n", bodylen);
    printf("strlen: %zu\n", strlen(html));

}
