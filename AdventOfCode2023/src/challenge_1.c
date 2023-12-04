// C standard headers
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// Local headers
#include <container.h>
#include <utils.h>

#define EXIT_SUCCESS                0
#define EXIT_FAILURE                1
#define DIGITS                      10
#define VAL_SIZE                    3
#define EMPTY_VALS                  "NN"
#define EMPTY_VAL                   'N'
#define WORD_OVERLAP                2
#define VALUE_TYPE                  "CALIBRATION VALUE"
#define S_LEN(_x)                   (sizeof(_x) - 1)
#define DIGIT_ENTRY(_word, _digit)  { _word, S_LEN(_word), _digit }

typedef struct {
    char *word;
    int wordLen;
    char digit;
} Digit;


Digit digitTable[] = {
    DIGIT_ENTRY("zero", '0'),
    DIGIT_ENTRY("one", '1'),
    DIGIT_ENTRY("two", '2'),
    DIGIT_ENTRY("three", '3'),
    DIGIT_ENTRY("four", '4'),
    DIGIT_ENTRY("five", '5'),
    DIGIT_ENTRY("six", '6'),
    DIGIT_ENTRY("seven", '7'),
    DIGIT_ENTRY("eight", '8'),
    DIGIT_ENTRY("nine", '9')
};

static void reset_buff(char *buff, int *output);
static char match_num(char *target, long *iterator);

ReturnData eval(char *data, long fSize) {
    ReturnData outData = { VALUE_TYPE, NULL, 0, EXIT_SUCCESS };
    char val[VAL_SIZE] = EMPTY_VALS;

    for(long i = 0; i < fSize; i++) {
        if(data[i] == '\n' || data[i] == '\r') {
            reset_buff(val, &outData.output);
            continue;
        }
        char result = match_num(data + i, &i);
        if(result != '\0') {
            if(val[0] == EMPTY_VAL) val[0] = result;
            val[1] = result;
        }
    }
    reset_buff(val, &outData.output);
    return outData;
}

static void reset_buff(char *buff, int *output) {
    if(buff[0] != EMPTY_VAL) {
        *output += convert_num(buff);
        memcpy(buff, EMPTY_VALS, VAL_SIZE);
    }
}

static char match_num(char *target, long *iterator) {
    for(int i = 0; i < DIGITS; i++) {
        if(*target == digitTable[i].digit)
            return digitTable[i].digit;
        if(strncmp(target, digitTable[i].word, digitTable[i].wordLen) == 0) {
            *iterator += digitTable[i].wordLen - WORD_OVERLAP;
            return digitTable[i].digit;
        }
    }
    return '\0';
}