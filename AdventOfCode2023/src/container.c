// C standard headers
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <container.h>

#define GENERAL_ERR     "ERROR READING DATA - %s\n"
#define EVAL_ERR        "EVALUATION ERROR - %s\nERROR CODE - %d\n"
#define UNLISTED_ERR    "UNLISTED ERROR"
#define UNLISTED_VAL    "VALUE"
#define USAGE           "%s [DATA PATH]"
#define DEFAULT_NAME    "challenge.exe"
#define READ_MODE       "rb"
#define BASE_LINESIZE   2

#define SERVICE_CHECK(_cond)    if(_cond) { \
                                    fprintf(stderr, GENERAL_ERR, strerror(errno)); \
                                    return EXIT_FAILURE; \
                                }

ReturnData EMPTY_DATA = { NULL, NULL, 0, EXIT_SUCCESS };

static char *extract_name(char *filePath);
static char *read_file(FILE *target, long *fSize);
static void print_char_len(char fill, int refLen);
static int determine_digits(int target);
static void print_output(const char *type, int output);

int main(int argc, char **argv) {
    if(argc != 2) {
        printf(USAGE, (argv[0] == NULL) ? DEFAULT_NAME : extract_name(argv[0]));
        return EXIT_FAILURE;
    }
    FILE *dataFile = fopen(argv[1], READ_MODE);
    SERVICE_CHECK(dataFile == NULL);

    long fSize;
    char *data = read_file(dataFile, &fSize);
    fclose(dataFile);
    SERVICE_CHECK(data == NULL);

    ReturnData evalData = eval(data, fSize);
    free(data);

    if(evalData.retCode == EXIT_SUCCESS)
        print_output((evalData.type == NULL) ? UNLISTED_VAL : evalData.type, evalData.output);
    else
        fprintf(stderr, EVAL_ERR, (evalData.errVal == NULL) ? UNLISTED_ERR : evalData.errVal, evalData.retCode);
    return evalData.retCode;
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

static char *extract_name(char *filePath) {
    char *lastSlash = strrchr(filePath, '/');
    if(lastSlash == NULL) lastSlash = strrchr(filePath, '\\');
    return (lastSlash == NULL) ? filePath : lastSlash + 1;
}

static char *read_file(FILE *target, long *fSize) {
    if(target == NULL) return NULL;
    if(fseek(target, 0, SEEK_END) == -1) return NULL;
    *fSize = ftell(target);
    if(*fSize == -1) return NULL;
    if(fseek(target, 0, SEEK_SET) == -1) return NULL;

    char *store = malloc(*fSize + 1);
    if(store == NULL) return NULL;
    size_t ret = fread(store, sizeof(char), *fSize, target);
    if(ret < *fSize) {
        free(store);
        errno = EIO;
        return NULL;
    }
    store[*fSize] = '\0';
    return store;
}

static void print_char_len(char fill, int refLen) {
    for(int i = 0; i < refLen; i++)
        printf("%c", fill);
}

static int determine_digits(int target) {
    int digits = 0;
    while(target != 0) {
        target /= 10;
        digits++;
    }
    return digits;
}

static void print_output(const char *type, int output) {
    int typeLen = strlen(type);
    print_char_len('-', typeLen);
    printf("\n%s\n", type);

    print_char_len('-', typeLen);
    printf("\n");
    print_char_len(' ', typeLen / 2 - determine_digits(output) / 2);
    printf("%d\n", output);
    print_char_len(' ', typeLen);
    printf("\n");
}