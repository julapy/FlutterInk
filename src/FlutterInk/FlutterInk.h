//
//  FlutterInk.h
//  emptyExample
//
//  Created by lukasz karluk on 22/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "InkTrail.h"

class FlutterInk : public ofBaseApp
{

public:
    
     FlutterInk();
    ~FlutterInk();
    
    void setup  ();
    void update ();
    void draw   ();
    
    void addTexture     ( ofTexture* tex );
    
    vector<InkTrail*>   inkTrails;
    vector<ofTexture*>  inkTextures;
};