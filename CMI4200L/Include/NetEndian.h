#pragma once
#include <winsock2.h>
#include <stdint.h> // VS2010

inline uint64_t htonll(uint64_t x) {
	static const int num = 1;
	if (*(const char*)&num == 1) {
		// little-endian
		uint32_t high = htonl((uint32_t)(x >> 32));
		uint32_t low  = htonl((uint32_t)(x & 0xFFFFFFFFULL));
		return ((uint64_t)low << 32) | high;
	} else {
		// big-endian
		return x;
	}
}
inline uint64_t ntohll(uint64_t x) { return htonll(x); }