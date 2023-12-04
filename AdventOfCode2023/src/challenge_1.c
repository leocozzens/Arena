// C standard headers
#include <stdio.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <container.h>
#include <utils.h>

ReturnData eval(char *data, long fSize) {
    char *lineFeed;
    set_linefeed(data);

    int output = 0;
    while((lineFeed = get_linefeed()) != NULL) {
        // Read here
    }
    close_linefeed();

    ReturnData outData = { NULL, strerror(errno), output, errno };
    return outData;
}