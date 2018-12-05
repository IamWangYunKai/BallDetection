#include <iostream>
#include "OpenNI.h"
#include "Viewer.h"

using namespace std;

int main(int argc, char** argv)
{
	openni::Status rc = openni::STATUS_OK;

	openni::Device device;
	openni::VideoStream depth, color;
	const char* deviceURI = openni::ANY_DEVICE;
	//printf("Divce: %s\n", deviceURI);
	if (argc > 1)
	{
		deviceURI = argv[1];
	}

	rc = openni::OpenNI::initialize();

	//printf("After initialization:\n%s\n", openni::OpenNI::getExtendedError());

	rc = device.open(deviceURI);
	if (rc != openni::STATUS_OK)
	{
		printf("SimpleViewer: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 1;
	}
	////////////////////////////////////////////
	depth.getSensorInfo();
	openni::VideoMode depth_videoMode = depth.getVideoMode();
	depth_videoMode.setResolution(640, 480);
	depth_videoMode.setFps(60);
	rc = depth.setVideoMode(depth_videoMode);
	if (rc != openni::STATUS_OK){
		printf("Set depth failed:\n%s\n", openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 1;
	}

	color.getSensorInfo();
	openni::VideoMode color_videoMode = color.getVideoMode();
	color_videoMode.setResolution(640, 480);
	color_videoMode.setFps(60);
	rc = color.setVideoMode(color_videoMode);
	if (rc != openni::STATUS_OK){
		printf("Set color failed:\n%s\n", openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 1;
	}
	////////////////////////////////////////////
	rc = depth.create(device, openni::SENSOR_DEPTH);
	if (rc == openni::STATUS_OK)
	{
		rc = depth.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
			depth.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	rc = color.create(device, openni::SENSOR_COLOR);

	if (rc == openni::STATUS_OK)
	{
		rc = color.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
			color.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	if (!depth.isValid() || !color.isValid())
	{
		printf("SimpleViewer: No valid streams. Exiting\n");
		openni::OpenNI::shutdown();
		return 2;
	}
	
	SampleViewer sampleViewer("Simple Viewer", device, depth, color);

	rc = sampleViewer.init(argc, argv);
	if (rc != openni::STATUS_OK)
	{
		openni::OpenNI::shutdown();
		return 3;
	}
	sampleViewer.run();
	
}