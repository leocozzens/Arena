// C standard headers
#include <stdlib.h>
#include <errno.h>
// Local headers
#include <utils.h>

#define BASE_LINESIZE   256

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