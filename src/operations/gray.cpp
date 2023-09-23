#include <immintrin.h>
#include <emmintrin.h>
#include <vector>

using namespace std;

void gray_unoptimized(vector<float>& picture) {
	for (int i = 0; i + 2 < picture.size(); i += 3) {
		float gray = picture[i] * 0.114f + picture[i + 1] * 0.587f + picture[i + 2] * 0.299f;
		picture[i] = picture[i+1] = picture[i+2] = gray;
	}
}

void gray_optimized(vector<float>& picture) {
	int size = picture.size();
	__m256 vParamB = _mm256_set1_ps(0.114f);
	__m256 vParamG = _mm256_set1_ps(0.587f);
	__m256 vParamR = _mm256_set1_ps(0.299f);

	float results[8];

	size_t i = 0;
	for (; i <= size - 24; i += 24) {
		__m256 vPictureB = _mm256_set_ps(picture[i + 0], picture[i + 3], picture[i + 6], picture[i + 9], picture[i + 12], picture[i + 15], picture[i + 18], picture[i + 21]);
		__m256 vPictureG = _mm256_set_ps(picture[i + 1], picture[i + 4], picture[i + 7], picture[i + 10], picture[i + 13], picture[i + 16], picture[i + 19], picture[i + 22]);
		__m256 vPictureR = _mm256_set_ps(picture[i + 2], picture[i + 5], picture[i + 8], picture[i + 11], picture[i + 14], picture[i + 17], picture[i + 20], picture[i + 23]);

		__m256 vResultB = _mm256_mul_ps(vPictureB, vParamB);
		__m256 vResultG = _mm256_mul_ps(vPictureG, vParamG);
		__m256 vResultR = _mm256_mul_ps(vPictureR, vParamR);

		__m256 vResult = _mm256_add_ps(_mm256_add_ps(vResultB, vResultG), vResultR);

		_mm256_store_ps(results, vResult);
		for (int k = 0; k < 8; k++) {
			picture[i + k * 3 + 0] = results[7-k];
			picture[i + k * 3 + 1] = results[7-k];
			picture[i + k * 3 + 2] = results[7-k];
		}
	}

	for (; i < size; i += 3) {
		float gray = picture[i] * 0.114f + picture[i + 1] * 0.587f + picture[i + 2] * 0.299f;
		picture[i] = picture[i + 1] = picture[i + 2] = gray;
	}
}