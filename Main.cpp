#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "SpatialEnhance.h"
using namespace std;
using namespace cv;

void imgEnhanceExampleRoutine(string img){
	IplImage *inputImg, *laplacianImg, *sobelImg, *finalImg ;
	inputImg = cvLoadImage(img.c_str(), CV_LOAD_IMAGE_GRAYSCALE) ;
	laplacianImg = laplacianFilter(inputImg, 1) ;
	cvSaveImage("b.jpg", laplacianImg) ;
	finalImg = sumOfImage(inputImg, laplacianImg) ;
	cvSaveImage("c.jpg", finalImg) ;
	sobelImg = sobelFilter(inputImg) ;
	cvSaveImage("d.jpg", sobelImg) ;
	sobelImg = avgFilter(sobelImg, 5) ;
	cvSaveImage("e.jpg", sobelImg) ;
	finalImg = productOfImage(finalImg, sobelImg) ;
	cvSaveImage("f.jpg", finalImg) ;
	finalImg = sumOfImage(finalImg, inputImg) ;
	cvSaveImage("g.jpg", finalImg) ;
	finalImg = powerLawTransformation(finalImg, 1.15) ;
	cvSaveImage("h.jpg", finalImg) ;
}

int main(){
	IplImage *inputImg, *eImg, *laplacianImg, *sobelImg, *finalImg ;
	vector<int> h, eh ;
	//imgEnhanceExampleRoutine("Fig0343(a)(skeleton_orig).tif") ;
	inputImg = cvLoadImage("Fig0333(a)(test_pattern_blurring_orig).tif", CV_LOAD_IMAGE_GRAYSCALE) ;
	finalImg = avgFilter(inputImg, 35) ;
	cvNamedWindow("inputImage") ;
	cvShowImage("inputImage", inputImg) ;
	//cvNamedWindow("sobelImg") ;
	//cvShowImage("sobelImg", sobelImg) ;
	cvNamedWindow("finalImage") ;
	cvShowImage("finalImage", finalImg) ;
	//cvNamedWindow("inputHistogram") ;
	//drawHistogram(h, "inputHistogram") ;
	//cvNamedWindow("outputImage") ;
	//cvShowImage("outputImage", eImg) ;
	//cvNamedWindow("outputHistogram") ;
	//drawHistogram(eh, "outputHistogram") ;
	cvWaitKey(0) ;
	cvDestroyAllWindows() ;
	return 0;
}