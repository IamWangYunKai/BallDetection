#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

namespace {
	int iLowH = 0;
	int iHighH = 65;
	int iLowS = 65;
	int iHighS = 255;
	int iLowV = 0;
	int iHighV = 255;
}

int main(){
	VideoCapture cap("Ball.mp4");
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	Mat imgOriginal;

	while (true) {
		bool isReading = cap.read(imgOriginal);
		if (!isReading) {
			cout << "Read over" << endl;
			break;
		}
		Mat imgHSV;
		vector<Mat> hsvSplit;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);//Convert the captured frame from BGR to HSV

		split(imgHSV, hsvSplit);
		equalizeHist(hsvSplit[2], hsvSplit[2]);
		merge(hsvSplit, imgHSV);
		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//开操作 (去除一些噪点)
		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
		//闭操作 (连接一些连通域
		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
		imshow("Thresholded Image", imgThresholded);
		imshow("Original Image", imgOriginal);
		char key = (char)waitKey(10);
		if (key == 27) break;
	}
	return 0;
}