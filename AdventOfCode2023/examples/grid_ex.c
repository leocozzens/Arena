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
    GridInfo lineData = get_linegrid(data, fSize);
    ReturnData outData = { VALUE_TYPE, NULL, 0, EXIT_SUCCESS };

    if(lineData.grid == NULL) {
        outData.errVal = "Failed to fetch line grid";
        outData.retCode = GRID_ERR_CODE;
    }
    for(long i = 0; i < lineData.height; i++) {
        printf("%s\n", lineData.grid[i]);
    }
    free_linegrid(&lineData);
    
    // Your ReturnData.output should contain your challenge answer
    return outData;
}