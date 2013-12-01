#ifndef _POSITION_H_
#define _POSITION_H_

class Position
{
private :
    int mX ;
    int mY ; 
public:
    Position();

    Position( int  x , int y ) :
        mX( x ) , mY ( y ) { }

    int getPositionX( ) { return mX ; }
    int getPositionY() { return mY ; }
};

#endif /* _POSITON_H_ */
