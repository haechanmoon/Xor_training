#include <stdio.h>
#include "MLP.h"
CMLP MultiLayer;
#define MAX_EPOCH 1000000


int main() {
	printf("20201544_문해찬\n");
	int n;
	int epoch;
	int HiddenNodes[2] = { 3,2 };
	int numofHiddenLayer = 2;
	MultiLayer.Create(2, HiddenNodes, 1, numofHiddenLayer);

	MultiLayer.LoadWeight((char*)"weight.txt");

	int input[4][2] = { {0.0},{0,1},{1,0},{1,1} };
	int danswer[4] = { 0,1,1,0 };

	// 입력과 현재의 출력값 계산
	for (n = 0;n < 4;n++) {
		MultiLayer.pInValue[1] = input[n][0];
		MultiLayer.pInValue[2] = input[n][1];
		MultiLayer.Forward();
		printf("%lf %lf=%lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);

	}
	printf("\n");
	getchar();

	double MSE;
	printf("***********학습시작*************");
	for (epoch = 0;epoch < MAX_EPOCH;epoch++) {
		MSE = 0.0;
		for (n = 0;n < 4;n++) {
			MultiLayer.pInValue[1] = input[n][0]; //입력전달
			MultiLayer.pInValue[2] = input[n][1]; //입력전달
			MultiLayer.pCorrectOutValue[1] = danswer[n]; //정답

			MultiLayer.Forward(); //출력계산
			MultiLayer.BackPropagationLearning(); //학습-가중치갱신

			//갱신후에 에러값 계산
			MultiLayer.Forward(); //갱신 이후 출력 계산
			MSE += (MultiLayer.pCorrectOutValue[1] - MultiLayer.pOutValue[1]) 
				* (MultiLayer.pCorrectOutValue[1] - MultiLayer.pOutValue[1]);
		}
		MSE /= 4; //평균값 계산
		printf("Epoch%d(MSE)=%lf\n", epoch, MSE);
		if (MSE < 0.000001)
			break;
	}
	printf("********학습종료*********\n");

	MultiLayer.SaveWeight((char*)"weight.txt");
	// 입력과 현재의 출력값 계산
	for (n = 0;n < 4;n++) {
		MultiLayer.pInValue[1] = input[n][0];
		MultiLayer.pInValue[2] = input[n][1];
		MultiLayer.Forward();
		printf("%lf %lf=%lf\n", MultiLayer.pInValue[1], MultiLayer.pInValue[2], MultiLayer.pOutValue[1]);

	}
	printf("20201544_문해찬\n");

	return 0;
}