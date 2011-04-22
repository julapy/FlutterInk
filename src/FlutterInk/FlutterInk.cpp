//
//  FlutterInk.cpp
//  emptyExample
//
//  Created by lukasz karluk on 22/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "FlutterInk.h"

FlutterInk :: FlutterInk ()
{
    //
}

FlutterInk :: ~FlutterInk ()
{
    //
}

void FlutterInk :: setup ()
{
    InkTrail* inkTrail;
    inkTrail = new InkTrail();
    inkTrail->setup();
    
    if( inkTextures.size() > 0 )
        inkTrail->setTexture( inkTextures[ inkTextures.size() - 1 ] );
    
    inkTrails.push_back( inkTrail );
}

void FlutterInk :: addTexture ( ofTexture* tex )
{
    inkTextures.push_back( tex );
    
    InkTrail* inkTrail;
    for( int i=0; i<inkTrails.size(); i++ )
    {
        inkTrail = inkTrails[ i ];
        inkTrail->setTexture( tex );
    }
}

void FlutterInk :: update ()
{
    InkTrail* inkTrail;
    for( int i=0; i<inkTrails.size(); i++ )
    {
        inkTrail = inkTrails[ i ];
        inkTrail->update();
    }
}

void FlutterInk :: draw ()
{
    InkTrail* inkTrail;
    for( int i=0; i<inkTrails.size(); i++ )
    {
        inkTrail = inkTrails[ i ];
        inkTrail->draw();
    }
}