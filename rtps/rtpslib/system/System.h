#ifndef RTPS_SYSTEM_H_INCLUDED
#define RTPS_SYSTEM_H_INCLUDED

#if defined __APPLE__ || defined(MACOSX)
    //OpenGL stuff
    #include <OpenGL/gl.h>
#else
    //OpenGL stuff
    #include <GL/gl.h>
#endif

#include "../particle/UniformGrid.h"

namespace rtps {

class System
{
public:
    virtual void update() = 0;
    
    
    virtual UniformGrid getGrid(){ return grid; };
    virtual int getNum(){ return num; };
    virtual GLuint getPosVBO() { return pos_vbo; };
    virtual GLuint getColVBO() { return col_vbo; };
    

protected:
    //number of particles
    int num; 

    GLuint pos_vbo;
    GLuint col_vbo;
    //flag is true if the system's constructor creates the VBOs for the system
    bool managed;

    UniformGrid grid;

};

}

#endif