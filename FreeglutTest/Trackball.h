#pragma once



/*
* This size should really be based on the distance from the center of
* rotation to the point on the object underneath the mouse.  That
* point would then track the mouse as closely as possible.  This is a
* simple example, though, so that is left as an Exercise for the
* Programmer.
*/
#define TRACKBALLSIZE  (0.8f)

/*
* Local function prototypes (not defined in trackball.h)
*/
static float tb_project_to_sphere(float, float, float);
static void normalize_quat(float[4]);

extern void vzero(float *v);

extern void vset(float *v, float x, float y, float z);

extern void vsub(const float *src1, const float *src2, float *dst);

extern void vcopy(const float *v1, float *v2);

extern void vcross(const float *v1, const float *v2, float *cross);

extern float vlength(const float *v);

extern void vscale(float *v, float div);

extern void vnormal(float *v);

extern float vdot(const float *v1, const float *v2);

extern void vadd(const float *src1, const float *src2, float *dst);

/*
* Ok, simulate a track-ball.  Project the points onto the virtual
* trackball, then figure out the axis of rotation, which is the cross
* product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
* Note:  This is a deformed trackball-- is a trackball in the center,
* but is deformed into a hyperbolic sheet of rotation away from the
* center.  This particular function was chosen after trying out
* several variations.
*
* It is assumed that the arguments to this routine are in the range
* (-1.0 ... 1.0)
*/
extern void trackball(float q[4], float p1x, float p1y, float p2x, float p2y);

/*
*  Given an axis and angle, compute quaternion.
*/
extern void axis_to_quat(float a[3], float phi, float q[4]);

/*
* Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
* if we are away from the center of the sphere.
*/
static float tb_project_to_sphere(float r, float x, float y);

/*
* Given two rotations, e1 and e2, expressed as quaternion rotations,
* figure out the equivalent single rotation and stuff it into dest.
*
* This routine also normalizes the result every RENORMCOUNT times it is
* called, to keep error from creeping in.
*
* NOTE: This routine is written so that q1 or q2 may be the same
* as dest (or each other).
*/

#define RENORMCOUNT 97

extern void add_quats(float q1[4], float q2[4], float dest[4]);

/*
* Quaternions always obey:  a^2 + b^2 + c^2 + d^2 = 1.0
* If they don't add up to 1.0, dividing by their magnitued will
* renormalize them.
*
* Note: See the following for more information on quaternions:
*
* - Shoemake, K., Animating rotation with quaternion curves, Computer
*   Graphics 19, No 3 (Proc. SIGGRAPH'85), 245-254, 1985.
* - Pletinckx, D., Quaternion calculus as a basic tool in computer
*   graphics, The Visual Computer 5, 2-13, 1989.
*/
static void normalize_quat(float q[4]);

/*
* Build a rotation matrix, given a quaternion rotation.
*
*/
extern void build_rotmatrix(float m[4][4], float q[4]);

/* Fortran wrappers */
extern void trackball_(float *q, float *p1x, float *p1y, float *p2x, float *p2y);

extern void add_quats__(float q1[4], float q2[4], float dest[4]);

extern void build_rotmatrix__(float m[4][4], float q[4]);

extern void pan(float x, float y, float px, float py, float* t);
extern void buildTranslateMatrix(float m[4][4],float* t);

extern void scale(int delta, float px, float py, float* scale);
extern void buildScaleMatrix(float m[4][4], float* scale);

extern void scale_t(int delta, float px, float py, float * scale);

extern void buildScale_tMatrix(float m[4][4], float* t);

