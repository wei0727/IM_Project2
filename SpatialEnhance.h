#include <vector>
#include <cmath>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

//�p��img��Histogram �^�ǰ}�C
vector<int> computeHistogram(IplImage *img) ;

//�e�XHistogram h���έp��
void drawHistogram(vector<int> &h, string window, string save="") ;

//�z�L��ϥH��Histogram�i��equalization �^�ǵ��G�Ϥ�
IplImage* histogramEqualization(IplImage *img, vector<int> &h) ;

//sum of two image, rescale�M�w�O�_�n�N���G��rescale��0~255 �קK�L�j�ιL�p���ƭȳy���~�t
IplImage* sumOfImage(IplImage *img1, IplImage *img2, bool rescale=false) ;

//difference of two image
IplImage* difOfImage(IplImage *img1, IplImage *img2) ;

//product of two image
IplImage* productOfImage(IplImage *img1, IplImage *img2) ;

//Power-Law transformation rescale�M�w�O�_�n�N�ƭ�scale��0~1�����A���B��
IplImage* powerLawTransformation(IplImage *img, double gamma, double c=1, bool rescale=false) ;

//Average Filter smoooth
IplImage* avgFilter(IplImage *img, int mask_size) ;

//Median Filter smooth
IplImage* medianFilter(IplImage *img, int mask_size) ;

//Laplacian Filter sharpe, type�M�wlaplacian��mask����
IplImage* laplacianFilter(IplImage *img1, int type, bool rescale=false) ;

//Sobel Filter sharpe
//���G�������ۥ[
IplImage* sobelFilter(IplImage *img, bool rescale=false) ;
//���G������ۥ[�}�ڸ�
IplImage* sobelFilter_euclidean(IplImage *img, bool rescale=false) ;

//compute image with mask
IplImage* applyMask(IplImage *img, Mat mask, bool rescale=false) ;