#include <algorithm>
#include <immintrin.h>
#include <vector> 
#include <cmath>

using namespace std;

void abs_unoptimized(vector<float>& picture) {
	for (int i = 0; i < picture.size(); i++) {
		picture[i] = abs(picture[i]);
	}
}

void abs_optimized(vector<float>& picture) {
	int size = picture.size();
	__m256 vMinus = _mm256_set_ps(-1, -1, -1, -1, -1, -1, -1, -1);

	size_t i = 0;
	for (; i <= size - 8; i += 8) {
		__m256 vPicture = _mm256_load_ps((&picture[i]));
		__m256 vNegative = _mm256_mul_ps(vPicture, vMinus);
		__m256 vResult = _mm256_max_ps(vPicture, vNegative);
		_mm256_store_ps(&picture[i], vResult);
	}

	for (; i < size; i++) {
		picture[i] = abs(picture[i]);
	}
}