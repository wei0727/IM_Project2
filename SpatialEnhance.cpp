#include "SpatialEnhance.h"

vector<int> computeHistogram(IplImage *img){
	vector<int> h((1<<img->depth), 0) ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			h[cvGet2D(img, i, j).val[0]]++ ;
		}
	}
	return h ;
}

void drawHistogram(vector<int> &h, string window, string save){
	const int height = 300 ;
	IplImage *img = cvCreateImage(cvSize(h.size()*2+10, height), IPL_DEPTH_8U, 1) ;
	cvSetZero(img) ;
	vector<int>::iterator max = max_element(h.begin(), h.end()) ;
	CvScalar lineColor = cvScalar(255) ;
	cvLine(img, cvPoint(0, height-5), cvPoint(img->width, height-4), lineColor, 2) ;
	for(int i=0; i<h.size(); i++){
		if(h[i] == 0 )
			continue ;
		double length = (h[i]/(double)(*max))*(height-10) ;
		CvPoint p1, p2 ;
		p1 = cvPoint(2*i+1, height-5) ;
		p2 = cvPoint(2*i+1, height-length-5) ;
		cvLine(img, p1, p2, lineColor, 2) ;
	}
	cvShowImage(window.c_str(), img) ;
	if(!save.empty())
		cvSaveImage(save.c_str(), img) ;
}

IplImage* histogramEqualization(IplImage *img, vector<int> &h){
	IplImage *eImg = cvCloneImage(img) ;
	vector<int> eTable(h.size()) ;
	double ap = 0 ;
	double total = img->width * img->height ;
	for(int i=0; i<h.size(); i++){
		ap += h[i]/total ;
		eTable[i] = floor(ap*255+0.5) ;
	}
	if(eTable.back()>255)
		eTable.back() = 255 ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			CvScalar color = cvGet2D(img, i, j) ;
			color.val[0] = eTable[color.val[0]] ;
			cvSet2D(eImg, i, j, color) ;
		}
	}
	return eImg ;
}

IplImage* sumOfImage(IplImage *img1, IplImage *img2){
	if(img1->width!=img2->width || img1->height!=img2->height)
		return NULL ;
	IplImage *img = cvCreateImage(cvSize(img1->width, img1->height), IPL_DEPTH_8U, 1) ;
	cvSetZero(img) ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			CvScalar color ;
			color.val[0] = cvGet2D(img1, i, j).val[0] + cvGet2D(img2, i, j).val[0] ;
			cvSet2D(img, i, j, color) ;
		}
	}
	return img ;
}

IplImage* difOfImage(IplImage *img1, IplImage *img2){
	if(img1->width!=img2->width || img1->height!=img2->height)
		return NULL ;
	IplImage *img = cvCreateImage(cvSize(img1->width, img1->height), IPL_DEPTH_8U, 1) ;
	cvSetZero(img) ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			CvScalar color ;
			color.val[0] = abs(cvGet2D(img1, i, j).val[0] - cvGet2D(img2, i, j).val[0]) ;
			cvSet2D(img, i, j, color) ;
		}
	}
	return img ;
}

IplImage* productOfImage(IplImage *img1, IplImage *img2){
	if(img1->width!=img2->width || img1->height!=img2->height)
		return NULL ;
	IplImage *img = cvCreateImage(cvSize(img1->width, img1->height), IPL_DEPTH_8U, 1) ;
	cvSetZero(img) ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			//double c1 = cvGetReal2D(img1, i, j) ;
			//double c2 = cvGetReal2D(img2, i, j) ;
			double color = ((cvGetReal2D(img1, i, j)/255) * (cvGetReal2D(img2, i, j)/255))*255 ;
			cvSetReal2D(img, i, j, color) ;
		}
	}
	return img ;
}

