#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuffer;

StringBuffer* sb_init(size_t initial_capacity) {
    StringBuffer *sb = malloc(sizeof(StringBuffer));
    if (!sb) return NULL;
    sb->data = malloc(initial_capacity);
    if (!sb->data) {
        free(sb);
        return NULL;
    }
    sb->length = 0;
    sb->capacity = initial_capacity;
    sb->data[0] = '\0';
    return sb;
}

int sb_append(StringBuffer *sb, const char *str) {
    size_t str_len = strlen(str);
    if (sb->length + str_len + 1 > sb->capacity) {
        size_t new_capacity = sb->capacity * 2;
        while (new_capacity < sb->length + str_len + 1) {
            new_capacity *= 2;
        }
        char *new_data = realloc(sb->data, new_capacity);
        if (!new_data) return -1;
        sb->data = new_data;
        sb->capacity = new_capacity;
    }
    memcpy(sb->data + sb->length, str, str_len + 1);
    sb->length += str_len;
    return 0;
}

void sb_free(StringBuffer *sb) {
    if (!sb) return;
    free(sb->data);
    free(sb);
}

int main() {
    StringBuffer *sb = sb_init(8);
    if (!sb) {
        printf("Initialization failed\n");
        return 1;
    }

    sb_append(sb, "Hello");
    printf("Buffer: %s | Length: %zu | Capacity: %zu\n", sb->data, sb->length, sb->capacity);

    sb_append(sb, ", World!");
    printf("Buffer: %s | Length: %zu | Capacity: %zu\n", sb->data, sb->length, sb->capacity);

    sb_append(sb, " This is a growing buffer.");
    printf("Buffer: %s | Length: %zu | Capacity: %zu\n", sb->data, sb->length, sb->capacity);

    sb_free(sb);
    return 0;
}
