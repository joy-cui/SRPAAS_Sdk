#ifndef TYPEDEF___H
#define TYPEDEF___H


typedef enum {
	AUTH_SUCCESS = 0,
	AUTH_FAILTURE = -1,
	AUTH_PASS = -2
}AUTH_STATUS;
#if defined SRENGINE_ANDROID || defined SRENGINE_IOS
#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif
#endif //SRENGINE_ANDROID

//typedef long long int64_t;
//typedef unsigned long long uint64_t;
//typedef unsigned char uint8_t;
typedef unsigned int UINT32;
//typedef int int32_t;
typedef unsigned long long UINT64;//long

#endif
