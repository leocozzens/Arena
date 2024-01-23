// C standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <container.h>
#include <utils.h>

#define VALUE_TYPE          "SUM OF ENGINE PART NUMBERS"

ReturnData eval(char *data, long fSize) {
    GridInfo lineData = get_linegrid(data, fSize);
    ReturnData outData = { VALUE_TYPE, NULL, 0, EXIT_SUCCESS };

    if(lineData.grid == NULL) {
        outData.errVal = "Failed to fetch line grid";
        outData.retCode = GRID_ERR_CODE;
    }
    for(int i = 0; i < lineData.height; i++) {
        printf("%s\n", lineData.grid[i]);
    }
    free_linegrid(&lineData);
    return outData;
}