#pragma once

#include "ofMain.h"

class ofxDraggablePoint {
public:
    ofxDraggablePoint(int x, int y);
    
    void setActive(bool active);
    void setEllipseSize(int ellipseSize){this->ellipseSize=ellipseSize;}

    void draw();
    
    void set(ofPoint p) {point.set(p);}
    void set(int x, int y) {set(ofPoint(x, y));}
    ofPoint get() {return point;}
    bool getActive() {return active;}
    
    float mouseMoved(int x, int y);
    bool mousePressed(int x, int y);
    bool mouseDragged(int x, int y);
    bool mouseReleased(int x, int y);

protected:
    
    ofPoint point;
    bool active;
    float dist;
    int ellipseSize;
};



class ofxDraggable {
public:
    ofxDraggable();
    ~ofxDraggable();
    
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

    void setActiveColor(ofColor cActive) {this->cActive = cActive;}
    void setRegularColor(ofColor cRegular) {this->cRegular = cRegular;}
    ofColor getRegularColor() {return cRegular;}
    ofColor getActiveColor() {return cActive;}

    void setEllipseSize(int ellipseSize);
    int getEllipseSize() {return ellipseSize;}

    bool mouseMoved(int x, int y);
    void mousePressed(int x, int y);
    bool mouseDragged(int x, int y);
    void mouseReleased(int x, int y);

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
    ofColor cActive;
    ofColor cRegular;
    int ellipseSize;
};


