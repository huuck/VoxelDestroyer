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

#define NULL 0

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

#define MAX(x, y) x > y ? x : y

#define TRANSFORM_MAT_LENGTH 16
#define SWIPE_LEFT 1
#define SWIPE_RIGHT 2
#define SINGLE_TAP 3

#define	MAX_WIDTH 16
#define	MAX_HEIGHT 16
#define	MAX_DEPTH 16

#endif /* UTILSDEFINES_H_ */
