/************************************************************/
/*  File Name: liFunction.cpp								*/
/*  Description: Functions used in the program.				*/
/*  Author: Haozheng Li										*/
/*  EMail: 466739850@qq.com									*/
/************************************************************/

#include "liFunction.h"

float liDistance(Point2f pt1, Point2f pt2)
{
	float s1 = pow(pt1.x - pt2.x, 2);
	float s2 = pow(pt1.y - pt2.y, 2);
	float dist = sqrt(s1 + s2);

	return dist;
}

Point2f liMean(Point2f pt1, Point2f pt2)
{
	Point2f pt(pt1.x / 2 + pt2.x / 2, pt1.y / 2 + pt2.y / 2);

	return pt;
}

vector<Point2f> liCorrectDetection(vector<Point2f> pt/*, Rect roi注释掉roi区域，如果为了划分检测区域可释放*/, float dist_T)
{
	vector<Point2f> pt_c;
	for (vector<Point2f>::iterator p = pt.begin(); p != pt.end(); p++)
	{
		/*if (p->x > roi.x && p->x < roi.x + roi.width && p->y > roi.y && p->y < roi.y + roi.height)
		{*/
			vector<Point2f>::iterator q = p + 1;
			for (; q != pt.end(); q++)
			{
				float dist = liDistance(*p, *q);
				if (dist < dist_T)
				{
					*q = liMean(*p, *q);
					break;
				}
			}

			if (q == pt.end())
			{
				pt_c.push_back(*p);
			}
		//}
	}

	return pt_c;
}

Mat liPointToMat(Point2f pt)
{
	Mat pt_m = *(Mat_<float>(2, 1) << pt.x, pt.y);

	return pt_m;
}

Point2f liMatToPoint(Mat pt)
{
	Point2f pt_p(0, 0);
	
	if (pt.rows == 2 && pt.cols == 1)
	{
		pt_p.x = pt.at<float>(0);
		pt_p.y = pt.at<float>(1);
	}

	return pt_p;
}