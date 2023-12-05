// C standard headers
#include <stdio.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <container.h>
#include <utils.h>

#define VALUE_TYPE          "SUM OF ENGINE PART NUMBERS"

ReturnData eval(char *data, long fSize) {
    set_linefeed(data);
    char *lineFeed;
    while((lineFeed = get_linefeed()) != NULL) {
        // Solve here
    }
    close_linefeed();

    ReturnData outData = { VALUE_TYPE, strerror(errno), 0, errno };
    return outData;
}