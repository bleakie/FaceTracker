#include "face_detect.h"

vector<Point2f> FaceDetect(Mat& frame)//���Ƿ����
{
	vector<Point2f> targ;
	Mat gray;
	cvtColor(frame, gray, CV_BGR2GRAY);
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		return targ;
	}
	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step, 1.2f, 2, 50, 0, 0);
	int peopleNUM = (pResults ? *pResults : 0);//��������

	for (int i = 0; i < peopleNUM; i++)//�����м�������(pResults ? *pResults : 0)
	{
		short * p = ((short*)(pResults + 1)) + 142 * i;
		Rect opencvRect(p[0], p[1], p[2], p[3]);
		if (calcSafeRect(opencvRect, frame))
		{
			cv::rectangle(frame, opencvRect, Scalar(255, 0, 0), 2);
			Point2f pot;
			pot.x = (p[0] + p[2] / 2);
			pot.y = (p[1] + p[3] / 2);
			targ.push_back(pot);
		}
	}
	free(pBuffer);
	/*target = targ.begin();*/
	return targ;
}

bool calcSafeRect(cv::Rect& roi_rect, Mat& src)
{
	// boudRect�����ϵ�x��y�п���С��0
	float tl_x = roi_rect.x > 0 ? roi_rect.x : 0;
	float tl_y = roi_rect.y > 0 ? roi_rect.y : 0;
	// boudRect�����µ�x��y�п��ܴ���src�ķ�Χ
	float br_x = roi_rect.x + roi_rect.width < src.cols ?
		roi_rect.x + roi_rect.width - 1 : src.cols - 1;
	float br_y = roi_rect.y + roi_rect.height < src.rows ?
		roi_rect.y + roi_rect.height - 1 : src.rows - 1;

	float roi_width = br_x - tl_x;
	float roi_height = br_y - tl_y;

	if (roi_width <= 0 || roi_height <= 0)
		return false;

	// �½�һ��mat��ȷ����ַ��Խ�磬�Է�mat��λroiʱ���쳣
	roi_rect = Rect_<float>(tl_x, tl_y, roi_width, roi_height);

	return true;
}
