#include "ofxDraggable.h"


//--------------------------------------------------------------
ofxDraggablePoint::ofxDraggablePoint(int x, int y) {
    point = ofPoint(x, y);
    active = false;
}

//--------------------------------------------------------------
float ofxDraggablePoint::mouseMoved(int x, int y) {
    dist = ofDist(x, y, point.x, point.y);
    return dist;
}

//--------------------------------------------------------------
bool ofxDraggablePoint::mousePressed(int x, int y) {
    
}

//--------------------------------------------------------------
bool ofxDraggablePoint::mouseDragged(int x, int y) {
    if (!active) return;
    point.set(x, y);
}

//--------------------------------------------------------------
bool ofxDraggablePoint::mouseReleased(int x, int y) {
    
}

//--------------------------------------------------------------
void ofxDraggablePoint::setActive(bool active) {
    this->active = active;
}

//--------------------------------------------------------------
void ofxDraggablePoint::draw() {
    ofPushStyle();
    //cout << "is hover " << isHover << " " <<dist << endl;
    if (active) {
        ofSetColor(ofColor::green);
    } else {
        ofSetColor(ofColor::red);
    }
    ofDrawEllipse(point.x, point.y, 20, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
ofxDraggable::ofxDraggable() {
    active = NULL;
    autoListen = false;
    isChanged = false;
    distThresh = 10;
    bbox.set(0, 0, 1e8, 1e8);
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
void ofxDraggable::setBoundingBox(int x, int y, int w, int h) {
    bbox.set(x, y, w, h);
}

//--------------------------------------------------------------
void ofxDraggable::draw() {
    ofPushMatrix();
    ofTranslate(bbox.x, bbox.y);
    for (auto p : points) {
        p->draw();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
bool ofxDraggable::mouseMoved(ofMouseEventArgs &e) {
    active = NULL;
    for (auto p : points) {
        p->setActive(false);
    }
    float minDist = 1e8;
    for (auto p : points) {
        float x = e.x - bbox.x;
        float y = e.y - bbox.y;
        float dist = p->mouseMoved(x, y);
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
void ofxDraggable::mousePressed(ofMouseEventArgs &e) {
    
}

//--------------------------------------------------------------
bool ofxDraggable::mouseDragged(ofMouseEventArgs &e) {
    if (active == NULL) return false;
    float x = e.x - bbox.x;
    float y = e.y - bbox.y;
    active->mouseDragged(x, y);
    isChanged = true;
    return isChanged;
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
void ofxDraggable::mouseReleased(ofMouseEventArgs &e) {
}

