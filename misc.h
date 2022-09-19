#ifndef MISC_H
#define MISC_H

#ifdef __cplusplus

#include <string>
#include <stdint.h>
#include <algorithm>

/*
判断是否为短uuid
*/
bool IsBLEShortUUID(std::string);

/*
获取短uuid的字符串
*/
std::string GetBLEUuidDescByShortUuid(uint16_t shortuuid);



#endif // __cplusplus

#endif // MISC_H
