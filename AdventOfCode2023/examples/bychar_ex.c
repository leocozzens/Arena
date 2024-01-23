// C standard headers
#include <stdio.h>
#include <errno.h>
// Local headers
#include <container.h>
#include <utils.h>
#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1

#define VALUE_TYPE          "OBJECTS"

ReturnData eval(char *data, long fSize) {
    ReturnData outData = { VALUE_TYPE, NULL, 0, EXIT_SUCCESS };
    for(long i = 0; i < fSize; i++) {
        printf("%c", data[i]);
    }

    // Your ReturnData.output should contain your challenge answer
    return outData;
}