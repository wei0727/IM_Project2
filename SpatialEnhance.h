#include <vector>
#include <cmath>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

//�p��img��Histogram �^�ǰ}�C
vector<int> computeHistogram(IplImage *img) ;

//�e�XHistogram h���έp��
void drawHistogram(vector<int> &h, string window) ;

//�z�L��ϥH��Histogram�i��equalization �^�ǵ��G�Ϥ�
IplImage* histogramEqualization(IplImage *img, vector<int> &h) ;

//sum of two image
IplImage* sumOfImage(IplImage *img1, IplImage *img2) ;

//product of two image
IplImage* productOfImage(IplImage *img1, IplImage *img2) ;

//Power-Law transformation
IplImage* powerLawTransformation(IplImage *img, double gamma, double c=1) ;

//Average Filter smoooth
IplImage* avgFilter(IplImage *img, int mask_size) ;

//Median Filter smooth
//Laplacian Filter sharpe
IplImage* laplacianFilter(IplImage *img1, int type, bool rescale=false) ;

//Sobel Filter sharpe
IplImage* sobelFilter(IplImage *img, bool rescale=false) ;

//compute image with mask
IplImage* applyMask(IplImage *img, Mat mask, bool rescale=false) ;