#include <stddef.h>
#include <stdint.h>

#define ALIGN_TO(_value, _alignment) ((_value) + ((_alignment) - 1) & -(_alignment))

typedef struct fba {
    uint8_t* buffer;
    uint8_t* bufferend;
    uint8_t* head;
} fba_t;

static inline void fbaInit(fba_t* fba, uint8_t* buffer, size_t buffer_size) {
    *fba = (fba_t) { .buffer = buffer, .bufferend = buffer + buffer_size, .head = buffer };
}

static inline void fbaReset(fba_t* fba) {
    fba->head = fba->buffer;
}

static inline void* fbaAllocOpt(fba_t* fba, size_t size, size_t align) {
    uint8_t* head = (uint8_t*)ALIGN_TO((uintptr_t)fba->head, align);
    if (head + size > fba->bufferend) return NULL;
    fba->head = head + size;
    return head;
}

static inline void* fbaAlloc(fba_t* fba, size_t size) {
    return fbaAllocOpt(fba, size, _Alignof(void*));
}
