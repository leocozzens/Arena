// C standard headers
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <utils.h>

#define BASE_LINESIZE   256

GridInfo EMPTY_GRID = { NULL, NULL, 0 };

GridInfo get_linegrid(char *data, long size) {
    GridInfo newGrid = { NULL, NULL, 1 };
    for(char *read = data; *read != '\0'; read++) {
        if(*read == '\r') size--;
        if(*read == '\n') newGrid.height++;
    }
    newGrid.grid = malloc(sizeof(char*) * newGrid.height);
    if(newGrid.grid == NULL) return EMPTY_GRID;

    newGrid.store = malloc(size + 1);
    if(newGrid.store == NULL) {
        free(newGrid.grid);
        return EMPTY_GRID;
    }
    long index = 0;
    char *lineStart = NULL;
    for(long i = 0; i <= size && index < newGrid.height; i++, data++) {
        while(*data == '\r') data++;
        if(lineStart == NULL)
            lineStart = newGrid.store + i;

        if(*data == '\n' || i == size) {
            newGrid.store[i] = '\0';
            newGrid.grid[index] = lineStart;
            lineStart = NULL;
            index++;
        }
        else newGrid.store[i] = *data;
    }
    if(index != newGrid.height) {
        free(newGrid.store);
        free(newGrid.grid);
        return EMPTY_GRID;
    }
    return newGrid;
}

void free_linegrid(GridInfo *target) {
    free(target->store);
    free(target->grid);
    *target = EMPTY_GRID;
}

static char *lineFeed = NULL;
static char *lineBuff = NULL;

void set_linefeed(char *data) {
    lineFeed = data;
}

char *get_linefeed(void) {
    static unsigned int size = 0;
    if(lineFeed == NULL || *lineFeed == '\0') {
        errno = 0;
        return NULL;
    }
    while(*lineFeed == '\n' || *lineFeed == '\r') lineFeed++;
    if(lineBuff == NULL) {
        lineBuff = malloc(BASE_LINESIZE);
        if(lineBuff == NULL) { errno = ENOMEM; return NULL; }
        size = BASE_LINESIZE;
    }
    unsigned int i = 0;
    for(; !(*lineFeed == '\r' || *lineFeed == '\n' || *lineFeed == '\0'); lineFeed++) {
        if(i >= size - 2) {
            char *tmp = realloc(lineBuff, size * 2);
            if(tmp == NULL) { errno = ENOMEM; return NULL; }
            lineBuff = tmp;
            size *= 2;
        }
        lineBuff[i] = *lineFeed;
        i++;
    }
    lineBuff[i] = '\0';
    errno = 0;
    return lineBuff;
}

void close_linefeed(void) {
    free(lineBuff);
    lineFeed = NULL;
    lineBuff = NULL;
}

int convert_num(char *str) {
    int ret = 0;
    while(*str != '\0')
        ret = ret * 10 + *str++ - '0';
    return ret;
}