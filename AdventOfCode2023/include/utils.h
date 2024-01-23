#ifndef UTILS_H
#define UTILS_H

#define GRID_ERR_CODE ENOMEM

typedef struct {
    char **grid;
    char *store;
    long height;
} GridInfo;

GridInfo get_linegrid(char *data, long size);
void free_linegrid(GridInfo *target);
void set_linefeed(char *data);
char *get_linefeed(void);
void close_linefeed(void);

int convert_num(char *str);

extern GridInfo EMPTY_GRID;

#endif