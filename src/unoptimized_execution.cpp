#include <vector>
#include "operation.h"

using namespace std;

extern vector<pair<operation_types, int>*> to_do;
extern vector<vector<vector<float>>> filter_matrix;

void add_unoptimized(vector<float>& picture, float param);
void sub_unoptimized(vector<float>& picture, float param);
void isub_unoptimized(vector<float>& picture, float param);
void mul_unoptimized(vector<float>& picture, float param);
void div_unoptimized(vector<float>& picture, float param);
void idiv_unoptimized(vector<float>& picture, float param);

void pow_unoptimized(vector<float>& picture, float param);
void log_unoptimized(vector<float>& picture, float param);
void abs_unoptimized(vector<float>& picture);
void min_unoptimized(vector<float>& picture, float param);
void max_unoptimized(vector<float>& picture, float param);

void inv_unoptimized(vector<float>& picture);
void gray_unoptimized(vector<float>& picture);

void filter_unoptimized(vector<float>& inputPicture, int height, int width, vector<vector<float>>& filter);

void unoptimized_execution(vector<float>& picture, int heigth, int width) {
	for (int i = 0; i < to_do.size(); i++) {
		operation_types myOperation = to_do[i]->first;
		int myParam = to_do[i]->second;

		switch (myOperation)
		{
		case(ADD):
			add_unoptimized(picture, (float)myParam);
			break;
		case(SUB):
			sub_unoptimized(picture, (float)myParam);
			break;
		case(ISUB):
			isub_unoptimized(picture, (float)myParam);
			break;
		case(MUL):
			mul_unoptimized(picture, myParam);
			break;
		case(DIV):
			div_unoptimized(picture, myParam);
			break;
		case(IDIV):
			idiv_unoptimized(picture, myParam);
			break;

		case(POW):
			pow_unoptimized(picture, myParam);
			break;
		case(LOG):
			log_unoptimized(picture, myParam);
			break;
		case(ABS):
			abs_unoptimized(picture);
			break;
		case(MIN):
			min_unoptimized(picture, (float)myParam);
			break;
		case(MAX):
			max_unoptimized(picture, (float)myParam);
			break;

		case(INV):
			inv_unoptimized(picture);
			break;
		case(GRAY):
			gray_unoptimized(picture);
			break;

		case(FILTER):
			filter_unoptimized(picture, heigth, width, filter_matrix[myParam]);
			break;
		default:
			break;
		}
	}
}
