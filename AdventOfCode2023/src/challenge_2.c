// C standard headers
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <container.h>
#include <utils.h>

#define VAL_SIZE            3
#define DIGITS              10
#define INVALID_COLOR       "Invalid color match"
#define S_LEN(_x)           (sizeof(_x) - 1)
#define COLOR_ENTRY(_word)  { _word, S_LEN(_word) }
#define VALUE_TYPE          "SUM OF ID'S"

#define RED_MAX             12
#define GREEN_MAX           13
#define BLUE_MAX            14

typedef enum {
    RED,
    GREEN,
    BLUE,
    MAX
} Color;

char digit[DIGITS] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

typedef struct {
    char *str;
    unsigned int size;
} ColorInfo;

ColorInfo colors[MAX] = {
    COLOR_ENTRY("red"),
    COLOR_ENTRY("green"),
    COLOR_ENTRY("blue")
};

static bool check_digit(char target);
static Color check_color(char *str);

ReturnData eval(char *data, long fSize) {
    char *lineFeed;
    set_linefeed(data);

    unsigned int pos = 0;
    char buffer[VAL_SIZE];
    ReturnData outData = EMPTY_DATA_WITH_TYPE(VALUE_TYPE);
    while((lineFeed = get_linefeed()) != NULL) {
        pos++;
        lineFeed = strchr(lineFeed, ':');
        if(lineFeed == NULL) break;

        bool possible = true;
        while(lineFeed[1] != '\0') {
            while(!check_digit(*lineFeed)) lineFeed++;
            {
                unsigned int i = 0;
                for(; *lineFeed != ' '; i++, lineFeed++)
                    buffer[i] = *lineFeed;
                buffer[i] = '\0';
            }
            lineFeed++;
            Color currColor = check_color(lineFeed);

            unsigned int max;
            unsigned int skipCount;
            switch(currColor) {
                case RED:
                max = RED_MAX;
                skipCount = colors[RED].size;
                break;
                case GREEN:
                max = GREEN_MAX;
                skipCount = colors[GREEN].size;
                break;
                case BLUE:
                max = BLUE_MAX;
                skipCount = colors[BLUE].size;
                break;
                default:
                errno = 0;
                outData.errVal = INVALID_COLOR;
                outData.retCode = EXIT_FAILURE;
                goto END;
            }
            if(convert_num(buffer) > max) {
                possible = false;
                break;
            }
            lineFeed += skipCount - 1;
        }
        if(possible) outData.output += pos;
    }

    END:
    close_linefeed();
    if(errno != 0) {
        outData.errVal = strerror(errno);
        outData.retCode = errno;
    }
    return outData;
}

static bool check_digit(char target) {
    for(unsigned char i = 0; i < DIGITS; i++)
        if(target == digit[i]) return true;
    return false;
}

static Color check_color(char *str) {
    for(Color i = 0; i < MAX; i++) {
        if(strncmp(colors[i].str, str, colors[i].size) == 0)
            return i;
    }
    return MAX;
}