#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp> 
#include "facedetect-dll.h"//»À¡≥ºÏ≤‚


using namespace std;
using namespace cv;
#define DETECT_BUFFER_SIZE 0x20000


vector<Point2f> FaceDetect(Mat& frame);
bool calcSafeRect(cv::Rect& roi_rect, Mat& src);