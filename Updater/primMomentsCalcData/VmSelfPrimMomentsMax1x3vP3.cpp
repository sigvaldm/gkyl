#include <PrimMomentsModDecl.h> 
 
using namespace Eigen; 
 
void VmSelfPrimMoments1x3vMax_P3(binOpData_t *data, const double *m0, const double *m1, const double *m2, const double *cM, const double *cE, double *u, double *vtSq) 
{ 
  // m0,m1,m2: moments of the distribution function. 
  // cM, cE:   vtSq*cM and vtSq*cE are corrections to u and vtSq, respectively. 
  // u:        velocity. 
  // vtSq:     squared thermal speed, sqrt(T/m). 
 
  // If a corner value is below zero, use cell average m0.
  bool cellAvg = false;
  if (-0.5*(3.741657386773942*m0[3]-3.16227766016838*m0[2]+2.449489742783178*m0[1]-1.414213562373095*m0[0]) < 0) cellAvg = true; 
  if (0.5*(3.741657386773942*m0[3]+3.16227766016838*m0[2]+2.449489742783178*m0[1]+1.414213562373095*m0[0]) < 0) cellAvg = true; 
  if (-0.5*(3.741657386773942*m2[3]-3.16227766016838*m2[2]+2.449489742783178*m2[1]-1.414213562373095*m2[0]) < 0) cellAvg = true; 
  if (0.5*(3.741657386773942*m2[3]+3.16227766016838*m2[2]+2.449489742783178*m2[1]+1.414213562373095*m2[0]) < 0) cellAvg = true; 
 
  double m0r[4]; 
  double m1r[12]; 
  double cMr[12]; 
  double cEr[4]; 
  double m2r[4]; 
  if (cellAvg) { 
    m0r[0] = m0[0]; 
    m0r[1] = 0.0; 
    m0r[2] = 0.0; 
    m0r[3] = 0.0; 
    m1r[0] = m1[0]; 
    m1r[1] = 0.0; 
    m1r[2] = 0.0; 
    m1r[3] = 0.0; 
    cMr[0] = cM[0]; 
    cMr[1] = 0.0; 
    cMr[2] = 0.0; 
    cMr[3] = 0.0; 
    m1r[4] = m1[4]; 
    m1r[5] = 0.0; 
    m1r[6] = 0.0; 
    m1r[7] = 0.0; 
    cMr[4] = cM[4]; 
    cMr[5] = 0.0; 
    cMr[6] = 0.0; 
    cMr[7] = 0.0; 
    m1r[8] = m1[8]; 
    m1r[9] = 0.0; 
    m1r[10] = 0.0; 
    m1r[11] = 0.0; 
    cMr[8] = cM[8]; 
    cMr[9] = 0.0; 
    cMr[10] = 0.0; 
    cMr[11] = 0.0; 
    cEr[0] = cE[0]; 
    cEr[1] = 0.0; 
    cEr[2] = 0.0; 
    cEr[3] = 0.0; 
    m2r[0] = m2[0]; 
    m2r[1] = 0.0; 
    m2r[2] = 0.0; 
    m2r[3] = 0.0; 
  } else { 
    m0r[0] = m0[0]; 
    m0r[1] = m0[1]; 
    m0r[2] = m0[2]; 
    m0r[3] = m0[3]; 
    m1r[0] = m1[0]; 
    m1r[1] = m1[1]; 
    m1r[2] = m1[2]; 
    m1r[3] = m1[3]; 
    m1r[4] = m1[4]; 
    m1r[5] = m1[5]; 
    m1r[6] = m1[6]; 
    m1r[7] = m1[7]; 
    m1r[8] = m1[8]; 
    m1r[9] = m1[9]; 
    m1r[10] = m1[10]; 
    m1r[11] = m1[11]; 
    cMr[0] = cM[0]; 
    cMr[1] = cM[1]; 
    cMr[2] = cM[2]; 
    cMr[3] = cM[3]; 
    cMr[4] = cM[4]; 
    cMr[5] = cM[5]; 
    cMr[6] = cM[6]; 
    cMr[7] = cM[7]; 
    cMr[8] = cM[8]; 
    cMr[9] = cM[9]; 
    cMr[10] = cM[10]; 
    cMr[11] = cM[11]; 
    cEr[0] = cE[0]; 
    cEr[1] = cE[1]; 
    cEr[2] = cE[2]; 
    cEr[3] = cE[3]; 
    m2r[0] = m2[0]; 
    m2r[1] = m2[1]; 
    m2r[2] = m2[2]; 
    m2r[3] = m2[3]; 
  } 
 
  // Declare Eigen matrix and vectors for weak division. 
  data->AEM_S = Eigen::MatrixXd::Zero(16,16); 
 
  // ....... Block from weak multiply of uX and m0  .......... // 
  data->AEM_S(0,0) = 0.7071067811865475*m0r[0]; 
  data->AEM_S(0,1) = 0.7071067811865475*m0r[1]; 
  data->AEM_S(0,2) = 0.7071067811865475*m0r[2]; 
  data->AEM_S(0,3) = 0.7071067811865475*m0r[3]; 
  data->AEM_S(1,0) = 0.7071067811865475*m0r[1]; 
  data->AEM_S(1,1) = 0.6324555320336759*m0r[2]+0.7071067811865475*m0r[0]; 
  data->AEM_S(1,2) = 0.6210590034081186*m0r[3]+0.6324555320336759*m0r[1]; 
  data->AEM_S(1,3) = 0.6210590034081186*m0r[2]; 
  data->AEM_S(2,0) = 0.7071067811865475*m0r[2]; 
  data->AEM_S(2,1) = 0.6210590034081186*m0r[3]+0.6324555320336759*m0r[1]; 
  data->AEM_S(2,2) = 0.4517539514526256*m0r[2]+0.7071067811865475*m0r[0]; 
  data->AEM_S(2,3) = 0.421637021355784*m0r[3]+0.6210590034081186*m0r[1]; 
  data->AEM_S(3,0) = 0.7071067811865475*m0r[3]; 
  data->AEM_S(3,1) = 0.6210590034081186*m0r[2]; 
  data->AEM_S(3,2) = 0.421637021355784*m0r[3]+0.6210590034081186*m0r[1]; 
  data->AEM_S(3,3) = 0.421637021355784*m0r[2]+0.7071067811865475*m0r[0]; 
 
  // ....... Block from correction to uX .......... // 
  data->AEM_S(0,12) = -0.7071067811865475*cMr[0]; 
  data->AEM_S(0,13) = -0.7071067811865475*cMr[1]; 
  data->AEM_S(0,14) = -0.7071067811865475*cMr[2]; 
  data->AEM_S(0,15) = -0.7071067811865475*cMr[3]; 
  data->AEM_S(1,12) = -0.7071067811865475*cMr[1]; 
  data->AEM_S(1,13) = (-0.6324555320336759*cMr[2])-0.7071067811865475*cMr[0]; 
  data->AEM_S(1,14) = (-0.6210590034081186*cMr[3])-0.6324555320336759*cMr[1]; 
  data->AEM_S(1,15) = -0.6210590034081186*cMr[2]; 
  data->AEM_S(2,12) = -0.7071067811865475*cMr[2]; 
  data->AEM_S(2,13) = (-0.6210590034081186*cMr[3])-0.6324555320336759*cMr[1]; 
  data->AEM_S(2,14) = (-0.4517539514526256*cMr[2])-0.7071067811865475*cMr[0]; 
  data->AEM_S(2,15) = (-0.421637021355784*cMr[3])-0.6210590034081186*cMr[1]; 
  data->AEM_S(3,12) = -0.7071067811865475*cMr[3]; 
  data->AEM_S(3,13) = -0.6210590034081186*cMr[2]; 
  data->AEM_S(3,14) = (-0.421637021355784*cMr[3])-0.6210590034081186*cMr[1]; 
  data->AEM_S(3,15) = (-0.421637021355784*cMr[2])-0.7071067811865475*cMr[0]; 
 
  // ....... Block from weak multiply of uX and m1X  .......... // 
  data->AEM_S(12,0) = 0.7071067811865475*m1r[0]; 
  data->AEM_S(12,1) = 0.7071067811865475*m1r[1]; 
  data->AEM_S(12,2) = 0.7071067811865475*m1r[2]; 
  data->AEM_S(12,3) = 0.7071067811865475*m1r[3]; 
  data->AEM_S(13,0) = 0.7071067811865475*m1r[1]; 
  data->AEM_S(13,1) = 0.6324555320336759*m1r[2]+0.7071067811865475*m1r[0]; 
  data->AEM_S(13,2) = 0.6210590034081186*m1r[3]+0.6324555320336759*m1r[1]; 
  data->AEM_S(13,3) = 0.6210590034081186*m1r[2]; 
  data->AEM_S(14,0) = 0.7071067811865475*m1r[2]; 
  data->AEM_S(14,1) = 0.6210590034081186*m1r[3]+0.6324555320336759*m1r[1]; 
  data->AEM_S(14,2) = 0.4517539514526256*m1r[2]+0.7071067811865475*m1r[0]; 
  data->AEM_S(14,3) = 0.421637021355784*m1r[3]+0.6210590034081186*m1r[1]; 
  data->AEM_S(15,0) = 0.7071067811865475*m1r[3]; 
  data->AEM_S(15,1) = 0.6210590034081186*m1r[2]; 
  data->AEM_S(15,2) = 0.421637021355784*m1r[3]+0.6210590034081186*m1r[1]; 
  data->AEM_S(15,3) = 0.421637021355784*m1r[2]+0.7071067811865475*m1r[0]; 
 
  // ....... Block from weak multiply of uY and m0  .......... // 
  data->AEM_S(4,4) = 0.7071067811865475*m0r[0]; 
  data->AEM_S(4,5) = 0.7071067811865475*m0r[1]; 
  data->AEM_S(4,6) = 0.7071067811865475*m0r[2]; 
  data->AEM_S(4,7) = 0.7071067811865475*m0r[3]; 
  data->AEM_S(5,4) = 0.7071067811865475*m0r[1]; 
  data->AEM_S(5,5) = 0.6324555320336759*m0r[2]+0.7071067811865475*m0r[0]; 
  data->AEM_S(5,6) = 0.6210590034081186*m0r[3]+0.6324555320336759*m0r[1]; 
  data->AEM_S(5,7) = 0.6210590034081186*m0r[2]; 
  data->AEM_S(6,4) = 0.7071067811865475*m0r[2]; 
  data->AEM_S(6,5) = 0.6210590034081186*m0r[3]+0.6324555320336759*m0r[1]; 
  data->AEM_S(6,6) = 0.4517539514526256*m0r[2]+0.7071067811865475*m0r[0]; 
  data->AEM_S(6,7) = 0.421637021355784*m0r[3]+0.6210590034081186*m0r[1]; 
  data->AEM_S(7,4) = 0.7071067811865475*m0r[3]; 
  data->AEM_S(7,5) = 0.6210590034081186*m0r[2]; 
  data->AEM_S(7,6) = 0.421637021355784*m0r[3]+0.6210590034081186*m0r[1]; 
  data->AEM_S(7,7) = 0.421637021355784*m0r[2]+0.7071067811865475*m0r[0]; 
 
  // ....... Block from correction to uY .......... // 
  data->AEM_S(4,12) = -0.7071067811865475*cMr[4]; 
  data->AEM_S(4,13) = -0.7071067811865475*cMr[5]; 
  data->AEM_S(4,14) = -0.7071067811865475*cMr[6]; 
  data->AEM_S(4,15) = -0.7071067811865475*cMr[7]; 
  data->AEM_S(5,12) = -0.7071067811865475*cMr[5]; 
  data->AEM_S(5,13) = (-0.6324555320336759*cMr[6])-0.7071067811865475*cMr[4]; 
  data->AEM_S(5,14) = (-0.6210590034081186*cMr[7])-0.6324555320336759*cMr[5]; 
  data->AEM_S(5,15) = -0.6210590034081186*cMr[6]; 
  data->AEM_S(6,12) = -0.7071067811865475*cMr[6]; 
  data->AEM_S(6,13) = (-0.6210590034081186*cMr[7])-0.6324555320336759*cMr[5]; 
  data->AEM_S(6,14) = (-0.4517539514526256*cMr[6])-0.7071067811865475*cMr[4]; 
  data->AEM_S(6,15) = (-0.421637021355784*cMr[7])-0.6210590034081186*cMr[5]; 
  data->AEM_S(7,12) = -0.7071067811865475*cMr[7]; 
  data->AEM_S(7,13) = -0.6210590034081186*cMr[6]; 
  data->AEM_S(7,14) = (-0.421637021355784*cMr[7])-0.6210590034081186*cMr[5]; 
  data->AEM_S(7,15) = (-0.421637021355784*cMr[6])-0.7071067811865475*cMr[4]; 
 
  // ....... Block from weak multiply of uY and m1Y  .......... // 
  data->AEM_S(12,4) = 0.7071067811865475*m1r[4]; 
  data->AEM_S(12,5) = 0.7071067811865475*m1r[5]; 
  data->AEM_S(12,6) = 0.7071067811865475*m1r[6]; 
  data->AEM_S(12,7) = 0.7071067811865475*m1r[7]; 
  data->AEM_S(13,4) = 0.7071067811865475*m1r[5]; 
  data->AEM_S(13,5) = 0.6324555320336759*m1r[6]+0.7071067811865475*m1r[4]; 
  data->AEM_S(13,6) = 0.6210590034081186*m1r[7]+0.6324555320336759*m1r[5]; 
  data->AEM_S(13,7) = 0.6210590034081186*m1r[6]; 
  data->AEM_S(14,4) = 0.7071067811865475*m1r[6]; 
  data->AEM_S(14,5) = 0.6210590034081186*m1r[7]+0.6324555320336759*m1r[5]; 
  data->AEM_S(14,6) = 0.4517539514526256*m1r[6]+0.7071067811865475*m1r[4]; 
  data->AEM_S(14,7) = 0.421637021355784*m1r[7]+0.6210590034081186*m1r[5]; 
  data->AEM_S(15,4) = 0.7071067811865475*m1r[7]; 
  data->AEM_S(15,5) = 0.6210590034081186*m1r[6]; 
  data->AEM_S(15,6) = 0.421637021355784*m1r[7]+0.6210590034081186*m1r[5]; 
  data->AEM_S(15,7) = 0.421637021355784*m1r[6]+0.7071067811865475*m1r[4]; 
 
  // ....... Block from weak multiply of uZ and m0  .......... // 
  data->AEM_S(8,8) = 0.7071067811865475*m0r[0]; 
  data->AEM_S(8,9) = 0.7071067811865475*m0r[1]; 
  data->AEM_S(8,10) = 0.7071067811865475*m0r[2]; 
  data->AEM_S(8,11) = 0.7071067811865475*m0r[3]; 
  data->AEM_S(9,8) = 0.7071067811865475*m0r[1]; 
  data->AEM_S(9,9) = 0.6324555320336759*m0r[2]+0.7071067811865475*m0r[0]; 
  data->AEM_S(9,10) = 0.6210590034081186*m0r[3]+0.6324555320336759*m0r[1]; 
  data->AEM_S(9,11) = 0.6210590034081186*m0r[2]; 
  data->AEM_S(10,8) = 0.7071067811865475*m0r[2]; 
  data->AEM_S(10,9) = 0.6210590034081186*m0r[3]+0.6324555320336759*m0r[1]; 
  data->AEM_S(10,10) = 0.4517539514526256*m0r[2]+0.7071067811865475*m0r[0]; 
  data->AEM_S(10,11) = 0.421637021355784*m0r[3]+0.6210590034081186*m0r[1]; 
  data->AEM_S(11,8) = 0.7071067811865475*m0r[3]; 
  data->AEM_S(11,9) = 0.6210590034081186*m0r[2]; 
  data->AEM_S(11,10) = 0.421637021355784*m0r[3]+0.6210590034081186*m0r[1]; 
  data->AEM_S(11,11) = 0.421637021355784*m0r[2]+0.7071067811865475*m0r[0]; 
 
  // ....... Block from correction to uZ .......... // 
  data->AEM_S(8,12) = -0.7071067811865475*cMr[8]; 
  data->AEM_S(8,13) = -0.7071067811865475*cMr[9]; 
  data->AEM_S(8,14) = -0.7071067811865475*cMr[10]; 
  data->AEM_S(8,15) = -0.7071067811865475*cMr[11]; 
  data->AEM_S(9,12) = -0.7071067811865475*cMr[9]; 
  data->AEM_S(9,13) = (-0.6324555320336759*cMr[10])-0.7071067811865475*cMr[8]; 
  data->AEM_S(9,14) = (-0.6210590034081186*cMr[11])-0.6324555320336759*cMr[9]; 
  data->AEM_S(9,15) = -0.6210590034081186*cMr[10]; 
  data->AEM_S(10,12) = -0.7071067811865475*cMr[10]; 
  data->AEM_S(10,13) = (-0.6210590034081186*cMr[11])-0.6324555320336759*cMr[9]; 
  data->AEM_S(10,14) = (-0.4517539514526256*cMr[10])-0.7071067811865475*cMr[8]; 
  data->AEM_S(10,15) = (-0.421637021355784*cMr[11])-0.6210590034081186*cMr[9]; 
  data->AEM_S(11,12) = -0.7071067811865475*cMr[11]; 
  data->AEM_S(11,13) = -0.6210590034081186*cMr[10]; 
  data->AEM_S(11,14) = (-0.421637021355784*cMr[11])-0.6210590034081186*cMr[9]; 
  data->AEM_S(11,15) = (-0.421637021355784*cMr[10])-0.7071067811865475*cMr[8]; 
 
  // ....... Block from weak multiply of uZ and m1Z  .......... // 
  data->AEM_S(12,8) = 0.7071067811865475*m1r[8]; 
  data->AEM_S(12,9) = 0.7071067811865475*m1r[9]; 
  data->AEM_S(12,10) = 0.7071067811865475*m1r[10]; 
  data->AEM_S(12,11) = 0.7071067811865475*m1r[11]; 
  data->AEM_S(13,8) = 0.7071067811865475*m1r[9]; 
  data->AEM_S(13,9) = 0.6324555320336759*m1r[10]+0.7071067811865475*m1r[8]; 
  data->AEM_S(13,10) = 0.6210590034081186*m1r[11]+0.6324555320336759*m1r[9]; 
  data->AEM_S(13,11) = 0.6210590034081186*m1r[10]; 
  data->AEM_S(14,8) = 0.7071067811865475*m1r[10]; 
  data->AEM_S(14,9) = 0.6210590034081186*m1r[11]+0.6324555320336759*m1r[9]; 
  data->AEM_S(14,10) = 0.4517539514526256*m1r[10]+0.7071067811865475*m1r[8]; 
  data->AEM_S(14,11) = 0.421637021355784*m1r[11]+0.6210590034081186*m1r[9]; 
  data->AEM_S(15,8) = 0.7071067811865475*m1r[11]; 
  data->AEM_S(15,9) = 0.6210590034081186*m1r[10]; 
  data->AEM_S(15,10) = 0.421637021355784*m1r[11]+0.6210590034081186*m1r[9]; 
  data->AEM_S(15,11) = 0.421637021355784*m1r[10]+0.7071067811865475*m1r[8]; 
 
  // ....... Block from correction to vtSq .......... // 
  data->AEM_S(12,12) = 2.121320343559642*m0r[0]-0.7071067811865475*cEr[0]; 
  data->AEM_S(12,13) = 2.121320343559642*m0r[1]-0.7071067811865475*cEr[1]; 
  data->AEM_S(12,14) = 2.121320343559642*m0r[2]-0.7071067811865475*cEr[2]; 
  data->AEM_S(12,15) = 2.121320343559642*m0r[3]-0.7071067811865475*cEr[3]; 
  data->AEM_S(13,12) = 2.121320343559642*m0r[1]-0.7071067811865475*cEr[1]; 
  data->AEM_S(13,13) = 1.897366596101028*m0r[2]-0.6324555320336759*cEr[2]+2.121320343559642*m0r[0]-0.7071067811865475*cEr[0]; 
  data->AEM_S(13,14) = 1.863177010224355*m0r[3]-0.6210590034081186*cEr[3]+1.897366596101028*m0r[1]-0.6324555320336759*cEr[1]; 
  data->AEM_S(13,15) = 1.863177010224355*m0r[2]-0.6210590034081186*cEr[2]; 
  data->AEM_S(14,12) = 2.121320343559642*m0r[2]-0.7071067811865475*cEr[2]; 
  data->AEM_S(14,13) = 1.863177010224355*m0r[3]-0.6210590034081186*cEr[3]+1.897366596101028*m0r[1]-0.6324555320336759*cEr[1]; 
  data->AEM_S(14,14) = 1.355261854357877*m0r[2]-0.4517539514526256*cEr[2]+2.121320343559642*m0r[0]-0.7071067811865475*cEr[0]; 
  data->AEM_S(14,15) = 1.264911064067352*m0r[3]-0.421637021355784*cEr[3]+1.863177010224355*m0r[1]-0.6210590034081186*cEr[1]; 
  data->AEM_S(15,12) = 2.121320343559642*m0r[3]-0.7071067811865475*cEr[3]; 
  data->AEM_S(15,13) = 1.863177010224355*m0r[2]-0.6210590034081186*cEr[2]; 
  data->AEM_S(15,14) = 1.264911064067352*m0r[3]-0.421637021355784*cEr[3]+1.863177010224355*m0r[1]-0.6210590034081186*cEr[1]; 
  data->AEM_S(15,15) = 1.264911064067352*m0r[2]-0.421637021355784*cEr[2]+2.121320343559642*m0r[0]-0.7071067811865475*cEr[0]; 
 
  // Set other entries to 0. // 
  data->AEM_S.block<4,8>(0,4).setZero(); 
  data->AEM_S.block<8,4>(4,0).setZero(); 
  data->AEM_S.block<4,4>(4,8).setZero(); 
  data->AEM_S.block<4,4>(8,4).setZero(); 
 
  // ....... RHS vector is composed of m1 and m2 .......... // 
  data->BEV_S << m1r[0],m1r[1],m1r[2],m1r[3],m1r[4],m1r[5],m1r[6],m1r[7],m1r[8],m1r[9],m1r[10],m1r[11],m2r[0],m2r[1],m2r[2],m2r[3]; 
 
  data->u_S = data->AEM_S.colPivHouseholderQr().solve(data->BEV_S); 
 
  Eigen::Map<VectorXd>(u,12,1) = data->u_S.segment<12>(0); 
 
  Eigen::Map<VectorXd>(vtSq,4,1) = data->u_S.segment<4>(12); 
 
} 
 
