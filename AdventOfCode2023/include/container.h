#ifndef CONTAINER_H
#define CONTAINER_H

typedef struct {
    char *type;
    char *errVal;
    int output;
    int retCode;
} ReturnData;

#define EMPTY_DATA_WITH_TYPE(_type) { _type, NULL, 0, EXIT_SUCCESS }

extern ReturnData EMPTY_DATA;

ReturnData eval(char *data, long fSize);

#endif