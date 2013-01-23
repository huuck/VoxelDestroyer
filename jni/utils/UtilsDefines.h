/*
 * UtilsDefines.h
 *
 *  Created on: Dec 19, 2012
 *      Author: Matsoii
 */

#ifndef UTILSDEFINES_H_
#define UTILSDEFINES_H_

#include <android/log.h>
#define	 LOG_TAG	"nativevoxelprototype"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define DELETE( ptr ) \
if (ptr != NULL)      \
{                     \
    delete ptr;       \
    ptr = NULL;       \
}

#define DELETE_ARRAY( ptr ) \
if (ptr != NULL)            \
{                           \
    delete[] ptr;           \
    ptr = NULL;             \
}

#define TRANSFORM_MAT_LENGTH 16
#define SWIPE_LEFT 1
#define SWIPE_RIGHT 2
#define DOUBLE_TAP 3

#endif /* UTILSDEFINES_H_ */
