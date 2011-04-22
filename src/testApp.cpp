#include "testApp.h"

///////////////////////////////////////////
//	SETUP.
///////////////////////////////////////////

void testApp::setup()
{
    int c = 200;
    ofBackground( c, c, c );
    ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    
    img.loadImage( "sound_wave_alpha.png" );
    tex.allocate( img.width, img.height, GL_RGBA );
    tex.loadData( img.getPixels(), img.width, img.height, GL_RGBA );
    
	ink.setup();
    ink.addTexture( &tex );
}

///////////////////////////////////////////
//	UPDATE.
///////////////////////////////////////////

void testApp::update()
{
	ink.update();
}

///////////////////////////////////////////
//	DRAW.
///////////////////////////////////////////

void testApp::draw()
{
	ink.draw();
}

///////////////////////////////////////////
//	HANDLERS.
///////////////////////////////////////////

void testApp::keyPressed(int key)
{

}

void testApp::keyReleased(int key)
{

}

void testApp::mouseMoved(int x, int y )
{
    for( int i=0; i<ink.inkTrails.size(); i++ )
    {
        ofPoint p( x, y );
        ink.inkTrails[ i ]->addToPosition( p );
    }
}

void testApp::mouseDragged(int x, int y, int button)
{

}

void testApp::mousePressed(int x, int y, int button)
{

}

void testApp::mouseReleased(int x, int y, int button)
{

}

void testApp::windowResized(int w, int h)
{

}