IplImage* applyMask(IplImage *img, Mat mask, bool rescale){
	mask.convertTo(mask, CV_32FC1) ;
	int paddingSize = floor(mask.rows/2.0) ;
	Mat matImgExp = Mat::zeros(img->height+paddingSize*2, img->width+paddingSize*2, CV_8UC1) ;
	Mat(img).copyTo(matImgExp(cvRect(paddingSize, paddingSize, img->width, img->height))) ;
	IplImage *dst = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels) ;
	cvSetZero(dst) ;
	Mat subImg ;
	vector< vector<double> > tmp(img->height, vector<double>(img->width, 0)) ;
	double max, min ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			subImg = matImgExp(cvRect(j, i, mask.cols, mask.rows)) ;
			double result = 0 ;
			for(int x=0; x<mask.rows; x++){
				for(int y=0; y<mask.cols; y++){
					result += mask.at<float>(x, y) * (int)subImg.at<unsigned char>(x, y) ;
				}
			}
			tmp[i][j] = result ;
			if(i==0 && j==0){
				max = result ;
				min = result ;
			}
			else{
				max = result>max? result: max ;
				min = result<min? result: min ;
			}
		}
	}
	if(rescale){
		double range = max - min ;
		for(int i=0; i<img->height; i++){
			for(int j=0; j<img->width; j++){
				double color = (tmp[i][j]-min)/range ;
				//cvSetReal2D(dst, i, j, color) ;
				cvSet2D(dst, i, j, cvScalar((int)(color*255))) ;
			}
		}
	}
	else{
		for(int i=0; i<img->height; i++){
			for(int j=0; j<img->width; j++){
				double color = floor(tmp[i][j]+0.5) ;
				if(color < 0)
					color = 0;
				else if(color > 255)
					color = 255 ;
				cvSet2D(dst, i, j, cvScalar(color)) ;
			}
		}
	}
	return dst ;
}

IplImage* laplacianFilter(IplImage *img1, int type, bool rescale){
	Mat mask ;
	if(type == 0){
		mask = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0) ;
	}
	else{
		mask = (Mat_<int>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1) ;
	}
	return applyMask(img1, mask, rescale) ;
}

IplImage* sobelFilter(IplImage *img, bool rescale){
	Mat mask_x, mask_y ;
	mask_x = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1 ,2 ,1) ;
	mask_y = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1) ;
	return sumOfImage(applyMask(img, mask_x, rescale), applyMask(img, mask_y, rescale)) ;
}

IplImage* avgFilter(IplImage *img, int mask_size){
	if((mask_size%2!=1) || mask_size<3)
		mask_size = 3 ;
	Mat mask = Mat::ones(mask_size, mask_size, CV_32F)/(mask_size*mask_size) ;
	return applyMask(img, mask) ;
}

IplImage* powerLawTransformation(IplImage *img, double gamma, double c){
	IplImage *dst = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels) ;
	cvSetZero(dst) ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			double color = c*pow(cvGetReal2D(img, i, j), gamma) ;
			cvSetReal2D(dst, i, j, color) ;
		}
	}
	return dst ;
}

IplImage* medianFilter(IplImage *img, int mask_size){
	if((mask_size%2!=1) || mask_size<3)
		mask_size = 3 ;
	int paddingSize = floor(mask_size/2.0) ;
	Mat matImgExp = Mat::zeros(img->height+paddingSize*2, img->width+paddingSize*2, CV_8UC1) ;
	Mat(img).copyTo(matImgExp(cvRect(paddingSize, paddingSize, img->width, img->height))) ;
	IplImage *dst = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels) ;
	cvSetZero(dst) ;
	Mat subImg ;
	for(int i=0; i<img->height; i++){
		for(int j=0; j<img->width; j++){
			subImg = matImgExp(cvRect(j, i, mask_size, mask_size)) ;
			vector<int> tmpArr ;
			for(int x=0; x<mask_size; x++){
				for(int y=0; y<mask_size; y++){
					tmpArr.push_back((int)subImg.at<unsigned char>(x, y)) ;
				}
			}
			sort(tmpArr.begin(), tmpArr.end()) ;
			cvSetReal2D(dst, i, j, tmpArr[((mask_size*mask_size)-1)/2]) ;
		}
	}
	return dst ;
}