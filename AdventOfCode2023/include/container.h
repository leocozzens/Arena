#ifndef CONTAINER_H
#define CONTAINER_H

typedef struct {
    char *type;
    char *errVal;
    int output;
    int retCode;
} ReturnData;

extern ReturnData EMPTY_DATA;

ReturnData eval(char *data, long fSize);

#endif