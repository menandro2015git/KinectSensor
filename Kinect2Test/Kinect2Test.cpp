#include <opencv2/opencv.hpp>
#include "KinectSensor.h"
#include "liblink.h"

int test_Kinect() {
	KinectSensor *stream = new KinectSensor();
	stream->open(stream->INFRAREDINDEX);
	cv::Mat infraredMat;
	std::cout << stream->infraredHeight << ":" << stream->infraredWidth << std::endl;
	for (;;) {
		//if (i1rgb.empty()) break; // end of video stream
		char pressed = cv::waitKey(10);
		if (pressed == 27) break; //press escape

		if (!stream->read(stream->INFRAREDINDEX)) {
			cv::imshow("Kinect IR", stream->infraredMat);
		}
		//infraredMat = cv::Mat(stream->infraredHeight, stream->infraredWidth, CV_16S, &stream->infraredBuffer);
	}
	stream->close();
	cv::waitKey();
	return 0;
}

int test_KinectDepth() {
	KinectSensor *stream = new KinectSensor();
	stream->open(stream->DEPTHINDEX);
	//std::cout << stream->depthHeight << ":" << stream->depthWidth << std::endl;
	cv::Mat depthMat;
	std::cout << "Waiting for Depth Stream...";
	while (stream->read(stream->DEPTHINDEX)); //Wait for stream start
	std::cout << "FOUND!" << std::endl;
	for (;;) {
		//if (i1rgb.empty()) break; // end of video stream
		char pressed = cv::waitKey(10);
		if (pressed == 27) break; //press escape

		if (!stream->read(stream->DEPTHINDEX)) {
			depthMat = 65536 - stream->depthMat * 10;
			cv::imshow("Kinect Depth", depthMat);;
		}
	}
	//stream->getDepthCameraIntrinsics();
	stream->close();
	cv::waitKey();
	return 0;
}

int main(int argc, char **argv)
{
	//test_KinectDepth();
	test_Kinect();
	return 0;
}