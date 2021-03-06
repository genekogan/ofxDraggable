#include "ofxDraggable.h"


//--------------------------------------------------------------
ofxDraggablePoint::ofxDraggablePoint(int x, int y) {
    point = ofPoint(x, y);
    active = false;
    ellipseSize = 20;
    msg = "";
    msgWidth = 0;
    cActive = ofColor::red;
    cRegular = ofColor::green;
}

//--------------------------------------------------------------
float ofxDraggablePoint::mouseMoved(int x, int y) {
    dist = ofDist(x, y, point.x, point.y);
    return dist;
}

//--------------------------------------------------------------
bool ofxDraggablePoint::mousePressed(int x, int y) {
    return active;
}

//--------------------------------------------------------------
bool ofxDraggablePoint::mouseDragged(int x, int y) {
    if (!active) return false;
    point.set(x, y);
    return true;
}

//--------------------------------------------------------------
bool ofxDraggablePoint::mouseReleased(int x, int y) {
    return active;
}

//--------------------------------------------------------------
void ofxDraggablePoint::setActive(bool active) {
    this->active = active;
}

//--------------------------------------------------------------
void ofxDraggablePoint::setMessage(string msg) {
    this->msg = msg;
    ofBitmapFont bitmapFont;
    msgWidth = bitmapFont.getBoundingBox(msg, 0, 0).getWidth();
}

//--------------------------------------------------------------
void ofxDraggablePoint::draw() {
    ofPushStyle();
    ofSetColor(active ? cActive : cRegular);
    ofDrawEllipse(point.x, point.y, ellipseSize, ellipseSize);
    ofSetColor(255);
    ofDrawBitmapStringHighlight(msg, point.x - msgWidth/2, point.y + 6);
    ofPopStyle();
}

//--------------------------------------------------------------
ofxDraggable::ofxDraggable() {
    active = NULL;
    autoListen = false;
    isChanged = false;
    cActive = ofColor::green;
    cRegular = ofColor::red;
    distThresh = 10;
    bbox.set(0, 0, 1e8, 1e8);
}

//--------------------------------------------------------------
ofxDraggable::~ofxDraggable() {
    for (auto p : points) {
        delete p;
    }
    points.clear();
}

//--------------------------------------------------------------
void ofxDraggable::addPoint(int x, int y) {
    ofxDraggablePoint *point = new ofxDraggablePoint(x, y);
    points.push_back(point);
}

//--------------------------------------------------------------
void ofxDraggable::setAuto(bool autoListen) {
    this->autoListen = autoListen;
    if (autoListen) {
        ofAddListener(ofEvents().mouseMoved, this, &ofxDraggable::mouseMoved);
        ofAddListener(ofEvents().mousePressed, this, &ofxDraggable::mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &ofxDraggable::mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &ofxDraggable::mouseReleased);
    } else {
        ofRemoveListener(ofEvents().mouseMoved, this, &ofxDraggable::mouseMoved);
        ofRemoveListener(ofEvents().mousePressed, this, &ofxDraggable::mousePressed);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofxDraggable::mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxDraggable::mouseReleased);
    }
}

//--------------------------------------------------------------
void ofxDraggable::setEllipseSize(int ellipseSize) {
    this->ellipseSize = ellipseSize;
    for (auto p : points) {
        p->setEllipseSize(ellipseSize);
    }
}

//--------------------------------------------------------------
void ofxDraggable::setActiveColor(ofColor cActive) {
    this->cActive = cActive;
    for (auto p : points) {
        p->setActiveColor(this->cActive);
    }
}

//--------------------------------------------------------------
void ofxDraggable::setRegularColor(ofColor cRegular) {
    this->cRegular = cRegular;
    for (auto p : points) {
        p->setRegularColor(this->cRegular);
    }
}

//--------------------------------------------------------------
void ofxDraggable::setBoundingBox(int x, int y, int w, int h) {
    bbox.set(x, y, w, h);
}

//--------------------------------------------------------------
void ofxDraggable::draw() {
    ofPushMatrix();
    ofTranslate(bbox.x, bbox.y);
    ofPushStyle();
    for (auto p : points) {
        p->draw();
    }
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
bool ofxDraggable::getIsChanged() {
    if (isChanged) {
        isChanged = false;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxDraggable::mouseMoved(int x, int y) {
    active = NULL;
    for (auto p : points) {
        p->setActive(false);
    }
    float minDist = 1e8;
    for (auto p : points) {
        float dist = p->mouseMoved(x - bbox.x, y - bbox.y);
        if (dist < minDist && dist < distThresh) {
            if (active != NULL) active->setActive(false);
            active = p;
            active->setActive(true);
            minDist = dist;
        }
    }
    return active != NULL;
}

//--------------------------------------------------------------
void ofxDraggable::mousePressed(int x, int y) {
    
}

//--------------------------------------------------------------
bool ofxDraggable::mouseDragged(int x, int y) {
    if (active == NULL) return false;
    active->mouseDragged(ofClamp(x - bbox.x, 0, bbox.width), ofClamp(y - bbox.y, 0, bbox.height));
    isChanged = true;
    return isChanged;
}

//--------------------------------------------------------------
void ofxDraggable::mouseReleased(int x, int y) {
}

//--------------------------------------------------------------
bool ofxDraggable::mouseMoved(ofMouseEventArgs &e){
    return mouseMoved(e.x, e.y);
}

//--------------------------------------------------------------
void ofxDraggable::mousePressed(ofMouseEventArgs &e) {
    mousePressed(e.x, e.y);
}

//--------------------------------------------------------------
bool ofxDraggable::mouseDragged(ofMouseEventArgs &e) {
    return mouseDragged(e.x, e.y);
}

//--------------------------------------------------------------
void ofxDraggable::mouseReleased(ofMouseEventArgs &e) {
    mouseReleased(e.x, e.y);
}


