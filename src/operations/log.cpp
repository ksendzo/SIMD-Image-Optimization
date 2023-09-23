#include <algorithm>
#include <immintrin.h>
#include <vector> 
#include <cmath>

using namespace std;

void log_unoptimized(vector<float>& picture, float param) {
	float paramLog = logf(param);
	for (int i = 0; i < picture.size(); i++) {
		picture[i] = logf(picture[i]) / paramLog;
	}
}

void log_optimized(vector<float>& picture, float param) {
	int size = picture.size();
	float paramLog = logf(param);
	__m256 vParam = _mm256_set_ps(paramLog, paramLog, paramLog, paramLog, paramLog, paramLog, paramLog, paramLog);

	size_t i = 0;
	for (; i <= size - 8; i += 8) {
		__m256 vPicture = _mm256_load_ps((&picture[i]));
		__m256 vPartial = _mm256_log_ps(vPicture);
		__m256 vResult = _mm256_div_ps(vPartial, vParam);
		_mm256_store_ps(&picture[i], vResult);
	}

	for (; i < size; i++) {
		picture[i] = logf(picture[i]) / paramLog;
	}
}