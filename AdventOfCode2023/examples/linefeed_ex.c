// C standard headers
#include <stdio.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <container.h>
#include <utils.h>

#define VALUE_TYPE          "OBJECTS"

ReturnData eval(char *data, long fSize) {
    set_linefeed(data);
    char *lineFeed;
    while((lineFeed = get_linefeed()) != NULL) {
        printf("%s\n", lineFeed);
    }

    close_linefeed();
    ReturnData outData = { VALUE_TYPE, strerror(errno), 0, errno };
    // Your ReturnData.output should contain your challenge answer
    return outData;
}