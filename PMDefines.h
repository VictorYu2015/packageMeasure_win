#ifndef PM_DEFINES_H_
#define PM_DEFINES_H_

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////////
// Define App related PROPERTY and CMD
/////////////////////////////////////////////////////////////////////

enum {
    I_CMD_START_FETCH_PACKAGE_INFO       = I_CMD_USER_DEFINED + 1, ///< see PackageInfo
    I_CMD_STOP_FETCH_PACKAGE_INFO        = I_CMD_USER_DEFINED + 2,
    I_CMD_START_FETCH_PACKAGE_INFO_IMAGE = I_CMD_USER_DEFINED + 3, ///< image buffer after package info
    I_CMD_STOP_FETCH_PACKAGE_INFO_IMAGE  = I_CMD_USER_DEFINED + 4,
    I_CMD_RESET_BG_IMAGE                 = I_CMD_USER_DEFINED + 5, ///< algorithm relate
};


typedef struct {
    int32_t     timestamp;
    int32_t     type;           ///< see PACKAGE_TYPE_LIST
#define I_PACKAGE_TYPE_NONE         0
#define I_PACKAGE_TYPE_BOX          1
#define I_PACKAGE_TYPE_IRREGULAR    2
    float       x;
    float       y;
    float       z;
    float       boundingVolume; ///< accumulated vol
    float       integeralVolume;///< accumulated vol
    char        devID[32];      ///< User defined device ID
    int32_t     rsvd;
} PackageInfo;



#ifdef __cplusplus
}
#endif


#endif
