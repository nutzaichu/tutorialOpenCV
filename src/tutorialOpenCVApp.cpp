#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "cinder/Cinder.h"
#include "cinder/Capture.h"
#include "cinder/gl/gl.h"
#include "CinderOpenCv.h"

using namespace ci;
using namespace ci::app;
using namespace cv;
using namespace gl;

class tutorialOpenCVApp : public AppNative {
  public:
	void setup();
	void update();
	void draw();
	
	Capture		mCapture;
	Texture		mTexture;
	Surface		mSurface;
};

void tutorialOpenCVApp::setup()
{
	mCapture = Capture(640, 480);
	mCapture.start();
}   
void tutorialOpenCVApp::update()
{
	mSurface = Surface(mCapture.getSurface());
	Mat input(toOcv(mSurface));
	
	Mat img(toOcv(Surface(loadImage(loadAsset("dfw.jpg")))));

	int R, G, B;
	for (int i = 0; i < input.rows; i++){
		for (int j = 0; j < input.cols; j++){
			R = input.at<cv::Vec3b>(i, j)[0];
			G = input.at<cv::Vec3b>(i, j)[1];
			B = input.at<cv::Vec3b>(i, j)[2];
			if (G - R > 10 && G - B > 10){
				input.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(i, j)[0];
				input.at<cv::Vec3b>(i, j)[1] = img.at<cv::Vec3b>(i, j)[1];
				input.at<cv::Vec3b>(i, j)[2] = img.at<cv::Vec3b>(i, j)[2];
			}
		}
	}

	mTexture = Texture(fromOcv(input));

}
void tutorialOpenCVApp::draw()
{
	gl::clear();
	gl::draw( mTexture );
}
CINDER_APP_NATIVE( tutorialOpenCVApp, RendererGl )
