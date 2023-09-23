#include <immintrin.h>
#include <emmintrin.h>
#include <vector>
#include "Cache.h"

using namespace std;


void filter_unoptimized(vector<float>& inputPicture, int height, int width, vector<vector<float>>& filter) {
	int radius = filter.size() / 2;
	vector<float> outputPicture(inputPicture.size(), 0);
	for (int i = radius; i < height - radius; i ++) {
		for (int j = radius; j < width - radius; j++) {
			int id = i * width * 3 + j * 3;
			float accB = 0.0f;
			float accG = 0.0f;
			float accR = 0.0f;
			for (int ki = 0; ki < filter.size(); ki++) {
				for (int kj = 0; kj < filter[0].size(); kj++) {
					int idd = id + (ki - radius) * width * 3 + (kj - radius) * 3;
					accB += inputPicture[idd] * filter[ki][kj];
					accG += inputPicture[idd + 1] * filter[ki][kj];
					accR += inputPicture[idd + 2] * filter[ki][kj];
				}
			}
			outputPicture[id] = accB;
			outputPicture[id + 1] = accG;
			outputPicture[id + 2] = accR;
		}
	}
	inputPicture = outputPicture;
}

void filter_optimized(vector<float>& inputPicture, int height, int width, vector<vector<float>>& filter) {
	int radius = filter.size() / 2;
	vector<float> outputPicture(inputPicture.size());
	int idd = 0, id = 0;
	int n = filter.size();

	for (int i = radius; i < height - radius; i++) {
		for (int j = radius; j < width - radius; j++) {
			id = i * width * 3 + j * 3;
			float accB = 0.0f;
			float accG = 0.0f;
			float accR = 0.0f;
			float arrB[8];
			float arrG[8];
			float arrR[8];
			float arrF[8];

			__m256 vResultR = _mm256_set1_ps(0);
			__m256 vResultG = _mm256_set1_ps(0);
			__m256 vResultB = _mm256_set1_ps(0);

			int ki = 0, kj = 0, arrId = 0;
			for (ki = 0; ki < n ; ki++) {
				for (kj = 0; kj < n; kj++) {
					idd = id + (ki - radius) * width * 3 + (kj - radius) * 3;
					arrB[arrId] = inputPicture[idd];
					arrG[arrId] = inputPicture[idd + 1];
					arrR[arrId] = inputPicture[idd + 2];
					arrF[arrId] = filter[kj][kj];

					arrId = (arrId + 1) % 8;
					if (arrId == 0) {

						__m256 vR = _mm256_load_ps(arrR);
						__m256 vG = _mm256_load_ps(arrG);
						__m256 vB = _mm256_load_ps(arrB);
						__m256 vF = _mm256_load_ps(arrF);

						vR = _mm256_mul_ps(vR, vF);
						vG = _mm256_mul_ps(vG, vF);
						vB = _mm256_mul_ps(vB, vF);

						vResultR = _mm256_add_ps(vResultR, vR);
						vResultG = _mm256_add_ps(vResultG, vG);
						vResultB = _mm256_add_ps(vResultB, vB);
					}
				}
			}

			_mm256_store_ps(arrR, vResultR);
			_mm256_store_ps(arrG, vResultG);
			_mm256_store_ps(arrB, vResultB);

			for (int xi = 0; xi < 8; xi++) {
				accR += arrR[xi];
				accG += arrG[xi];
				accB += arrB[xi];
			}

			if (ki == n) ki -= 1;
			//for (; ki < n * n; ki++) {
				for (kj = kj - arrId; kj < n; kj++) {
					idd = id + (ki - radius) * width * 3 + (kj - radius) * 3;
					accB += inputPicture[idd] * filter[ki][kj];
					accG += inputPicture[idd + 1] * filter[ki][kj];
					accR += inputPicture[idd + 2] * filter[ki][kj];
				}
			//}

			outputPicture[id] = accB;
			outputPicture[id + 1] = accG;
			outputPicture[id + 2] = accR;
		}
	}
	inputPicture = outputPicture;
}

/*
void filter_optimized(vector<float>& inputPicture, int height, int width, vector<vector<float>>& filter) {
	int radius = filter.size() / 2;
	vector<float> outputPicture(inputPicture.size());

	int cacheEntries = (Cache::cacheSize - filter.size() * filter[0].size() * sizeof(float)) / Cache::cacheLine - 3;
	if (cacheEntries == 0) cacheEntries = 1;
	int elemPerLine = Cache::cacheLine / sizeof(float);

	int stepW = width; // elemPerLine / Cache::cacheAssociativity;
	int stepH = height; // cacheEntries / 3 * Cache::cacheAssociativity;

	for (int oi = radius; oi < height - radius; oi += stepH) {
		for (int oj = radius; oj < width - radius; oj += stepW) {
			for (int i = oi; i < oi + stepH && i < height - radius; i++) {
				for (int j = oj; j < oj + stepW && j < width - radius; j++) {
					int id = i * width * 3 + j * 3;
					float accB = 0.0f;
					float accG = 0.0f;
					float accR = 0.0f;
					for (int ki = 0; ki < filter.size(); ki++) {
						for (int kj = 0; kj < filter[0].size(); kj++) {
							int idd = id + (ki - radius) * width * 3 + (kj - radius) * 3;
							accB += inputPicture[idd] * filter[ki][kj];
							accG += inputPicture[idd + 1] * filter[ki][kj];
							accR += inputPicture[idd + 2] * filter[ki][kj];
						}
					}
					outputPicture[id] = accB;
					outputPicture[id + 1] = accG;
					outputPicture[id + 2] = accR;
				}
			}
		}
	}
	inputPicture = outputPicture;
} */