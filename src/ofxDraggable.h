#pragma once

#include "ofMain.h"

class ofxDraggablePoint {
public:
    ofxDraggablePoint(int x, int y);
    
    void setActive(bool active);
    void draw();
    
    void set(ofPoint p) {point.set(p);}
    void set(int x, int y) {set(ofPoint(x, y));}
    ofPoint get() {return point;}
    
    float mouseMoved(int x, int y);
    bool mousePressed(int x, int y);
    bool mouseDragged(int x, int y);
    bool mouseReleased(int x, int y);

protected:
    
    ofPoint point;
    bool active;
    float dist;
};

class ofxDraggable {
public:
    ofxDraggable();
    
    void setBoundingBox(int x, int y, int w, int h);
    ofRectangle getBoundingBox() {return bbox;}
    
    void addPoint(int x, int y);
    void draw();
    
    bool getIsChanged();
    
    int size() {return points.size();}
    ofPoint get(int idx) {return points[idx]->get();}
    void set(int idx, float x, float y) {points[idx]->set(x, y);}
    void set(int idx, ofPoint p) {points[idx]->set(p);}

    void setAuto(bool autoListen);

    bool mouseMoved(ofMouseEventArgs &e);
    void mousePressed(ofMouseEventArgs &e);
    bool mouseDragged(ofMouseEventArgs &e);
    void mouseReleased(ofMouseEventArgs &e);
    
protected:
    bool autoListen;
    bool isChanged;
    vector<ofxDraggablePoint*> points;
    ofxDraggablePoint *active;
    float distThresh;
    ofRectangle bbox;
};

