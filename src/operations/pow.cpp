#include <algorithm>
#include <immintrin.h>
#include <vector> 
#include <cmath>

using namespace std;

void pow_unoptimized(vector<float>& picture, float param) {
	for (int i = 0; i < picture.size(); i++) {
		picture[i] = pow(picture[i], param);
	}
}

void pow_optimized(vector<float>& picture, float param) {
	int size = picture.size();
	__m256 vParam = _mm256_set_ps(param, param, param, param, param, param, param, param);

	size_t i = 0;
	for (; i <= size - 8; i += 8) {
		__m256 vPicture = _mm256_load_ps((&picture[i]));
		__m256 vResult = _mm256_pow_ps(vPicture, vParam);
		_mm256_store_ps(&picture[i], vResult);
	}

	for (; i < size; i++) {
		picture[i] = pow(picture[i], param);
	}
}