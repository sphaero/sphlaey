#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofHideCursor();
	frameByframe = false;
	alpha = 0;

	dir.listDir("movies/");
	if (dir.size() == 0)
	{
		ofLogError("No movies found!!!");
		ofExit(1);
	}
	for(int i = 0; i < (int)dir.size(); i++)
	{
		string vpath =  dir.getPath(i);
		const char* path = vpath.c_str();
		int key = (int)path[7];
		//ofLogVerbose() << dir.getPath(i) << " :  " << key << "end";
		ofVideoPlayer* vp = new ofVideoPlayer();
		vp->loadMovie(vpath);
		vp->setLoopState(OF_LOOP_NORMAL);
		videoMap.insert(std::pair<int, ofVideoPlayer*>(key,vp));
	}

	std::map<int,ofVideoPlayer*>::iterator it=videoMap.begin();
	canvasMovie = it->second;
	canvasMovie->play();
	fgCanvasMovie = NULL;
	// Uncomment this to show movies with alpha channels
	// canvasMovie.setPixelFormat(OF_PIXELS_RGBA);
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (alpha > 1 && fgCanvasMovie->isPlaying())
	{
		alpha -= 4;
		fgCanvasMovie->update();
	}
	else
	{
		if (fgCanvasMovie) fgCanvasMovie->stop();
	}
    if (canvasMovie->isLoaded())
    {
        canvasMovie->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{

	ofEnableAlphaBlending();
    ofSetHexColor(0xFFFFFF);
    canvasMovie->draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    if (alpha > 1)
    {
		ofSetColor(255,255,255,alpha);
		fgCanvasMovie->draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
	}
}

void ofApp::loadMovie( int key) 
{
	canvasMovie->loadMovie("movies/%d.avi" + ofToString(key) + ".avi" );
	canvasMovie->play();

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key)
{
	std::map<int,ofVideoPlayer*>::iterator it;
	it = videoMap.find(key);
	if (it == videoMap.end()) return;
	if (it->second == canvasMovie) return;
	alpha = 255;
	fgCanvasMovie = canvasMovie;
	canvasMovie = it->second;
    canvasMovie->play();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
