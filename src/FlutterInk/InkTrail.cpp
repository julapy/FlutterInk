//
//  InkTrail.cpp
//  emptyExample
//
//  Created by lukasz karluk on 22/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "InkTrail.h"

InkTrail :: InkTrail ()
{
    int max = 5000;
    
    line_indices_max    = max;
    line_indices        = 0;
    line_vertices       = new GLfloat[ line_indices_max * 3 ];
    line_normals        = new GLfloat[ line_indices_max * 3 ];
    line_lengths        = new GLfloat[ line_indices_max ];
    
	strip_indices_max   = max * 2;
	strip_indices       = 0;
	strip_vertices      = new GLfloat[ strip_indices_max * 3 ];
    strip_tex_coords    = new GLfloat[ strip_indices_max * 3 ];
	strip_colors        = new GLfloat[ strip_indices_max * 4 ];
}

InkTrail :: ~InkTrail ()
{
    delete[] line_vertices;
    line_vertices = NULL;
    
    delete[] line_normals;
    line_normals = NULL;
    
    delete[] line_lengths;
    line_lengths = NULL;
    
	delete[] strip_vertices;
    strip_vertices = NULL;
    
    delete[] strip_tex_coords;
    strip_tex_coords = NULL;
    
	delete[] strip_colors;
	strip_colors = NULL;
}

////////////////////////////////////////////////////
//  SETUP.
////////////////////////////////////////////////////

void InkTrail :: setup ()
{
    //
}

void InkTrail :: setInitialPosition	( float x, float y )
{
	pos.x = posPrev.x = posNew.x = x;
	pos.y = posPrev.y = posNew.y = y;
    
    line_vertices[ 0 ] = x;
    line_vertices[ 1 ] = y;
    line_vertices[ 2 ] = 0;
    
    line_normals[ 0 ] = 0;
    line_normals[ 1 ] = 0;
    line_normals[ 2 ] = 0;
    
    line_lengths[ 0 ] = 0;
    
    strip_vertices[ 0 ] = x;
    strip_vertices[ 1 ] = y;
    strip_vertices[ 2 ] = 0;
    strip_vertices[ 3 ] = x;
    strip_vertices[ 4 ] = y;
    strip_vertices[ 5 ] = 0;
    
    strip_tex_coords[ 0 ] = 0;
    strip_tex_coords[ 1 ] = 0;
    strip_tex_coords[ 2 ] = 0;
    strip_tex_coords[ 3 ] = 0;
    strip_tex_coords[ 4 ] = 0;
    strip_tex_coords[ 5 ] = 0;
    
    strip_colors[ 0 ] = 1.0;
    strip_colors[ 1 ] = 1.0;
    strip_colors[ 2 ] = 1.0;
    strip_colors[ 3 ] = 1.0;
    strip_colors[ 4 ] = 1.0;
    strip_colors[ 5 ] = 1.0;
    strip_colors[ 6 ] = 1.0;
    strip_colors[ 7 ] = 1.0;
    
    line_indices    = 1;
    strip_indices   = 2;
}

void InkTrail :: setTexture ( ofTexture* tex )
{
    this->tex = tex;
}

void InkTrail :: addToPosition ( const ofPoint& p )
{
    posNew = p;
}

////////////////////////////////////////////////////
//  GEOMETRY.
////////////////////////////////////////////////////

void InkTrail :: addToLineVertices ()
{
	if( line_indices >= line_indices_max )
	{
        cout << "particle PARTICLE_MAX_LENGTH exceeded.";
		return;
	}
	
	int i = line_indices * 3;
	
	line_vertices[ i + 0 ] = pos.x;
	line_vertices[ i + 1 ] = pos.y;
	line_vertices[ i + 2 ] = 0;
}

void InkTrail :: addToLineNormals ()
{
    ofxVec2f q;
    ofxVec2f p;
    ofxVec2f v;
    int i, j;
    
    //--- left to right.
    
    i = line_indices - 0;
    j = line_indices - 1;
    
    q.set( line_vertices[ i * 3 + 0 ], line_vertices[ i * 3 + 1 ] );
    p.set( line_vertices[ j * 3 + 0 ], line_vertices[ j * 3 + 1 ] );
    v = q - p;
    v.perpendicular();
    v.normalize();
    v *= -1;            // reversed so its always pointing up.
    
    line_normals[ i * 3 + 0 ] = v.x;
    line_normals[ i * 3 + 1 ] = v.y;
    line_normals[ i * 3 + 2 ] = 0;
    
    //--- right to left.
    
    i = line_indices - 1;
    j = line_indices - 0;
    
    q.set( line_vertices[ i * 3 + 0 ], line_vertices[ i * 3 + 1 ] );
    p.set( line_vertices[ j * 3 + 0 ], line_vertices[ j * 3 + 1 ] );
    v = q - p;
    v.perpendicular();
    v.normalize();
    v *= 1;             // doesn't need to be reversed as its already pointing up.
    
    //--- average with previous.
    
    v.x += line_normals[ i * 3 + 0 ];
    v.y += line_normals[ i * 3 + 1 ];
    v.normalize();
    
    line_normals[ i * 3 + 0 ] = v.x;
    line_normals[ i * 3 + 1 ] = v.y;
    line_normals[ i * 3 + 2 ] = 0;
}

