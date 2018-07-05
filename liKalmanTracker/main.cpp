
#include "liFunction.h"
#include "liKalmanTracker.h"
#include "face_detect.h"

int main()
{	
	liKalmanTracker tracker(40, "face");
	cv::VideoCapture cap(0);
	int nFrameCount = 1;
	Mat src;
	vector<vector<Point2f>::const_iterator> trajectory;
	while (true)
	{
		cap >> src;

		vector<Point2f> dets = FaceDetect(src);
		vector<Point2f> measurement = liCorrectDetection(dets,/* ROI,*/ tracker.size);	

		tracker.track(measurement);
		tracker.print(nFrameCount);
		src = tracker.show(src, 0, trajectory);
		namedWindow("Tracking", CV_WINDOW_AUTOSIZE);
		imshow("Tracking", src);

		//Video Control
		int nKey = waitKey(50);
		if (nKey == 27)	break;
		if (nKey == 32)
		{
			cout << "Pause." << endl;
			nKey = waitKey();
			if (nKey == 27)	break;
		}
	}
	
	return 1;
}
