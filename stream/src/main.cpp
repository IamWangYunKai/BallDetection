#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

mutex mtx;

template <typename T>
void change(T *p, T *q){
	T tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}

void get_video(VideoCapture &cap, Mat *latest_img, Mat *new_img) {
	while (true) {
		cap.read(*new_img);
		mtx.lock();
		change(latest_img, new_img);
		mtx.unlock();
		std::chrono::milliseconds dura(30);
		std::this_thread::sleep_for(dura);
	}
}

int main(){
	VideoCapture cap(0);
	Mat img1(Size(640,480), CV_8UC3), img2(Size(640, 480), CV_8UC3);
	Mat *latest_img, *new_img;
	latest_img = &img1;
	new_img = &img2;

	std::thread t{ get_video, cap, latest_img, new_img };
	t.detach();

	while (true) {
		imshow("Image", *latest_img);
		waitKey(10);
	}

	return 0;
}