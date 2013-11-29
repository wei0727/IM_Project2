#include <vector>
#include <cmath>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

//計算img的Histogram 回傳陣列
vector<int> computeHistogram(IplImage *img) ;

//畫出Histogram h的統計圖
void drawHistogram(vector<int> &h, string window, string save="") ;

//透過原圖以及Histogram進行equalization 回傳結果圖片
IplImage* histogramEqualization(IplImage *img, vector<int> &h) ;

//sum of two image, rescale決定是否要將結果值rescale到0~255 避免過大或過小的數值造成誤差
IplImage* sumOfImage(IplImage *img1, IplImage *img2, bool rescale=false) ;

//difference of two image
IplImage* difOfImage(IplImage *img1, IplImage *img2) ;

//product of two image
IplImage* productOfImage(IplImage *img1, IplImage *img2) ;

//Power-Law transformation rescale決定是否要將數值scale到0~1之間再做運算
IplImage* powerLawTransformation(IplImage *img, double gamma, double c=1, bool rescale=false) ;

//Average Filter smoooth
IplImage* avgFilter(IplImage *img, int mask_size) ;

//Median Filter smooth
IplImage* medianFilter(IplImage *img, int mask_size) ;

//Laplacian Filter sharpe, type決定laplacian的mask種類
IplImage* laplacianFilter(IplImage *img1, int type, bool rescale=false) ;

//Sobel Filter sharpe
//結果為直接相加
IplImage* sobelFilter(IplImage *img, bool rescale=false) ;
//結果為平方相加開根號
IplImage* sobelFilter_euclidean(IplImage *img, bool rescale=false) ;

//compute image with mask
IplImage* applyMask(IplImage *img, Mat mask, bool rescale=false) ;