void InkTrail :: addToLineLengths ()
{
    int i = line_indices - 0;
    int j = line_indices - 1;
    
    ofxVec2f p1( line_vertices[ i * 3 + 0 ], line_vertices[ i * 3 + 1 ] );
    ofxVec2f p2( line_vertices[ j * 3 + 0 ], line_vertices[ j * 3 + 1 ] );
    
    float distMoved = ( p1 - p2 ).length();
    
    line_lengths[ i ] = line_lengths[ j ] + distMoved;
}

void InkTrail :: addToStripVertices ()
{
	if( strip_indices >= strip_indices_max )
	{
		cout << "particle PARTICLE_MAX_LENGTH exceeded.";
		
		return;
	}
	
	int i, j;
    float thick = 10;
    
    i = strip_indices * 3 - 6;
	j = i * 0.5;
	
	strip_vertices[ i + 0 ] = line_vertices[ j + 0 ] + line_normals[ j + 0 ] * thick;
	strip_vertices[ i + 1 ] = line_vertices[ j + 1 ] + line_normals[ j + 1 ] * thick;
	strip_vertices[ i + 2 ] = 0;
	strip_vertices[ i + 3 ] = line_vertices[ j + 0 ] - line_normals[ j + 0 ] * thick;
	strip_vertices[ i + 4 ] = line_vertices[ j + 1 ] - line_normals[ j + 1 ] * thick;
	strip_vertices[ i + 5 ] = 0;
    
    i = strip_indices * 3;
	j = i * 0.5;
	
	strip_vertices[ i + 0 ] = line_vertices[ j + 0 ] + line_normals[ j + 0 ] * thick;
	strip_vertices[ i + 1 ] = line_vertices[ j + 1 ] + line_normals[ j + 1 ] * thick;
	strip_vertices[ i + 2 ] = 0;
	strip_vertices[ i + 3 ] = line_vertices[ j + 0 ] - line_normals[ j + 0 ] * thick;
	strip_vertices[ i + 4 ] = line_vertices[ j + 1 ] - line_normals[ j + 1 ] * thick;
	strip_vertices[ i + 5 ] = 0;
	
    //-- color.
    
    i = strip_indices * 4;
    
	strip_colors[ i + 0 ] = 1.0;
	strip_colors[ i + 1 ] = 1.0;
	strip_colors[ i + 2 ] = 1.0;
	strip_colors[ i + 3 ] = 1.0;
	strip_colors[ i + 4 ] = 1.0;
	strip_colors[ i + 5 ] = 1.0;
	strip_colors[ i + 6 ] = 1.0;
	strip_colors[ i + 7 ] = 1.0;
}

void InkTrail :: addToStripTexCoords ()
{
    int i       = line_indices;
    int w       = tex->getWidth();
    float l     = line_lengths[ i ];
    float px    = ( l - w * (int)( l / w ) ) / (float)w;
    float py    = 0.5;
    
    ofPoint tx1 = tex->getCoordFromPercent( px, 0.0 );
    ofPoint tx2 = tex->getCoordFromPercent( px, 1.0 );
    
    i = strip_indices * 3;
    
	strip_tex_coords[ i + 0 ] = tx1.x;
	strip_tex_coords[ i + 1 ] = tx1.y;
	strip_tex_coords[ i + 2 ] = 0;
	strip_tex_coords[ i + 3 ] = tx2.x;
	strip_tex_coords[ i + 4 ] = tx2.y;
	strip_tex_coords[ i + 5 ] = 0;
}

////////////////////////////////////////////////////
//  UDPATE.
////////////////////////////////////////////////////

void InkTrail :: update ()
{
    if( line_indices == 0 )
    {
        setInitialPosition( 0, 0 );
        return;
    }
    
    if( posNew == posPrev )
        return;
    
    posPrev = pos;
    pos     = posNew;
    
    addToLineVertices();
    addToLineNormals();
    addToLineLengths();
    addToStripVertices();
    addToStripTexCoords();
    
    line_indices    += 1;
    strip_indices   += 2;
}

////////////////////////////////////////////////////
//  DRAW.
////////////////////////////////////////////////////

void InkTrail :: draw ()
{
//    drawLine();
    drawStrip();
}

void InkTrail :: drawLine ()
{
    glColor4f( 0.0, 0.0, 0.0, 1.0 );
    
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, line_vertices );
	
	glDrawArrays( GL_LINE_STRIP, 0, line_indices );
	
	glDisableClientState( GL_VERTEX_ARRAY );
}

void InkTrail :: drawStrip ()
{
    tex->bind();
    
	glEnableClientState( GL_COLOR_ARRAY );
	glColorPointer( 4, GL_FLOAT, 0, strip_colors );
	
	glEnableClientState( GL_VERTEX_ARRAY );		
	glVertexPointer( 3, GL_FLOAT, 0, strip_vertices );
    
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer( 3, GL_FLOAT, 0, strip_tex_coords );
	
	glDrawArrays( GL_QUAD_STRIP, 0, strip_indices );
	
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
    
    tex->unbind();
}
