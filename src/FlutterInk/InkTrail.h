//
//  InkTrail.h
//  emptyExample
//
//  Created by lukasz karluk on 22/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"

class InkTrail : public ofBaseApp
{
    
public :
    
     InkTrail ();
    ~InkTrail ();
    
    void setup  ();
    void update ();
    void draw   ();
    
    void setInitialPosition     ( float x, float y );
    void setTexture             ( ofTexture* tex );
    void addToPosition          ( const ofPoint& p );
    
    void addToLineVertices      ();
    void addToLineNormals       ();
    void addToLineLengths       ();
    void addToStripVertices     ();
    void addToStripTexCoords    ();
    
    void drawLine   ();
    void drawStrip  ();
    
	ofxVec2f	pos;
    ofxVec2f    posNew;
	ofxVec2f	posPrev;
	ofxVec2f	vel;

    int         line_indices;
    int         line_indices_max;
    GLfloat*	line_vertices;
    GLfloat*    line_normals;
    GLfloat*    line_lengths;

	int			strip_indices;
	int			strip_indices_max;
	GLfloat*	strip_vertices;
    GLfloat*    strip_tex_coords;
	GLfloat*	strip_colors;
    
    ofTexture*  tex;
};