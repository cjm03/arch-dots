#ifndef CACHE_H
#define CACHE_H

struct cache_entry {
    char* path;
    char* content_type;
    int content_length;
    void* content;
    struct cache_entry *prev, *next;
};

struct cache {
    struct hashtable* index;
    struct cache_entry *head, *tail;
    int max_size;
    int cur_size;
};

extern struct cache_entry* allocEntry(char* path, char* content_type, void* content, int content_length);
extern void freeEntry(struct cache_entry* entry);
extern struct cache* cacheCreate(int max_size, int hashsize);
extern void cacheFree(struct cache* cache);
extern void cachePut(struct cache* cache, char* path, char* content_type, void* content, int content_length);
extern struct cache_entry* cacheGet(struct cache* cache, char* path);

#endif
