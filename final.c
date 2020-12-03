#include "CSCIx229.h"

int th=0;          //  Azimuth of view angle
int ph=0;          //  Elevation of view angle
int mode=0;        //  What to display
int move=1;       // move light
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=30;   //  Size of world
double xAxis = -2; //x axis of the camera
double yAxis = 1; //y axis of the camera
double zAxis = 5; //z axis of the camera
double angle=0; //angle of the camera
int count = 0; // num of triangles
int vrtc = 0; // num of vertices
//light values
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   20;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   0;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   20;  // Elevation of light
//  Planar vector 0
float dx0;
float dy0;
float dz0;
//  Planar vector 1
float dx1;
float dy1;
float dz1;
//  Normal
float Nx;
float Ny;
float Nz;
// vertex struct
typedef struct {float x,y,z;} vtx;
unsigned int texture[25];

//front grass
const vtx grassTri1[] =
{
  {-18,-1,-17},{-14,0,-17},{-14,0,-15}, {-18,-1,-17},{-14,0,-15},{-18,-1,-15}, {-18,-1,-15},{-14,0,-15},{-13,0,-13}, {-18,-1,-15},{-13,0,-13},{-18,-1,-13},
  {-18,-1,-13},{-13,0,-13},{-13,0,-10}, {-18,-1,-13},{-13,0,-10},{-18,-1,-10}, {-18,-1,-10},{-13,0,-10},{-11,0,-6}, {-18,-1,-10},{-11,0,-6},{-18,0,-6},
  {-18,0,-6},{-11,0,-6},{-11,0,-3}, {-18,0,-6},{-11,0,-3},{-18,0,-3}, {-18,0,-3},{-11,0,-3},{-10.5,0,0}, {-18,0,-3},{-10.5,0,0},{-18,1,0},
  {-18,1,0},{-10.5,0,0},{-9.5,0,3}, {-18,1,0},{-9.5,0,3},{-18,1,2}, {-18,1,2},{-9.5,0,3},{-8,0,6}, {-18,1,2},{-8,0,6},{-14,1,6}, {-14,1,6},{-8,0,6},{-4,0,9},
  {-4,0,9},{0,0,8},{0,3,9}, {0,3,9},{0,0,8},{3,3,9}, {0,0,8},{3,0,6},{3,3,9}, {3,3,9},{3,0,6},{5,3,9}, {3,0,6},{3,0,3},{5,3,9}, {3,0,3},{5,3,1},{5,3,9},
  {5,3,1},{10,-1,4},{5,3,9}, {5,3,9},{10,-1,4},{10,1,9}, {10,1,9},{10,-1,4},{15,-1,10}, {5,3,1},{12,-1,-2},{10,-1,4}, {5,3,1},{8,0,-5},{12,-1,-2},
  {8,0,-5},{13,0,-5},{12,-1,-2}, {13,0,-5},{19,0,-8},{12,-1,-2}, {12,-1,-2},{19,0,-8},{20,-1,-5}, {0,0,0},{5,3,1},{3,0,3}, {0,0,0},{3,1,-4},{5,3,1},
  {3,1,-4},{8,0,-5},{5,3,1}, {0,0,0},{-4,1,-2},{3,1,-4}, {-5,0,1},{-4,1,-2},{0,0,0}, {-5,0,1},{-7,0,-1},{-4,1,-2}, {-7,0,-1},{-7,0,-4},{-4,1,-2},
  {-7,0,-4},{-4,0,-5},{-4,1,-2}, {-4,0,-5},{0,1,-5},{-4,1,-2}, {-4,1,-2},{0,1,-5},{3,1,-4}
};
//front path
const vtx pathTri1[] =
{
  {-14,0,-17},{-11,0,-17},{-14,0,-15}, {-14,0,-15},{-11,0,-17},{-11,0,-12}, {-14,0,-15},{-11,0,-12},{-13,0,-13}, {-13,0,-13},{-11,0,-12},{-11,0,-10},
  {-13,0,-10},{-13,0,-13},{-11,0,-10}, {-13,0,-10},{-11,0,-10},{-10,0,-8}, {-13,0,-10},{-10,0,-8},{-11,0,-6}, {-11,0,-6},{-10,0,-8},{-7,0,-4},
  {-11,0,-6},{-7,0,-4},{-11,0,-3}, {-11,0,-3},{-7,0,-4},{-7,0,-1}, {-11,0,-3},{-7,0,-1},{-10.5,0,0}, {-10.5,0,0},{-7,0,-1},{-5,0,1},
  {-10.5,0,0},{-5,0,1},{-9.5,0,3}, {-9.5,0,3},{-5,0,1},{-8,0,6}, {-5,0,1},{0,0,0},{-8,0,6}, {-8,0,6},{0,0,0},{-4,0,9}, {0,0,0},{3,0,3},{-4,0,9},
  {-4,0,9},{3,0,3},{0,0,8}, {0,0,8},{3,0,3},{3,0,6}, {-10,0,-8},{-4,0,-8},{-7,0,-4}, {-4,0,-8},{-4,0,-5},{-7,0,-4}, {-4,0,-8},{2,1,-8},{-4,0,-5},
  {-4,0,-5},{2,1,-8},{0,1,-5}, {2,1,-8},{8,1,-8},{0,1,-5}, {0,1,-5},{8,1,-8},{3,1,-4}, {8,1,-8},{13,0,-8},{3,1,-4}, {8,0,-5},{3,1,-4},{13,0,-8},
  {8,0,-5},{13,0,-8},{18,0,-10}, {8,0,-5},{18,0,-10},{13,0,-5}, {13,0,-5},{18,0,-10},{19,0,-8}
};
//beach
const vtx beachTri[] =
{
  {15,-1,10},{28,-4,7},{25,-3,10}, {15,-1,10},{10,-1,4},{28,-4,7}, {10,-1,4},{30,-4,2},{28,-4,7}, {10,-1,4},{12,-1,-2},{30,-4,2},
  {12,-1,-2},{21,-4,-3},{30,-4,2}, {12,-1,-2},{20,-1,-5},{21,-4,-3}, {21,-4,-3},{26,-4,-6},{30,-4,2}
};
//right path
const vtx pathTri2[] =
{
  {-2,1,-5},{-3,1,-7},{0,1,-7}, {-3,1,-7},{0,1,-12},{0,1,-7}, {-3,1,-12},{0,1,-12},{-3,1,-7}, {-3,1,-12},{-4,1,-18},{0,1,-12},
  {-6,1,-17},{-4,1,-18},{-3,1,-12}, {-6,1,-17},{-4,1,-27},{-4,1,-18}, {-6,1,-17},{-6,1,-23},{-4,1,-27}, {-6,1,-23},{-11,1,-28},{-4,1,-27},
  {-11,1,-23},{-11,1,-28},{-6,1,-23}
};
//right grass
const vtx grassTri2[] =
{
  {0,0,0},{0,1,-7},{4,1,8}, {0,1,-7},{0,1,-12},{4,1,8}, {4,1,8},{0,1,-12},{7,2,-21}, {0,1,-12},{-4,1,-18},{7,2,-21},
  {-4,1,-18},{3,2,-29},{7,2,-21}, {-4,1,-18},{-4,1,-27},{3,2,-29}, {-4,1,-27},{-11,1,-28},{3,2,-29}, {-11,1,-28},{-4,2,-32},{3,2,-29},
  {-2,1,-5},{0,1,-7},{0,0,0}
};
//wall in front of the castle
const vtx wallQuad1[] =
{
  {18,0,-10},{13,0,-8},{13,-2,-8},{18,-2,-10}, {13,0,-8},{8,1,-8},{8,-2,-8},{13,-2,-8}, {8,1,-8},{2,1,-8},{2,-2,-8},{8,-2,-8},
  {2,1,-8},{-4,0,-8},{-4,-2,-8},{2,-2,-8}, {-4,0,-8},{-10,0,-8},{-10,-2,-8},{-4,-2,-8}, {-10,0,-8},{-11,0,-10},{-11,-2,-10},{-10,-2,-8},
  {-11,0,-10},{-11,0,-17},{-11,-2,-17},{-11,-2,-10}, {-11,0,-17},{-14,0,-17},{-14,-2,-17},{-11,-2,-17}, {-14,0,-17},{-18,-1,-17},{-18,-2,-17},{-14,-2,-17},
  {19,0,-8},{18,0,-10},{18,-2,-10},{19,-2,-8}, {20,-1,-5},{19,0,-8},{19,-5,-8},{20,-5,-5}, {21,-3,-3},{20,-1,-5},{20,-5,-5},{21,-5,-3}
};
//wall around pond
const vtx wallQuad2[] =
{
  {23,0,-13},{24,0,-11},{24,-2,-11},{23,-2,-13}, {24,0,-11},{26,-1,-6},{26,-4,-6},{24,-4,-11}, {26,-1,-6},{30,0,2},{30,-4,2},{26,-4,-6},
  {30,0,2},{28,0,7},{28,-4,7},{30,-4,2}, {28,0,7},{25,0,10},{25,-4,10},{28,-4,7}, {25,0,10},{15,-1,10},{15,-4,10},{25,-4,10}
};
//brick wall to the right of the castle
const vtx brickWallQuad[] =
{
  {-6,1,-23},{-6,1,-17},{-6,-1,-17},{-6,-1,-23}, {-6,1,-17},{-3,1,-12},{-3,-1,-12},{-6,-1,-17}, {-3,1,-12},{-3,1,-7},{-3,-1,-7},{-3,-1,-12}
};
//grass wall on right side
const vtx grassWallQuad1[] =
{
  {-4,6,-33},{4,6,-30},{3,2,-29},{-4,2,-32}, {4,6,-30},{8,6,-21},{7,2,-21},{3,2,-29}, {8,6,-21},{5,6,8},{4,1,8},{7,2,-21}
};
//front grass wall
const vtx grassWallQuad2[] =
{
  {31,5,2},{29,5,8},{28,0,7},{30,0,2}, {29,5,8},{25,5,11},{25,0,10},{28,0,7}, {25,5,11},{15,5,11},{15,-1,10},{25,0,10},
  {15,5,11},{10,5,10},{10,1,9},{15,-1,10}, {10,5,10},{5,5,10},{5,3,9},{10,1,9}, {5,5,10},{3,5,10},{3,3,9},{5,3,9},
  {3,5,10},{0,5,10},{0,3,9},{3,3,9}, {0,5,10},{-4,5,10},{-4,0,9},{0,3,9}, {-4,5,10},{-15,5,7},{-14,1,6},{-4,0,9},
  {-15,5,7},{-19,5,2},{-18,1,2},{-14,1,6}, {-19,5,2},{-19,5,0},{-18,1,0},{-18,1,2}, {-19,5,0},{-19,5,-3},{-18,0,-3},{-18,1,0},
  {-19,5,-3},{-19,5,-6},{-18,0,-6},{-18,0,-3}, {-19,5,-6},{-19,5,-10},{-18,-1,-10},{-18,0,-6}, {-19,5,-10},{-22,8,-23},{-17,-2,-17},{-18,-1,-10},
  {-21,8,-26},{-4,5,-34},{-4,-2,-34},{-15,-2,-26}
};
//behind waterfall
const vtx waterFallBack[] =
{
  {-22,8,-23},{-21,8,-26},{-15,-2,-26},{-17,-2,-17}
};

