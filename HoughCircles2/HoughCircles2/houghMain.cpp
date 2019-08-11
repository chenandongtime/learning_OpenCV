/////OpenCV4.1.1+VS2017
////author :Chenandong
////time:2019.08.10
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// Loads an image
	Mat src = imread("circle7from6.png", IMREAD_COLOR);
	// Check if image is loaded fine
	if (src.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n");
		return -1;
	}
	//show the origin image
	imshow("origin image", src);
	
	//////////////HOughCircles detect
	//----------------------------------------------------------
	// change to gray image
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	
	//滤波处理
	medianBlur(gray, gray, 5);
	imshow("gray", gray);
	
	//Hough圆检测
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
		gray.rows / 8,  // change this value to detect circles with different distances to each other
		60, 25, 30, 300 // change the last two parameters
   // (min_radius & max_radius) to detect larger circles
	);
	
	//draw the circle be detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		cout << center << endl;
		// circle center
		circle(src, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(src, center, radius, Scalar(0, 100, 100), 3, LINE_AA);
	}
	
	//show the result
	imshow("detected circles", src);
	//------------------------------------------------
	
	
	waitKey();
	return 0;
}