#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "SpatialEnhance.h"
using namespace std;
using namespace cv;

void imgHistogramRoutine(string img){
	IplImage *inputImg, *outputImg ;
	vector<int> inputH, outputH ;
	inputImg = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_GRAYSCALE) ;
	inputH = computeHistogram(inputImg) ;
	outputImg = histogramEqualization(inputImg, inputH) ;
	outputH = computeHistogram(outputImg) ;
	cvShowImage("input", inputImg) ;
	cvSaveImage("h_input.jpg", inputImg) ;
	cvShowImage("output", outputImg) ;
	cvSaveImage("h_output.jpg", outputImg) ;
	drawHistogram(inputH, "inputHistogram", "h_input_histogram.jpg") ;
	drawHistogram(outputH, "outputHistogram", "h_output_histogram.jpg") ;
}

void imgEnhanceExampleRoutine(string img){
	IplImage *inputImg, *laplacianImg, *sobelImg, *finalImg ;
	inputImg = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_GRAYSCALE) ;
	laplacianImg = laplacianFilter(inputImg, 1) ;
	cvSaveImage("example_b.jpg", laplacianImg) ;
	finalImg = sumOfImage(inputImg, laplacianImg) ;
	cvSaveImage("example_c.jpg", finalImg) ;
	sobelImg = sobelFilter(inputImg) ;
	cvSaveImage("example_d.jpg", sobelImg) ;
	sobelImg = avgFilter(sobelImg, 5) ;
	cvSaveImage("example_e.jpg", sobelImg) ;
	finalImg = productOfImage(finalImg, sobelImg) ;
	cvSaveImage("example_f.jpg", finalImg) ;
	finalImg = sumOfImage(finalImg, inputImg) ;
	cvSaveImage("example_g.jpg", finalImg) ;
	finalImg = powerLawTransformation(finalImg, 1.15) ;
	cvSaveImage("example_h.jpg", finalImg) ;
}

void imgEnhanceCustomRoutine_1(string img){
	IplImage *inputImg, *laplacianImg, *sobel, *result ;
	inputImg = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_GRAYSCALE) ;
	laplacianImg = laplacianFilter(inputImg, 1) ;
	cvSaveImage("custom_1_b.jpg", laplacianImg) ;
	sobel = sobelFilter(inputImg) ;
	cvSaveImage("custom_1_c.jpg", sobel) ;
	sobel = avgFilter(sobel, 3) ;
	result = sumOfImage(inputImg, laplacianImg) ;
	cvSaveImage("custom_1_d.jpg", result) ;
	result = avgFilter(result, 3) ;
	cvSaveImage("custom_1_e.jpg", result) ;
	result = sumOfImage(result, sobel) ;
	result = avgFilter(result, 3) ;
	cvSaveImage("custom_1_f.jpg", result) ;
	result = powerLawTransformation(result, 1.05) ;
	cvSaveImage("custom_1_g.jpg", result) ;
	//cvShowImage("result", result) ;
	//cvSaveImage("customResult.jpg", result) ;
}

void imgEnhanceCustomRoutine_2(string img){
	IplImage *inputImg, *result, *laplacian, *sobel ;
	inputImg = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_GRAYSCALE) ;
	laplacian = laplacianFilter(inputImg, 1) ;
	//laplacian = avgFilter(laplacian, 5) ;
	cvSaveImage("custom_2_b.jpg", laplacian) ;
	sobel = sobelFilter(inputImg) ;
	cvSaveImage("custom_2_c.jpg", sobel) ;
	sobel = medianFilter(sobel, 5) ;
	//sobel = avgFilter(sobel, 5) ;
	cvSaveImage("custom_2_d.jpg", sobel) ;
	result = sumOfImage(inputImg, sobel) ;
	cvSaveImage("custom_2_e.jpg", result) ;
	result = sumOfImage(result, laplacian) ;
	cvSaveImage("custom_2_f.jpg", result) ;
	result = avgFilter(result, 5) ;
	//result = powerLawTransformation(result, 1.1) ;
	cvSaveImage("custom_2_g.jpg", result) ;
	result = sumOfImage(result, laplacian) ;
	cvSaveImage("custom_2_h.jpg", result) ;
	//cvShowImage("result", result) ;
}

int main(){
	String img ;
	int type ;
	cout << "輸入要處理的圖片檔案名稱" << endl ;
	cin >> img ;
	cout << "選擇要進行的處理" << endl ;
	cout << "1: Histogram equlization" << endl ;
	cout << "2: Example Enhancement" << endl ;
	cout << "3: Custom Enhancement_1" << endl ;
	cout << "4: Custom_Enhancement_2" << endl ;
	cin >> type ;
	switch (type)
	{
	case 1:
		imgHistogramRoutine(img) ;
		break ;
	case 2:
		cout << "結果圖將儲存為 example_b~h.jpg" << endl ;
		imgEnhanceExampleRoutine(img) ;
		break ;
	case 3:
		cout << "結果圖將儲存為 custom_1_b~g.jpg" << endl ;
		imgEnhanceCustomRoutine_1(img) ;
		break ;
	case 4:
		cout << "結果圖將儲存為 custom_2_b~h.jpg" << endl ;
		imgEnhanceCustomRoutine_2(img) ;
		break ;
	default:
		break;
	}
	cvWaitKey(0) ;
	cvDestroyAllWindows() ;
	return 0;
}