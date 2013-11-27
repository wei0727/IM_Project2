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
	cvShowImage("output", outputImg) ;
	drawHistogram(inputH, "inputHistogram") ;
	drawHistogram(outputH, "outputHistogram") ;
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
	cvSaveImage("custom_b.jpg", laplacianImg) ;
	sobel = sobelFilter(inputImg) ;
	cvSaveImage("custom_c.jpg", sobel) ;
	sobel = avgFilter(sobel, 3) ;
	result = sumOfImage(inputImg, laplacianImg) ;
	cvSaveImage("custom_d.jpg", result) ;
	result = avgFilter(result, 3) ;
	cvSaveImage("custom_e.jpg", result) ;
	result = sumOfImage(result, sobel) ;
	result = avgFilter(result, 3) ;
	cvSaveImage("custom_f.jpg", result) ;
	result = powerLawTransformation(result, 1.05) ;
	cvSaveImage("custom_g.jpg", result) ;
	//cvShowImage("result", result) ;
	//cvSaveImage("customResult.jpg", result) ;
}

int main(){
	IplImage *inputImg, *eImg, *laplacianImg, *sobelImg, *finalImg ;
	//imgHistogramRoutine("Fig0316(1)(top_left).tif") ;
	imgEnhanceExampleRoutine("Fig0343(a)(skeleton_orig).tif") ;
	imgEnhanceCustomRoutine_1("Fig0343(a)(skeleton_orig).tif") ;
	cvWaitKey(0) ;
	cvDestroyAllWindows() ;
	return 0;
}