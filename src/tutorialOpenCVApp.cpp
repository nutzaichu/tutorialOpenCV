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
	void keyDown(KeyEvent event);
	Capture		mCapture;
	Texture		mTexture;
	Surface		mSurface;
	Mat			img;
	bool		first = true;
};

void tutorialOpenCVApp::setup()
{
	mCapture = Capture(640, 480);
	mCapture.start();
	Mat img(toOcv(Surface(mCapture.getSurface())));
	
}   
void tutorialOpenCVApp::update()
{
	if (first) {
		img = Mat(toOcv(Surface(mCapture.getSurface()))); first = false;
	}
	mSurface = Surface(mCapture.getSurface());
	Mat input(toOcv(mSurface));
	//Mat img(toOcv(Surface(loadImage(loadAsset("dfw.jpg")))));

	int R, G, B;
	for (int i = 0; i < input.rows; i++){
		for (int j = 0; j < input.cols; j++){
			R = input.at<cv::Vec3b>(i, j)[0];
			G = input.at<cv::Vec3b>(i, j)[1];
			B = input.at<cv::Vec3b>(i, j)[2];
			if (G - R > 5 && G - B > 5){
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

void tutorialOpenCVApp::keyDown(KeyEvent event){
	if (event.getChar() == '1'){
		img = Mat(toOcv(Surface(mCapture.getSurface())));
	}
}

CINDER_APP_NATIVE( tutorialOpenCVApp, RendererGl )