static void structure(double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  //Rectangular Prism
  //Sides
  //back
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  glTexCoord2f(0.0,0.0); glVertex3d(-7,-2,-10);
  glTexCoord2f(11,0.0); glVertex3d(-7,7,-10);
  glTexCoord2f(11,11); glVertex3d(-7,7,10);
  glTexCoord2f(0.0,11); glVertex3d(-7,-2,10);
  glEnd();
  //left side
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0.0,0.0); glVertex3d(-7,-2,10);
  glTexCoord2f(11,0.0); glVertex3d(-7,7,10);
  glTexCoord2f(11,11); glVertex3d(7,7,10);
  glTexCoord2f(0.0,11); glVertex3d(7,-2,10);
  glEnd();
  //front
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0.0,0.0); glVertex3d(7,-2,10);
  glTexCoord2f(11,0.0); glVertex3d(7,7,10);
  glTexCoord2f(11,11); glVertex3d(7,7,-10);
  glTexCoord2f(0.0,11); glVertex3d(7,-2,-10);
  glEnd();
  //right side
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,-1);
  glTexCoord2f(0.0,0.0); glVertex3d(7,-2,-10);
  glTexCoord2f(11,0.0); glVertex3d(7,7,-10);
  glTexCoord2f(11,11); glVertex3d(-7,7,-10);
  glTexCoord2f(0.0,11);glVertex3d(-7,-2,-10);
  glEnd();

  //right wall
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(81,0,-81);
  glTexCoord2f(0.0,0.0); glVertex3d(-7,-2,-10);
  glTexCoord2f(11,0.0); glVertex3d(-7,7,-10);
  glTexCoord2f(11,11); glVertex3d(-16,7,-19);
  glTexCoord2f(0.0,11); glVertex3d(-16,-2,-19);
  glEnd();

  //left wall
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3d(-7,-2,10);
  glTexCoord2f(11,0.0); glVertex3d(-7,7,10);
  glTexCoord2f(11,11); glVertex3d(-12,7,15);
  glTexCoord2f(0.0,11); glVertex3d(-12,-2,15);
  glEnd();
  //Entry
  //front
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0.0,0.0); glVertex3d(8,-2,-3);
  glTexCoord2f(6,0.0); glVertex3d(8,-2,3);
  glTexCoord2f(6,6); glVertex3d(8,7,3);
  glTexCoord2f(0.0,6); glVertex3d(8,7,-3);
  glEnd();
  //doors
  glBindTexture(GL_TEXTURE_2D,texture[24]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,1); glVertex3d(8.01,2.9,0);
  glTexCoord2f(1,1); glVertex3d(8.01,2.9,-1);
  glTexCoord2f(1,0); glVertex3d(8.01,0.9,-1);
  glTexCoord2f(0,0); glVertex3d(8.01,0.9,0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texture[24]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,1); glVertex3d(8.01,2.9,0);
  glTexCoord2f(1,1); glVertex3d(8.01,2.9,1);
  glTexCoord2f(1,0); glVertex3d(8.01,0.9,1);
  glTexCoord2f(0,0); glVertex3d(8.01,0.9,0);
  glEnd();
  //left
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(7,0,7);
  glTexCoord2f(0.0,0.0); glVertex3d(8,-2,3);
  glTexCoord2f(1,0.0); glVertex3d(8,7,3);
  glTexCoord2f(1,1); glVertex3d(7,7,4);
  glTexCoord2f(0.0,1); glVertex3d(7,-2,4);
  glEnd();
  //right
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(7,0,-7);
  glTexCoord2f(0.0,0.0); glVertex3d(8,-2,-3);
  glTexCoord2f(1,0.0); glVertex3d(8,7,-3);
  glTexCoord2f(1,1); glVertex3d(7,7,-4);
  glTexCoord2f(0.0,1); glVertex3d(7,-2,-4);
  glEnd();
  //window front
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1,1);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,7,1.5);
  glTexCoord2f(2,0.0); glVertex3d(8.5,7,-1.5);
  glTexCoord2f(2,2); glVertex3d(8.5,5.5,-1.5);
  glTexCoord2f(0.0,2); glVertex3d(8.5,5.5,1.5);
  glEnd();
  glDisable(GL_POLYGON_OFFSET_FILL);
  //window triangle
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1,1);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_TRIANGLES);
  glNormal3f(1,0,0);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,9,0);
  glTexCoord2f(2,0.0); glVertex3d(8.5,7,1.5);
  glTexCoord2f(1,2);glVertex3d(8.5,7,-1.5);
  glEnd();
  glDisable(GL_POLYGON_OFFSET_FILL);
  //Peach window top
  glBindTexture(GL_TEXTURE_2D,texture[3]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0.0,1); glVertex3d(8.5,7.5,1);
  glTexCoord2f(1,1); glVertex3d(8.5,7.5,-1);
  glTexCoord2f(1,0.0); glVertex3d(8.5,6.5,-1);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,6.5,1);
  glEnd();
  //Peach window bottom
  glBindTexture(GL_TEXTURE_2D,texture[4]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0.0,1); glVertex3d(8.5,6.5,1);
  glTexCoord2f(1,1); glVertex3d(8.5,6.5,-1);
  glTexCoord2f(1,0.0); glVertex3d(8.5,5.5,-1);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,5.5,1);
  glEnd();
  //window left
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,7,1.5);
  glTexCoord2f(2,0.0); glVertex3d(8.5,5.5,1.5);
  glTexCoord2f(2,2); glVertex3d(7,5.5,1.5);
  glTexCoord2f(0.0,2); glVertex3d(7,7,1.5);
  glEnd();
  //window right
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,-1);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,7,-1.5);
  glTexCoord2f(2,0.0); glVertex3d(8.5,5.5,-1.5);
  glTexCoord2f(2,2); glVertex3d(7,5.5,-1.5);
  glTexCoord2f(0.0,2); glVertex3d(7,7,-1.5);
  glEnd();
  //window bottom
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
  glNormal3f(0,-1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,5.5,-1.5);
  glTexCoord2f(2,0.0); glVertex3d(8.5,5.5,1.5);
  glTexCoord2f(2,2); glVertex3d(7,5.5,1.5);
  glTexCoord2f(0.0,2); glVertex3d(1,5.5,-1.5);
  glEnd();
  //Entry Roof
  //front
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(1,1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(8,7,-3);
  glTexCoord2f(5,0.0); glVertex3d(8,7,3);
  glTexCoord2f(5,5); glVertex3d(4,11,2);
  glTexCoord2f(0.0,5); glVertex3d(4,11,-2);
  glEnd();
  //left window
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(0,3.75,5);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,9,0);
  glTexCoord2f(2,0.0); glVertex3d(8.5,7,1.5);
  glTexCoord2f(2,2); glVertex3d(6,7,1.5);
  glTexCoord2f(0.0,2); glVertex3d(6,9,0);
  glEnd();
  //right window
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(0,3.75,-5);
  glTexCoord2f(0.0,0.0); glVertex3d(8.5,9,0);
  glTexCoord2f(2,0.0); glVertex3d(8.5,7,-1.5);
  glTexCoord2f(2,2); glVertex3d(6,7,-1.5);
  glTexCoord2f(0.0,2); glVertex3d(6,9,0);
  glEnd();

  //left front
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_TRIANGLES);
  glNormal3f(4,5,4);
  glTexCoord2f(0.0,0.0); glVertex3d(8,7,3);
  glTexCoord2f(2,0.0); glVertex3d(7,7,4);
  glTexCoord2f(1,2); glVertex3d(4,11,2);
  glEnd();
  //right front
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_TRIANGLES);
  glNormal3f(4,5,-4);
  glTexCoord2f(0.0,0.0); glVertex3d(8,7,-3);
  glTexCoord2f(2,0.0); glVertex3d(7,7,-4);
  glTexCoord2f(1,2); glVertex3d(4,11,-2);
  glEnd();
  //left back
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_TRIANGLES);
  glNormal3f(-8,0,12);
  glTexCoord2f(0.0,0.0); glVertex3d(4,11,2);
  glTexCoord2f(4,0.0); glVertex3d(4,7,2);
  glTexCoord2f(2,4); glVertex3d(7,7,4);
  glEnd();
  //right back
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_TRIANGLES);
  glNormal3f(-8,0,-12);
  glTexCoord2f(0.0,0.0); glVertex3d(4,11,-2);
  glTexCoord2f(4,0.0); glVertex3d(4,7,-2);
  glTexCoord2f(2,4); glVertex3d(7,7,-4);
  glEnd();

  //Roof
  //top
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(-4.5,9,-6.5);
  glTexCoord2f(6,0.0); glVertex3d(-4.5,9,6.5);
  glTexCoord2f(6,6); glVertex3d(4.5,9,6.5);
  glTexCoord2f(0.0,6); glVertex3d(4.5,9,-6.5);
  glEnd();
  //back
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(-40,46.75,0);
  glTexCoord2f(0.0,0.0); glVertex3d(-4.5,9,-6.5);
  glTexCoord2f(5.5,0.0); glVertex3d(-7,7,-10);
  glTexCoord2f(5.5,4); glVertex3d(-7,7,10);
  glTexCoord2f(0.0,4); glVertex3d(-4.5,9,6.5);
  glEnd();
  //right
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(0,49,-28);
  glTexCoord2f(0.0,0.0); glVertex3d(-4.5,9,-6.5);
  glTexCoord2f(5.5,0.0); glVertex3d(-7,7,-10);
  glTexCoord2f(5.5,4); glVertex3d(7,7,-10);
  glTexCoord2f(0.0,4); glVertex3d(4.5,9,-6.5);
  glEnd();
  //front
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(40,46.75,0);
  glTexCoord2f(0.0,0.0); glVertex3d(4.5,9,-6.5);
  glTexCoord2f(5.5,0.0); glVertex3d(7,7,-10);
  glTexCoord2f(5.5,4); glVertex3d(7,7,10);
  glTexCoord2f(0.0,4); glVertex3d(4.5,9,6.5);
  glEnd();
  //left
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUADS);
  glNormal3f(0,49,28);
  glTexCoord2f(0.0,0.0); glVertex3d(4.5,9,6.5);
  glTexCoord2f(5.5,0.0); glVertex3d(7,7,10);
  glTexCoord2f(5.5,4); glVertex3d(-7,7,10);
  glTexCoord2f(0.0,4); glVertex3d(-4.5,9,6.5);
  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

}

