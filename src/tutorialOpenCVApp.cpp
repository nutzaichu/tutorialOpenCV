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

class tutorialOpenCVApp : public AppNative {
  public:
	void setup();
	void update();
	void draw();
	
	CaptureRef		mCapture;
	gl::TextureRef	mTexture;
};

void tutorialOpenCVApp::setup()
{

	// The included image is copyright Trey Ratcliff
	// http://www.flickr.com/photos/stuckincustoms/4045813826/
	mCapture = Capture::create(640, 480);
	mCapture->start();
	//ci::Surface8u surface( loadImage( loadAsset( "dfw.jpg" ) ) );
	//cv::Mat input( toOcv( surface ) );
	//cv::Mat output;
	mTexture = gl::Texture::create(mCapture->getSurface());
	//mTexture = gl::Texture( fromOcv( output ) );
}   
void tutorialOpenCVApp::update()
{
//	if (mCapture && mCapture->checkNewFrame()) {
	mTexture = gl::Texture::create(mCapture->getSurface());
//	}
}
void tutorialOpenCVApp::draw()
{
	gl::clear();
	gl::draw( mTexture );
}

void bgSubstract(){

}

CINDER_APP_NATIVE( tutorialOpenCVApp, RendererGl )
