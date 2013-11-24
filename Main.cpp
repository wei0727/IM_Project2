#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "SpatialEnhance.h"
using namespace std;
using namespace cv;

int main(){
	IplImage *inputImg, *eImg, *laplacianImg, *sobelImg, *finalImg ;
	vector<int> h, eh ;
	inputImg = cvLoadImage("Fig0343(a)(skeleton_orig).tif", CV_LOAD_IMAGE_GRAYSCALE) ;
	h = computeHistogram(inputImg) ;
	eImg = histogramEqualization(inputImg, h) ;
	eh = computeHistogram(eImg) ;
	laplacianImg = laplacianFilter(inputImg, 1) ;
	sobelImg = sobelFilter(inputImg) ;
	sobelImg = avgFilter(sobelImg, 5) ;
	finalImg = sumOfImage(inputImg, sobelImg) ;
	finalImg = sumOfImage(inputImg, laplacianImg) ;
	//finalImg = productOfImage(finalImg, sobelImg) ;
	//finalImg = histogramEqualization(finalImg, computeHistogram(finalImg)) ;
	//finalImg = sumOfImage(finalImg, inputImg) ;
	finalImg = powerLawTransformation(finalImg, 1.2) ;
	cvNamedWindow("inputImage") ;
	cvShowImage("inputImage", inputImg) ;
	cvNamedWindow("sobelImg") ;
	cvShowImage("sobelImg", sobelImg) ;
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