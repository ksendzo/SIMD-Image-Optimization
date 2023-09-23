#include <immintrin.h>
#include <vector>

using namespace std;

void inv_unoptimized(vector<float>& picture) {
	for (int i = 0; i < picture.size(); i++) {
		picture[i] = 255.0f - picture[i];
	}
}

void inv_optimized(vector<float>& picture) {
	int size = picture.size();
	__m256 vParam = _mm256_set1_ps(255.0f);

	size_t i = 0;
	for (; i <= size - 8; i += 8) {
		__m256 vPicture = _mm256_load_ps((&picture[i]));
		__m256 vResult = _mm256_sub_ps(vParam, vPicture);
		_mm256_store_ps(&picture[i], vResult);
	}

	for (; i < size; i++) {
		picture[i] = 255.0f - picture[i];
	}
}