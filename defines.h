#ifndef XYZ_PACKAGE_MEASURE_APP_DEFINES_H_
#define XYZ_PACKAGE_MEASURE_APP_DEFINES_H_


#include <stdint.h>


/// TODO: use default config
#define DEVICE_DEFAULT_IP               "192.168.1.167"
#define DEVICE_DEFAULT_NETMASK          "255.255.255.0"
#define DEVICE_DEFAULT_GATEWAY          "192.168.1.1"
#define DEVICE_DEFAULT_DNS              "192.168.1.1"
#define SERVER_DEFAULT_PORT             7000


#ifdef __cplusplus
extern "C" {
#endif

/// error id
enum {
    I_ERR_NO_ERROR              = 0,
    I_ERR_UNKNOWN_ERROR         = -1000,
    I_ERR_NOT_IMPLEMENTED       = -1001,
    I_ERR_NOT_READY             = -1002,
    I_ERR_DEVICE_ERROR          = -1003,
    I_ERR_ACTION_FAILED         = -1004,
    I_ERR_CONNECTION_ERROR      = -1005,
    I_ERR_INVALID_ACTION        = -1006,
    I_ERR_INVALID_PROPERTY      = -1007,
    I_ERR_INVALID_CMD           = -1008,
    I_ERR_INVALID_CMD_VAL       = -1009,
    I_ERR_NO_NEW_FRAME          = -1010,
    I_ERR_OUT_OF_MEMORY         = -1011,
    I_ERR_WRONG_MODE            = -1012,
    I_ERR_NOT_CAPTURING         = -1012,
    I_ERR_BUSY                  = -1013,
    I_ERR_COMPUTE_ERROR         = -1014,
    I_ERR_INVALID_PARAM         = -1015,
};
typedef int16_t ErrID;


enum I_WORK_MODE_LIST {
    I_VAL_WORK_MODE_PREVIEW     = 1000,
    I_VAL_WORK_MODE_SETUP       = 1001,
    I_VAL_WORK_MODE_NORMAL_RUN  = 1002,
};
typedef int32_t WorkMode;


enum I_TRIGGER_MODE_LIST {
    I_VAL_TRIGGER_MODE_OUTSIDE      = 1100,
    I_VAL_TRIGGER_MODE_INTERNAL     = 1101,
    I_VAL_TRIGGER_MODE_CONTINUOUS   = 1102,
};
typedef int32_t TriggerMode;


/// data package
typedef struct {
    int16_t     action_id;      ///< action id
    int16_t     target_id;      ///< property id or cmd id or error id (if action_id == I_ACTION_ANSWER)
    int16_t     error_id;       ///< will be ignored in request
    int16_t     reserved;
    int32_t     uid;            ///< UID for user to match request and answer
    uint32_t    length;         ///< data buffer length in bytes (i.e. size of byte array 'data')
    uint8_t     data[0];        ///< data buffer
} XData;


/// action id
enum {
    I_ACTION_WRITE_PROPERTY = 0,
    I_ACTION_READ_PROPERTY  = 1,
    I_ACTION_CMD            = 2,
    I_ACTION_ANSWER         = 3,
};
typedef int16_t ActionID;


/// property id
enum {
    I_PROPERTY_string_DEV_UID            = 10,
    I_PROPERTY_string_DEV_IP             = 11,
    I_PROPERTY_string_DEV_NETMASK        = 12,
    I_PROPERTY_string_DEV_GATEWAY        = 13,
    I_PROPERTY_string_DEV_DNS            = 14,

    I_PROPERTY_int32_WORK_MODE           = 30,  ///< see I_WORK_MODE_LIST
    I_PROPERTY_int32_TRIGGER_MODE        = 31,  ///< see I_TRIGGER_MODE_LIST

    I_PROPERTY_USER_DEFINED              = 1000,///< user defined Property starts here
};
typedef int16_t PropertyID;


/// cmd id
enum {
    I_CMD_START_CAPTURE     = 100,
    I_CMD_STOP_CAPTURE      = 101,
    I_CMD_TRIGGER           = 102,
    I_CMD_SAVE_CONFIG       = 103,
    I_CMD_RESET_CONFIG      = 104,
    I_CMD_REBOOT            = 105,
    I_CMD_FETCH_LOG         = 106,

    I_CMD_START_FETCH_DEPTH = 200,  ///< set device to send depth image continuously
    I_CMD_STOP_FETCH_DEPTH  = 201,

    I_CMD_HEART_BEAT        = 999,  ///< heart beat

    I_CMD_USER_DEFINED      = 1000, ///< user defined cmd starts here
};
typedef int16_t CmdID;


#ifdef __cplusplus
}
#endif


#endif
