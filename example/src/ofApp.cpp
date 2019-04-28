#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    draggable.setAuto(true);
    
    draggable.addPoint(150, 150);
    draggable.addPoint(450, 150);
    draggable.addPoint(450, 450);
    draggable.addPoint(150, 450);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    draggable.draw();
    
    for (int i=0; i<draggable.size(); i++) {
        ofPoint p = draggable.get(i);
        ofLog() << p;
    }
    
    ofDrawBitmapString("drag the points!", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
