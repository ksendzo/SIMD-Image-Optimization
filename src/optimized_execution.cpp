#include <vector>
#include "operation.h"

using namespace std;

extern vector<pair<operation_types, int>*> to_do;
extern vector<vector<vector<float>>> filter_matrix;

void add_optimized(vector<float>& picture, float param);
void sub_optimized(vector<float>& picture, float param);
void isub_optimized(vector<float>& picture, float param);
void mul_optimized(vector<float>& picture, float param);
void div_optimized(vector<float>& picture, float param);
void idiv_optimized(vector<float>& picture, float param);

void pow_optimized(vector<float>& picture, float param);
void log_optimized(vector<float>& picture, float param);
void abs_optimized(vector<float>& picture);
void min_optimized(vector<float>& picture, float param);
void max_optimized(vector<float>& picture, float param);

void inv_optimized(vector<float>& picture);
void gray_optimized(vector<float>& picture);

void filter_optimized(vector<float>& inputPicture, int height, int width, vector<vector<float>>& filter);

void optimized_execution(vector<float> &picture, int heigth, int width) {
	for (int i = 0; i < to_do.size(); i++) {
		operation_types myOperation = to_do[i]->first;
		int myParam = to_do[i]->second;

		switch (myOperation)
		{
		case(ADD): 
			add_optimized(picture,(float) myParam);
			break;
		case(SUB):
			sub_optimized(picture, (float)myParam);
			break;
		case(ISUB):
			isub_optimized(picture, (float)myParam);
			break;
		case(MUL):
			mul_optimized(picture, myParam);
			break;
		case(DIV):
			div_optimized(picture, myParam);
			break;
		case(IDIV):
			idiv_optimized(picture, myParam);
			break;

		case(POW):
			pow_optimized(picture, myParam);
			break;
		case(LOG):
			log_optimized(picture, myParam);
			break;
		case(ABS):
			abs_optimized(picture);
			break;
		case(MIN):
			min_optimized(picture, (float)myParam);
			break;
		case(MAX):
			max_optimized(picture, (float)myParam);
			break;

		case(INV):
			inv_optimized(picture);
			break; 
		case(GRAY):
			gray_optimized(picture);
			break;

		case(FILTER):
			filter_optimized(picture, heigth, width, filter_matrix[myParam]);
			break;
		default:
			break;
		}
	}
}