static void tower(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{

   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   //octagonal prism
   //Roof
   //1
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-4.5,3,1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(-2,5,0);
   glTexCoord2f(1.0,2.0); glVertex3d(-1.5,5,1.5);
   glEnd();
   //2
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-4.5,3,-1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(-1.5,5,-1.5);
   glTexCoord2f(1.0,2.0); glVertex3d(-2,5,0);
   glEnd();
   //3
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-1.5,3,-4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(0,5,-2);
   glTexCoord2f(1.0,2.0); glVertex3d(-1.5,5,-1.5);
   glEnd();
   //4
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(1.5,3,-4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(1.5,5,-1.5);
   glTexCoord2f(1.0,2.0); glVertex3d(0,5,-2);
   glEnd();
   //5
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(4.5,3,-1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(2,5,0);
   glTexCoord2f(1.0,2.0); glVertex3d(1.5,5,-1.5);
   glEnd();
   //6
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(4.5,3,1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(1.5,5,1.5);
   glTexCoord2f(1.0,2.0); glVertex3d(2,5,0);
   glEnd();
   //7
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(1.5,3,4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(0,5,2);
   glTexCoord2f(1.0,2.0); glVertex3d(1.5,5,1.5);
   glEnd();
   //8
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_TRIANGLES);
   glNormal3f(-1.5,3,4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(0,8,0);
   glTexCoord2f(2.0,0.0); glVertex3d(-1.5,5,1.5);
   glTexCoord2f(1.0,2.0); glVertex3d(0,5,2);
   glEnd();

   //Octagonal Prism
   //Sides
   //1
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-4.5,0,1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(-2,0,0);
   glTexCoord2f(4.0,0.0); glVertex3d(-1.5,0,1.5);
   glTexCoord2f(4.0,4.0); glVertex3d(-1.5,5,1.5);
   glTexCoord2f(0.0,4.0); glVertex3d(-2,5,0);
   glEnd();
   //2
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-4.5,0,-1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(-2,0,0);
   glTexCoord2f(4.0,0.0); glVertex3d(-1.5,0,-1.5);
   glTexCoord2f(4.0,4.0); glVertex3d(-1.5,5,-1.5);
   glTexCoord2f(0.0,4.0); glVertex3d(-2,5,0);
   glEnd();
   //3
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1.5,0,-4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(-1.5,0,-1.5);
   glTexCoord2f(4.0,0.0); glVertex3d(0,0,-2);
   glTexCoord2f(4.0,4.0); glVertex3d(0,5,-2);
   glTexCoord2f(0.0,4.0); glVertex3d(-1.5,5,-1.5);
   glEnd();
   //4
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(1.5,0,-4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(1.5,0,-1.5);
   glTexCoord2f(4.0,0.0); glVertex3d(0,0,-2);
   glTexCoord2f(4.0,4.0); glVertex3d(0,5,-2);
   glTexCoord2f(0.0,4.0); glVertex3d(1.5,5,-1.5);
   glEnd();
   //5
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(4.5,0,-1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(2,0,0);
   glTexCoord2f(4.0,0.0); glVertex3d(1.5,0,-1.5);
   glTexCoord2f(4.0,4.0); glVertex3d(1.5,5,-1.5);
   glTexCoord2f(0.0,4.0); glVertex3d(2,5,0);
   glEnd();
   //6
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(4.5,0,1.5);
   glTexCoord2f(0.0,0.0); glVertex3d(2,0,0);
   glTexCoord2f(4.0,0.0); glVertex3d(1.5,0,1.5);
   glTexCoord2f(4.0,4.0); glVertex3d(1.5,5,1.5);
   glTexCoord2f(0.0,4.0); glVertex3d(2,5,0);
   glEnd();
   //7
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(1.5,0,4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(1.5,0,1.5);
   glTexCoord2f(4.0,0.0); glVertex3d(0,0,2);
   glTexCoord2f(4.0,4.0); glVertex3d(0,5,2);
   glTexCoord2f(0.0,4.0); glVertex3d(1.5,5,1.5);
   glEnd();
   //8
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f(-1.5,0,4.5);
   glTexCoord2f(0.0,0.0); glVertex3d(-1.5,0,1.5);
   glTexCoord2f(4.0,0.0); glVertex3d(0,0,2);
   glTexCoord2f(4.0,4.0); glVertex3d(0,5,2);
   glTexCoord2f(0.0,4.0); glVertex3d(-1.5,5,1.5);
   glEnd();
   //Bottom Octagon
   glBegin(GL_POLYGON);
   glNormal3f(0,-1,0);
   glVertex3d(-2,0,0);
   glVertex3d(-1.5,0,1.5);
   glVertex3d(0,0,2);
   glVertex3d(1.5,0,1.5);
   glVertex3d(2,0,0);
   glVertex3d(1.5,0,-1.5);
   glVertex3d(0,0,-2);
   glVertex3d(-1.5,0,-1.5);
   glEnd();

   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void bridge(double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  //walkway
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(-1.5,1,8);
  glTexCoord2f(0.0,4.0); glVertex3d(1.5,1,8);
  glTexCoord2f(4.0,4.0); glVertex3d(1.5,1,15);
  glTexCoord2f(4.0,0.0); glVertex3d(-1.5,1,15);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glBegin(GL_QUADS);
  glNormal3f(0,-1,0);
  glTexCoord2f(4.0,0.0); glVertex3d(-1.5,0.5,15);
  glTexCoord2f(4.0,4.0); glVertex3d(1.5,0.5,15);
  glTexCoord2f(0.0,4.0); glVertex3d(1.5,0.5,8);
  glTexCoord2f(0.0,0.0); glVertex3d(-1.5,0.5,8);
  glEnd();
  //rail
  //left
  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(1,1); glVertex3d(-2,1.5,8);
  glTexCoord2f(0,1); glVertex3d(-1.5,1.5,8);
  glTexCoord2f(0,0); glVertex3d(-1.5,1.5,15);
  glTexCoord2f(1,0); glVertex3d(-2,1.5,15);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glBegin(GL_QUADS);
  glNormal3f(0,-1,0);
  glTexCoord2f(1,0); glVertex3d(-2,0.5,15);
  glTexCoord2f(0,0); glVertex3d(-1.5,0.5,15);
  glTexCoord2f(0,1); glVertex3d(-1.5,0.5,8);
  glTexCoord2f(1,1); glVertex3d(-2,0.5,8);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(1,1); glVertex3d(-2,1.5,15);
  glTexCoord2f(0,1); glVertex3d(-1.5,1.5,15);
  glTexCoord2f(0,0); glVertex3d(-1.5,0.5,15);
  glTexCoord2f(1,0); glVertex3d(-2,0.5,15);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  glTexCoord2f(6,1); glVertex3d(-2,1.5,8);
  glTexCoord2f(0,1); glVertex3d(-2,1.5,15);
  glTexCoord2f(0,0); glVertex3d(-2,0.5,15);
  glTexCoord2f(6,0); glVertex3d(-2,0.5,8);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(6,1); glVertex3d(-1.5,1.5,8);
  glTexCoord2f(0,1); glVertex3d(-1.5,1.5,15);
  glTexCoord2f(0,0); glVertex3d(-1.5,0.5,15);
  glTexCoord2f(6,0); glVertex3d(-1.5,0.5,8);
  glEnd();
  //right
  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(1,1); glVertex3d(2,1.5,8);
  glTexCoord2f(0,1); glVertex3d(1.5,1.5,8);
  glTexCoord2f(0,0); glVertex3d(1.5,1.5,15);
  glTexCoord2f(1,0); glVertex3d(2,1.5,15);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glBegin(GL_QUADS);
  glNormal3f(0,-1,0);
  glTexCoord2f(1,0); glVertex3d(2,0.5,15);
  glTexCoord2f(0,0); glVertex3d(1.5,0.5,15);
  glTexCoord2f(0,1); glVertex3d(1.5,0.5,8);
  glTexCoord2f(1,1); glVertex3d(2,0.5,8);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(1,1); glVertex3d(2,1.5,15);
  glTexCoord2f(0,1); glVertex3d(1.5,1.5,15);
  glTexCoord2f(0,0); glVertex3d(1.5,0.5,15);
  glTexCoord2f(1,0); glVertex3d(2,0.5,15);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(6,1); glVertex3d(2,1.5,8);
  glTexCoord2f(0,1); glVertex3d(2,1.5,15);
  glTexCoord2f(0,0); glVertex3d(2,0.5,15);
  glTexCoord2f(6,0); glVertex3d(2,0.5,8);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  glTexCoord2f(6,1); glVertex3d(1.5,1.5,8);
  glTexCoord2f(0,1); glVertex3d(1.5,1.5,15);
  glTexCoord2f(0,0); glVertex3d(1.5,0.5,15);
  glTexCoord2f(6,0); glVertex3d(1.5,0.5,8);
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void window(double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

  glBindTexture(GL_TEXTURE_2D,texture[5]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0); glVertex3d(0,0,0);
  glTexCoord2f(0,1); glVertex3d(0,1,0);
  glTexCoord2f(1,1); glVertex3d(1,1,0);
  glTexCoord2f(1,0); glVertex3d(1,0,0);
  glEnd();

  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void castle(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
  //  Save transformation
  glPushMatrix();
  //  Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Draw the castle
  tower(-10,2,-7 , 1,1.1,1 , 0);
  tower(-10,2,7 , 1,1,1 , 0);
  tower(10,2,-7 , 1,1.1,1 , 0);
  tower(10,2,7 , 1,1,1 , 0);
  structure(0,0,0 , 1,1,1, -90);
  tower(0,8,2 , 2,0.75,1.5  ,0); //2,0.75,1.5
  tower(0,7,2 , 1.25,2,1 , 0); //1.25,2,1
  bridge(0,0,0, 1,1,1, 0);
  window(6.5,5,7.01, 1,1,1, 0);
  window(5,5,7.01, 1,1,1, 0);
  window(6.5,3.5,7.01, 1,1,1, 0);
  window(5,3.5,7.01, 1,1,1, 0);
  window(-7.5,5,7.01, 1,1,1, 0);
  window(-6,5,7.01, 1,1,1, 0);
  window(-7.5,3.5,7.01, 1,1,1, 0);
  window(-6,3.5,7.01, 1,1,1, 0);
  window(-0.5,10.5,5.01, 1,1,1, 0);
  window(-0.5,15,4.01, 1,1,1, 0);
  //  Undo transformations
  glPopMatrix();
}

static void tri(const vtx tri[], int tex, int obCount, double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  //  Set specular color to white
  float white[] = {1,1,1,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

  count = 0;
  vrtc = 0;
  glBindTexture(GL_TEXTURE_2D,texture[tex]);
  glBegin(GL_TRIANGLES);
  while (count < obCount){
    //  Planar vector 0
    dx0 = tri[vrtc].x-tri[vrtc+1].x;
    dy0 = tri[vrtc].y-tri[vrtc+1].y;
    dz0 = tri[vrtc].z-tri[vrtc+1].z;
    //  Planar vector 1
    dx1 = tri[vrtc+2].x-tri[vrtc].x;
    dy1 = tri[vrtc+2].y-tri[vrtc].y;
    dz1 = tri[vrtc+2].z-tri[vrtc].z;
    //  Normal
    Nx = dy0*dz1 - dy1*dz0;
    Ny = dz0*dx1 - dz1*dx0;
    Nz = dx0*dy1 - dx1*dy0;
    glNormal3f(Nx,Ny,Nz);
    //grabs the next 3 vertices to make a new triangle
    glTexCoord2f(0.0,0.0); glVertex3d(tri[vrtc].x, tri[vrtc].y, tri[vrtc].z);
    glTexCoord2f(1.0,0.0); glVertex3d(tri[vrtc+1].x, tri[vrtc+1].y, tri[vrtc+1].z);
    glTexCoord2f(0.5,1.0); glVertex3d(tri[vrtc+2].x, tri[vrtc+2].y, tri[vrtc+2].z);
    //keeps count of triangles
    count = count + 1;
    //moves to next set of vertices in index
    vrtc = vrtc + 3;
  };
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void quad(const vtx quad[], int tex, int obCount, float rep, double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  //  Set specular color to white
  float white[] = {1,1,1,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

  count = 0;
  vrtc = 0;
  glBindTexture(GL_TEXTURE_2D,texture[tex]);
  glBegin(GL_QUADS);
  while (count < obCount){
    //  Planar vector 0
    dx0 = quad[vrtc].x-quad[vrtc+1].x;
    dy0 = quad[vrtc].y-quad[vrtc+1].y;
    dz0 = quad[vrtc].z-quad[vrtc+1].z;
    //  Planar vector 1
    dx1 = quad[vrtc+2].x-quad[vrtc].x;
    dy1 = quad[vrtc+2].y-quad[vrtc].y;
    dz1 = quad[vrtc+2].z-quad[vrtc].z;
    //  Normal
    Nx = dy0*dz1 - dy1*dz0;
    Ny = dz0*dx1 - dz1*dx0;
    Nz = dx0*dy1 - dx1*dy0;
    glNormal3f(Nx,Ny,Nz);
    //grabs the next 4 vertices to make the new quad
    glTexCoord2f(rep,rep); glVertex3d(quad[vrtc].x, quad[vrtc].y, quad[vrtc].z);
    glTexCoord2f(0.0,rep); glVertex3d(quad[vrtc+1].x, quad[vrtc+1].y, quad[vrtc+1].z);
    glTexCoord2f(0.0,0.0); glVertex3d(quad[vrtc+2].x, quad[vrtc+2].y, quad[vrtc+2].z);
    glTexCoord2f(rep,0.0); glVertex3d(quad[vrtc+3].x, quad[vrtc+3].y, quad[vrtc+3].z);
    //keeps count of quads
    count = count + 1;
    //moves to next set of vertices in index
    vrtc = vrtc + 4;
  };
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void woodBridge(double x,double y,double z,
                          double dx,double dy,double dz,
                          double th)
{
  //  Set specular color to white
  float white[] = {1,1,1,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  //top
  glBindTexture(GL_TEXTURE_2D,texture[13]);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(5.0,0.0); glVertex3d(4,0,-5);
  glTexCoord2f(5.0,0.0); glVertex3d(5,0,-3);
  glTexCoord2f(0.0,0.0); glVertex3d(0,0,0);
  glTexCoord2f(0.0,0.0); glVertex3d(-1,0,-2);
  //bottom
  glNormal3f(0,-1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(-1,-0.5,-2);
  glTexCoord2f(0.0,0.0); glVertex3d(0,-0.5,0);
  glTexCoord2f(0.0,5.0); glVertex3d(5,-0.5,-3);
  glTexCoord2f(0.0,5.0); glVertex3d(4,-0.5,-5);
  glEnd();
  //sides
  glBindTexture(GL_TEXTURE_2D,texture[14]);
  glBegin(GL_QUADS);
  glNormal3f(1.5,0,2.5);
  glTexCoord2f(0.0,0.0); glVertex3d(0,0,0);
  glTexCoord2f(1.0,0.0); glVertex3d(5,0,-3);
  glTexCoord2f(1.0,1.0); glVertex3d(5,-0.5,-3);
  glTexCoord2f(0.0,1.0); glVertex3d(0,-0.5,0);
  glNormal3f(-1.5,0,-2.5);
  glTexCoord2f(0.0,0.0); glVertex3d(-1,0,-2);
  glTexCoord2f(1.0,0.0); glVertex3d(4,0,-5);
  glTexCoord2f(1.0,1.0); glVertex3d(4,-0.5,-5);
  glTexCoord2f(0.0,1.0); glVertex3d(-1,-0.5,-2);
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void moat(double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  //  Set specular color to white
  float white[] = {1,1,1,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  // Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  //moat
  glBindTexture(GL_TEXTURE_2D,texture[9]);
  glBegin(GL_POLYGON);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(19,-2,-8);
  glTexCoord2f(20.0,0.0); glVertex3d(-18,-2,-8);
  glTexCoord2f(20.0,20.0); glVertex3d(-18,-2,-34);
  glTexCoord2f(0.0,20.0); glVertex3d(24,-2,-34);
  glTexCoord2f(1.75,0.2); glVertex3d(24,-2,-11);
  glEnd();
  //moat stairs
  //tops
  glBindTexture(GL_TEXTURE_2D,texture[10]);
  glBegin(GL_QUADS);
  glNormal3f(1.5,0,2.5);
  glTexCoord2f(0.0,0.0); glVertex3d(19,-2,-8);
  glTexCoord2f(2.0,0.0); glVertex3d(24,-2,-11);
  glTexCoord2f(2.0,2.0); glVertex3d(24,-3,-11);
  glTexCoord2f(0.0,2.0); glVertex3d(19,-3,-8);
  glTexCoord2f(0.0,0.0); glVertex3d(19,-3,-5);
  glTexCoord2f(2.0,0.0); glVertex3d(26,-3,-9);
  glTexCoord2f(2.0,2.0); glVertex3d(26,-4,-9);
  glTexCoord2f(0.0,2.0); glVertex3d(19,-4,-5);
  glEnd();
  //sides
  glBindTexture(GL_TEXTURE_2D,texture[9]);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0,0.0); glVertex3d(19,-3,-8);
  glTexCoord2f(2.5,0.0); glVertex3d(24,-3,-11);
  glTexCoord2f(2.5,2.5); glVertex3d(26,-3,-9);
  glTexCoord2f(0.0,2.5); glVertex3d(19,-3,-5);
  glTexCoord2f(0.0,0.0); glVertex3d(19,-4,-5);
  glTexCoord2f(2.5,0.0); glVertex3d(26,-4,-9);
  glTexCoord2f(2.5,2.5); glVertex3d(26,-4,-6);
  glTexCoord2f(0.0,2.5); glVertex3d(21,-4,-3);
  glEnd();
  //moat ramp
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glBegin(GL_QUADS);
  glTexCoord2f(5.0,0.0); glVertex3d(14,0,-29);
  glTexCoord2f(5.0,5.0); glVertex3d(20,0,-29);
  glTexCoord2f(0.0,5.0); glVertex3d(20,-2,-23);
  glTexCoord2f(0.0,0.0); glVertex3d(14,-2,-23);
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

static void water(double x,double y,double z,
                      double dx,double dy, double dz,
                      double th)
{
  //  Set specular color to white
  float white[] = {1,1,1,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
  //  Save transformation
  glPushMatrix();
  //  Offset, scale and rotate
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  //  Enable textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
  glColor4f(0.2,0.2,0.5,150);
  glBindTexture(GL_TEXTURE_2D,texture[17]);
  //Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0); glVertex3d(30,-1,-34);
  glTexCoord2f(20.0,0.0); glVertex3d(30,-2,10);
  glTexCoord2f(20.0,20.0); glVertex3d(-18,-1,10);
  glTexCoord2f(0.0,20.0); glVertex3d(-18,-1,-34);
  glEnd();
  //waterfall
  glBegin(GL_QUADS);
  //front top
  glTexCoord2f(0.0,1.0); glVertex3d(-22,8,-23);
  glTexCoord2f(1.0,1.0); glVertex3d(-21,8,-26);
  glTexCoord2f(1.0,0.0); glVertex3d(-17,5,-25);
  glTexCoord2f(0.0,0.0); glVertex3d(-18,5,-23);
  //front middle
  glTexCoord2f(0.0,1.0); glVertex3d(-18,5,-23);
  glTexCoord2f(1.0,1.0); glVertex3d(-17,5,-25);
  glTexCoord2f(1.0,0.0); glVertex3d(-15,2,-24);
  glTexCoord2f(0.0,0.0); glVertex3d(-16,2,-21);
  //front bottom
  glTexCoord2f(0.0,1.0); glVertex3d(-16,2,-21);
  glTexCoord2f(1.0,1.0); glVertex3d(-15,2,-24);
  glTexCoord2f(1.0,0.0); glVertex3d(-12,-1,-23);
  glTexCoord2f(0.0,0.0); glVertex3d(-14,-1,-19);
  //left bottom
  glTexCoord2f(0.0,1.0); glVertex3d(-19,2,-20);
  glTexCoord2f(1.0,1.0); glVertex3d(-16,2,-21);
  glTexCoord2f(1.0,0.0); glVertex3d(-14,-1,-19);
  glTexCoord2f(0.0,0.0); glVertex3d(-17,-1,-17);
  //left top
  glTexCoord2f(0.0,1.0); glVertex3d(-22,8,-23);
  glTexCoord2f(1.0,1.0); glVertex3d(-18,5,-23);
  glTexCoord2f(1.0,0.0); glVertex3d(-16,2,-21);
  glTexCoord2f(0.0,0.0); glVertex3d(-19,2,-20);
  //right bottom
  glTexCoord2f(0.0,1.0); glVertex3d(-15,2,-24);
  glTexCoord2f(1.0,1.0); glVertex3d(-17,2,-26);
  glTexCoord2f(1.0,0.0); glVertex3d(-15,-1,-26);
  glTexCoord2f(0.0,0.0); glVertex3d(-12,-1,-23);
  //right top
  glTexCoord2f(0.0,1.0); glVertex3d(-17,5,-25);
  glTexCoord2f(1.0,1.0); glVertex3d(-21,8,-26);
  glTexCoord2f(1.0,0.0); glVertex3d(-17,2,-26);
  glTexCoord2f(0.0,0.0); glVertex3d(-15,2,-24);
  glEnd();
  //  Undo transformations
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}

static void skyBox(double D)
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,texture[18]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,texture[19]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,texture[20]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,texture[21]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,texture[22]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,+D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,+D,+D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,texture[23]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
    glEnd();
}
/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    //  Undo previous transformations
    glLoadIdentity();

    //third person camera
    // double Ex = -2*dim*Sin(th)*Cos(ph);
    // double Ey = +2*dim        *Sin(ph);
    // double Ez = +2*dim*Cos(th)*Cos(ph);
    // gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);

    //first person camera
    //Controls: UP(move up) DOWN(move down) LEFT(rotate left) RIGHT(rotate right)
    //w(move forward) s(move backward)
    gluLookAt(xAxis,yAxis,zAxis , xAxis+sin(angle),yAxis,zAxis-cos(angle) , 0,1,0);
    //  Translate intensity to color vectors
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    //  Light position
    float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),0};
    //  Draw light position as ball (still no lighting here)
    glColor3f(1,1,1);
    ball(Position[0],Position[1],Position[2] , 0.5);
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  Enable light 0
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);

    //Drawing the scene
    //draws the castle
    castle(5,0,-23 , 1,1,1 ,0);
    //draws the moat
    moat(0,0,0 , 1,1,1 ,0);
    //draws all of the grass in the front section
    tri(grassTri1,6,41, 0,0,0 , 1,1,1 , 0);
    //draws the path in the front section
    tri(pathTri1,7,30, 0,0,0 , 1,1,1 ,0);
    //draws the beach
    tri(beachTri,8,7, 0,0,0 , 1,1,1, 0);
    //draws the path in the side section
    tri(pathTri2,7,9, 26,-1,-6, 1,1,1, 0);
    //draws the grass in the side section
    tri(grassTri2,6,9, 26,-1,-6, 1,1,1, 0);
    //draws the wood bridge
    woodBridge(19,0,-8 , 1,1,1 ,0);
    //draws the wall in the moat
    quad(wallQuad1,15,12,1, 0,0,0, 1,1,1, 0);
    //draws the brick wall in the moat
    quad(brickWallQuad,10,3,3, 26,-1,-6, 1,1,1, 0);
    //draws the wall around the pond
    quad(wallQuad2,15,6,1, 0,0,0, 1,1,1, 0);
    //draws the wall in the side section
    quad(grassWallQuad1,16,3,1, 26,-1,-6, 1,1,1, 0);
    //draws the main wall around the scene
    quad(grassWallQuad2,16,16,1, 0,0,0, 1,1,1, 0);
    //draws the back of the waterfall
    quad(waterFallBack,15,1,1, 0,0,0, 1,1,1, 0);

    glDisable(GL_LIGHTING);
    //draws all of the water
    water(0,0,0, 1,1,1, 0);
    skyBox(100);

    glColor3f(1,1,1);
    //  Five pixels from the lower left corner of the window
    glWindowPos2i(5,5);
    //  Render the scene
    ErrCheck("display");
    glFlush();
    //  Make the rendered scene visible
    glutSwapBuffers();
}

/*
 *  GLUT calls this toutine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - rotates camera to the right
   if (key == GLUT_KEY_RIGHT){
      th += 5;
      angle += 0.1f;
   }
   //  Left arrow key - rotates camera to the left
   else if (key == GLUT_KEY_LEFT){
      th -= 5;
      angle -= 0.1f;
   }
   //  Up arrow key - moves camera up
   else if (key == GLUT_KEY_UP){
      ph += 5;
      yAxis += 1;
   }
   //  Down arrow key - moves camera down
   else if (key == GLUT_KEY_DOWN){
      ph -= 5;
      yAxis -= 1;
   }
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //Update projection
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   // w key - moves camera forward
   else if(ch == 'w'){
     xAxis += sin(angle);
     zAxis += -cos(angle);
   }
   // s key - moves camera backward
   else if(ch == 's'){
     xAxis -= sin(angle);
     zAxis -= -cos(angle);
   }
   Project(45,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
 void reshape(int width,int height)
 {
    //  Ratio of the width to the height of the window
    asp = (height>0) ? (double)width/height : 1;
    //  Set the viewport to the entire window
    glViewport(0,0, width,height);
    //  Set projection
    Project(45,asp,dim);
 }



int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Garrett Hite");
   //  Set callbacks
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //Load textures
   texture[0] = LoadTexBMP("Brick.bmp");
   texture[1] = LoadTexBMP("Roof.bmp");
   texture[2] = LoadTexBMP("CastleTrim.bmp");
   texture[3] = LoadTexBMP("PeachWindow1.bmp");
   texture[4] = LoadTexBMP("PeachWindow2.bmp");
   texture[5] = LoadTexBMP("window.bmp");
   texture[6] = LoadTexBMP("Grass.bmp");
   texture[7] = LoadTexBMP("path.bmp");
   texture[8] = LoadTexBMP("beach.bmp");
   texture[9] = LoadTexBMP("moatGround.bmp");
   texture[10] = LoadTexBMP("brickWall.bmp");
   texture[11] = LoadTexBMP("bridgeBrick.bmp");
   texture[12] = LoadTexBMP("bridgeRail.bmp");
   texture[13] = LoadTexBMP("woodTop.bmp");
   texture[14] = LoadTexBMP("woodSide.bmp");
   texture[15] = LoadTexBMP("cliffSide.bmp");
   texture[16] = LoadTexBMP("grass2.bmp");
   texture[17] = LoadTexBMP("water.bmp");
   texture[18] = LoadTexBMP("SkyBox1.bmp");
   texture[19] = LoadTexBMP("SkyBox2.bmp");
   texture[20] = LoadTexBMP("SkyBox3.bmp");
   texture[21] = LoadTexBMP("SkyBox4.bmp");
   texture[22] = LoadTexBMP("SkyBox5.bmp");
   texture[23] = LoadTexBMP("SkyBox6.bmp");
   texture[24] = LoadTexBMP("door.bmp");

   ErrCheck("init");
   glutMainLoop();
   return 0;
}
