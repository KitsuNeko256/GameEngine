#pragma once

#include <random>

inline int max(int l, int r) {
	return l > r ? l : r;
}
inline float max(float l, float r) {
	return l > r ? l : r;
}

inline int min(int l, int r) {
	return l < r ? l : r;
}
inline float min(float l, float r) {
	return l < r ? l : r;
}

inline int toRange(int l, int v, int r) {
	return l < v ? (v < r ? v : r) : l;
}
inline float toRange(float l, float v, float r) {
	return l < v ? (v < r ? v : r) : l;
}

inline int randomFromRange(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

inline void removeUnderscore(std::string& str) {
	for (size_t i = 0; i < str.size(); ++i)
		if (str[i] == '_')
			str[i] = ' ';
}