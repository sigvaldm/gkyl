#include <GyrokineticModDecl.h> 
double GyrokineticGenGeoVol1x2vTensorP2_Bvars(const double q_, const double m_, const double *w, const double *dxv, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *f, double *out) 
{ 
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
  // q_,m_: species charge and mass.
  // w[NDIM]: cell-center.
  // dxv[NDIM]: cell length.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // f: Distribution function.
  // out: output increment.

  double wx = w[0];
  double rdx2 = 2.0/dxv[0];
  double wvpar = w[1];
  double rdvpar2 = 2.0/dxv[1];
  double wmu = w[2];
  double rdmu2 = 2.0/dxv[2];

  double wxSq = w[0]*w[0];
  double rdx2Sq = rdx2*rdx2;
  double wvparSq = w[1]*w[1];
  double rdvpar2Sq = rdvpar2*rdvpar2;
  double wmuSq = w[2]*w[2];
  double rdmu2Sq = rdmu2*rdmu2;

  double hamil[27]; 
  hamil[0] = (0.2357022603955158*(3.0*rdvpar2Sq*(2.0*m_*wvparSq+2.828427124746191*(bmag[0]*wmu+phi[0]*q_))+2.0*m_))/rdvpar2Sq; 
  hamil[1] = 2.0*phi[1]*q_; 
  hamil[2] = (1.632993161855453*m_*wvpar)/rdvpar2; 
  hamil[3] = (1.154700538379252*bmag[0])/rdmu2; 
  hamil[7] = 2.0*phi[2]*q_; 
  hamil[8] = (0.421637021355784*m_)/rdvpar2Sq; 

  double BstarZdBmag[27]; 
  BstarZdBmag[0] = 1.414213562373095*cmag[0]*jacobTotInv[0]; 

  double cflFreq = 0.0; 
  double alphaL = 0.0; 
  double alphaR = 0.0; 
  double alphax[27]; 
  alphax[0] = (0.6123724356957944*BstarZdBmag[0]*hamil[2]*rdvpar2*rdx2)/m_; 
  alphax[2] = (1.369306393762915*BstarZdBmag[0]*hamil[8]*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = 0.1767766952966368*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.1767766952966368*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  double alphavpar[27]; 
  alphavpar[0] = -(0.6123724356957944*BstarZdBmag[0]*hamil[1]*rdvpar2*rdx2)/m_; 
  alphavpar[1] = -(1.369306393762915*BstarZdBmag[0]*hamil[7]*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = 0.1767766952966368*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.1767766952966368*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  out[1] += 0.6123724356957944*(alphax[2]*f[2]+alphax[0]*f[0]); 
  out[2] += 0.6123724356957944*(alphavpar[1]*f[1]+alphavpar[0]*f[0]); 
  out[4] += 0.1224744871391589*(4.47213595499958*(alphax[2]*f[8]+alphavpar[1]*f[7])+5.0*(alphax[0]*f[2]+f[0]*alphax[2]+alphavpar[0]*f[1]+f[0]*alphavpar[1])); 
  out[5] += 0.6123724356957944*(alphax[2]*f[6]+alphax[0]*f[3]); 
  out[6] += 0.6123724356957944*(alphavpar[1]*f[5]+alphavpar[0]*f[3]); 
  out[7] += 1.369306393762915*(alphax[2]*f[4]+alphax[0]*f[1]); 
  out[8] += 1.369306393762915*(alphavpar[1]*f[4]+alphavpar[0]*f[2]); 
  out[10] += 0.07071067811865474*(7.745966692414834*(alphax[2]*f[14]+alphavpar[1]*f[13])+8.660254037844386*(alphax[0]*f[6]+alphavpar[0]*f[5]+(alphax[2]+alphavpar[1])*f[3])); 
  out[11] += 0.07071067811865474*(17.32050807568877*alphax[2]*f[12]+8.660254037844387*alphavpar[0]*f[7]+19.36491673103708*alphax[0]*f[4]+f[1]*(19.36491673103708*alphax[2]+7.745966692414834*alphavpar[1])); 
  out[12] += 0.07071067811865474*(17.32050807568877*alphavpar[1]*f[11]+8.660254037844387*alphax[0]*f[8]+19.36491673103708*alphavpar[0]*f[4]+(7.745966692414834*alphax[2]+19.36491673103708*alphavpar[1])*f[2]); 
  out[13] += 1.369306393762915*(alphax[2]*f[10]+alphax[0]*f[5]); 
  out[14] += 1.369306393762915*(alphavpar[1]*f[10]+alphavpar[0]*f[6]); 
  out[15] += 0.07071067811865474*(8.660254037844386*alphax[2]*f[16]+8.660254037844387*alphax[0]*f[9]); 
  out[16] += 0.07071067811865474*(8.660254037844386*alphavpar[1]*f[15]+8.660254037844387*alphavpar[0]*f[9]); 
  out[17] += 0.07071067811865474*(17.32050807568877*alphax[2]*f[18]+8.660254037844387*alphavpar[0]*f[13]+19.36491673103709*alphax[0]*f[10]+(19.36491673103709*alphax[2]+7.745966692414834*alphavpar[1])*f[5]); 
  out[18] += 0.07071067811865474*(17.32050807568877*alphavpar[1]*f[17]+8.660254037844387*alphax[0]*f[14]+19.36491673103709*alphavpar[0]*f[10]+(7.745966692414834*alphax[2]+19.36491673103709*alphavpar[1])*f[6]); 
  out[19] += 0.07071067811865474*(7.745966692414834*(alphax[2]*f[22]+alphavpar[1]*f[21])+8.660254037844387*(alphax[0]*f[16]+alphavpar[0]*f[15])+8.660254037844386*(alphax[2]+alphavpar[1])*f[9]); 
  out[20] += 0.3535533905932737*(3.872983346207417*(alphax[0]*f[12]+alphavpar[0]*f[11])+3.464101615137754*(alphax[2]+alphavpar[1])*f[4]); 
  out[21] += 1.369306393762915*(alphax[2]*f[19]+alphax[0]*f[15]); 
  out[22] += 1.369306393762915*(alphavpar[1]*f[19]+alphavpar[0]*f[16]); 
  out[23] += 0.6123724356957944*(2.23606797749979*(alphax[0]*f[18]+alphavpar[0]*f[17])+2.0*(alphax[2]+alphavpar[1])*f[10]); 
  out[24] += 0.07071067811865474*(17.32050807568877*alphax[2]*f[25]+8.660254037844386*alphavpar[0]*f[21]+19.36491673103709*alphax[0]*f[19]+(19.36491673103708*alphax[2]+7.745966692414834*alphavpar[1])*f[15]); 
  out[25] += 0.07071067811865474*(17.32050807568877*alphavpar[1]*f[24]+8.660254037844386*alphax[0]*f[22]+19.36491673103709*alphavpar[0]*f[19]+(7.745966692414834*alphax[2]+19.36491673103708*alphavpar[1])*f[16]); 
  out[26] += 0.6123724356957944*(2.23606797749979*(alphax[0]*f[25]+alphavpar[0]*f[24])+2.0*(alphax[2]+alphavpar[1])*f[19]); 
  return cflFreq; 
} 
double GyrokineticGenGeoVol1x2vTensorP2_Bvarsx(const double q_, const double m_, const double *w, const double *dxv, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *f, double *out) 
{ 
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
  // q_,m_: species charge and mass.
  // w[NDIM]: cell-center.
  // dxv[NDIM]: cell length.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // f: Distribution function.
  // out: output increment.

  double wx = w[0];
  double rdx2 = 2.0/dxv[0];
  double wvpar = w[1];
  double rdvpar2 = 2.0/dxv[1];
  double wmu = w[2];
  double rdmu2 = 2.0/dxv[2];

  double wxSq = w[0]*w[0];
  double rdx2Sq = rdx2*rdx2;
  double wvparSq = w[1]*w[1];
  double rdvpar2Sq = rdvpar2*rdvpar2;
  double wmuSq = w[2]*w[2];
  double rdmu2Sq = rdmu2*rdmu2;

  double hamil[27]; 
  hamil[0] = (0.2357022603955158*(3.0*rdvpar2Sq*(2.0*m_*wvparSq+2.828427124746191*(bmag[0]*wmu+phi[0]*q_))+2.0*m_))/rdvpar2Sq; 
  hamil[1] = 2.0*(bmag[1]*wmu+phi[1]*q_); 
  hamil[2] = (1.632993161855453*m_*wvpar)/rdvpar2; 
  hamil[3] = (1.154700538379252*bmag[0])/rdmu2; 
  hamil[5] = (1.154700538379252*bmag[1])/rdmu2; 
  hamil[7] = 2.0*(bmag[2]*wmu+phi[2]*q_); 
  hamil[8] = (0.421637021355784*m_)/rdvpar2Sq; 
  hamil[13] = (1.154700538379251*bmag[2])/rdmu2; 

  double BstarZdBmag[27]; 
  BstarZdBmag[0] = (1.414213562373095*(1.732050807568877*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2*wvpar+(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0])*q_))/q_; 
  BstarZdBmag[1] = (0.2828427124746191*(1.732050807568877*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2*wvpar+(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1]))*q_))/q_; 
  BstarZdBmag[2] = (1.414213562373095*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2)/(q_*rdvpar2); 
  BstarZdBmag[4] = (1.414213562373095*(b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2)/(q_*rdvpar2); 
  BstarZdBmag[7] = (0.04040610178208843*(60.6217782649107*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2*wvpar+((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1]))*q_))/q_; 
  BstarZdBmag[11] = (1.414213562373095*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2)/(q_*rdvpar2); 

  double cflFreq = 0.0; 
  double alphaL = 0.0; 
  double alphaR = 0.0; 
  double alphax[27]; 
  alphax[0] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[2]*hamil[8]+BstarZdBmag[0]*hamil[2])*rdvpar2*rdx2)/m_; 
  alphax[1] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[4]*hamil[8]+BstarZdBmag[1]*hamil[2])*rdvpar2*rdx2)/m_; 
  alphax[2] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[0]*hamil[8]+BstarZdBmag[2]*hamil[2])*rdvpar2*rdx2)/m_; 
  alphax[4] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[1]*hamil[8]+hamil[2]*BstarZdBmag[4])*rdvpar2*rdx2)/m_; 
  alphax[7] = (0.3535533905932737*(3.872983346207417*hamil[8]*BstarZdBmag[11]+1.732050807568877*hamil[2]*BstarZdBmag[7])*rdvpar2*rdx2)/m_; 
  alphax[8] = (1.224744871391589*BstarZdBmag[2]*hamil[8]*rdvpar2*rdx2)/m_; 
  alphax[11] = (0.3535533905932737*(1.732050807568877*hamil[2]*BstarZdBmag[11]+3.872983346207417*BstarZdBmag[7]*hamil[8])*rdvpar2*rdx2)/m_; 
  alphax[12] = (1.224744871391589*BstarZdBmag[4]*hamil[8]*rdvpar2*rdx2)/m_; 
  alphax[20] = (1.224744871391589*hamil[8]*BstarZdBmag[11]*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = 0.125*(3.16227766016838*alphax[7]-2.449489742783178*alphax[1]+1.414213562373095*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.125*(3.16227766016838*alphax[7]+2.449489742783178*alphax[1]+1.414213562373095*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.883883476483184*alphax[20])+0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.883883476483184*alphax[20])+0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.883883476483184*alphax[20])+0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.883883476483184*alphax[20])-0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.883883476483184*alphax[20])-0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.883883476483184*alphax[20])-0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  double alphavpar[27]; 
  alphavpar[0] = -(0.6123724356957944*(2.23606797749979*BstarZdBmag[1]*hamil[7]+BstarZdBmag[0]*hamil[1])*rdvpar2*rdx2)/m_; 
  alphavpar[1] = -(0.6123724356957944*((2.0*BstarZdBmag[7]+2.23606797749979*BstarZdBmag[0])*hamil[7]+BstarZdBmag[1]*hamil[1])*rdvpar2*rdx2)/m_; 
  alphavpar[2] = -(0.6123724356957944*(2.23606797749979*BstarZdBmag[4]*hamil[7]+hamil[1]*BstarZdBmag[2])*rdvpar2*rdx2)/m_; 
  alphavpar[3] = -(0.3535533905932737*(3.872983346207417*BstarZdBmag[1]*hamil[13]+1.732050807568877*BstarZdBmag[0]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[4] = -(0.3535533905932737*(3.464101615137755*hamil[7]*BstarZdBmag[11]+1.732050807568877*(2.23606797749979*BstarZdBmag[2]*hamil[7]+hamil[1]*BstarZdBmag[4]))*rdvpar2*rdx2)/m_; 
  alphavpar[5] = -(0.3535533905932737*(3.872983346207417*(0.8944271909999159*BstarZdBmag[7]+BstarZdBmag[0])*hamil[13]+1.732050807568877*BstarZdBmag[1]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[6] = -(0.3535533905932737*(3.872983346207417*BstarZdBmag[4]*hamil[13]+1.732050807568877*BstarZdBmag[2]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[7] = -(0.6123724356957944*(2.0*BstarZdBmag[1]*hamil[7]+hamil[1]*BstarZdBmag[7])*rdvpar2*rdx2)/m_; 
  alphavpar[10] = -(0.3535533905932737*((3.464101615137754*BstarZdBmag[11]+3.872983346207417*BstarZdBmag[2])*hamil[13]+1.732050807568877*BstarZdBmag[4]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[11] = -(0.3535533905932737*(1.732050807568877*hamil[1]*BstarZdBmag[11]+3.464101615137755*BstarZdBmag[4]*hamil[7])*rdvpar2*rdx2)/m_; 
  alphavpar[13] = -(0.3535533905932737*(3.464101615137754*BstarZdBmag[1]*hamil[13]+1.732050807568877*hamil[5]*BstarZdBmag[7])*rdvpar2*rdx2)/m_; 
  alphavpar[17] = -(0.6123724356957944*(2.0*BstarZdBmag[4]*hamil[13]+hamil[5]*BstarZdBmag[11])*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = -0.125*(2.449489742783178*alphavpar[2]-1.414213562373095*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.125*(2.449489742783178*alphavpar[2]+1.414213562373095*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.7348469228349533*alphavpar[17]-0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.9185586535436913*alphavpar[17])+0.5303300858899104*alphavpar[13]+0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]+0.8215838362577489*alphavpar[6]-0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7348469228349533*alphavpar[17]-0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.5477225575051661*alphavpar[11])+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[4]-0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]-0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.5477225575051661*alphavpar[11])+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[4]-0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.7348469228349533*alphavpar[17])+0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.9185586535436913*alphavpar[17]-0.5303300858899104*alphavpar[13]+0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]-0.8215838362577489*alphavpar[6]+0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.7348469228349533*alphavpar[17])+0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*((-0.7348469228349533*alphavpar[17])-0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.9185586535436913*alphavpar[17]+0.5303300858899104*alphavpar[13]-0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]-0.8215838362577489*alphavpar[6]-0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.7348469228349533*alphavpar[17])-0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.5477225575051661*alphavpar[11]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[4]+0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.6846531968814574*alphavpar[11])-0.3952847075210473*alphavpar[7]+0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.5477225575051661*alphavpar[11]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[4]+0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7348469228349533*alphavpar[17]+0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.9185586535436913*alphavpar[17])-0.5303300858899104*alphavpar[13]-0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]+0.8215838362577489*alphavpar[6]+0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7348469228349533*alphavpar[17]+0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  out[1] += 0.6123724356957944*(alphax[20]*f[20]+alphax[12]*f[12]+alphax[11]*f[11]+alphax[8]*f[8]+alphax[7]*f[7]+alphax[4]*f[4]+alphax[2]*f[2]+alphax[1]*f[1]+alphax[0]*f[0]); 
  out[2] += 0.6123724356957944*(alphavpar[17]*f[17]+alphavpar[13]*f[13]+alphavpar[11]*f[11]+alphavpar[10]*f[10]+alphavpar[7]*f[7]+alphavpar[6]*f[6]+alphavpar[5]*f[5]+alphavpar[4]*f[4]+alphavpar[3]*f[3]+alphavpar[2]*f[2]+alphavpar[1]*f[1]+alphavpar[0]*f[0]); 
  out[4] += 0.07071067811865474*(7.745966692414834*(alphax[11]*f[20]+f[11]*alphax[20]+alphavpar[10]*f[17]+f[10]*alphavpar[17]+alphavpar[5]*f[13]+f[5]*alphavpar[13]+alphax[4]*f[12]+f[4]*alphax[12])+(8.660254037844387*alphax[7]+7.745966692414834*alphavpar[4])*f[11]+8.660254037844387*f[7]*alphax[11]+7.745966692414834*f[4]*alphavpar[11]+8.660254037844386*(alphavpar[6]*f[10]+f[6]*alphavpar[10])+7.745966692414834*(alphax[2]*f[8]+f[2]*alphax[8]+alphavpar[1]*f[7]+f[1]*alphavpar[7])+8.660254037844386*(alphavpar[3]*f[5]+f[3]*alphavpar[5]+(alphavpar[2]+alphax[1])*f[4]+f[1]*alphax[4]+f[2]*(alphavpar[4]+alphax[0])+f[0]*alphax[2]+alphavpar[0]*f[1]+f[0]*alphavpar[1])); 
  out[5] += 0.07071067811865474*(8.660254037844386*alphax[20]*f[23]+8.660254037844387*(alphax[12]*f[18]+alphax[11]*f[17]+alphax[8]*f[14]+alphax[7]*f[13])+8.660254037844386*(alphax[4]*f[10]+alphax[2]*f[6]+alphax[1]*f[5]+alphax[0]*f[3])); 
  out[6] += 0.07071067811865474*(7.745966692414834*(alphavpar[17]*f[24]+alphavpar[13]*f[21]+alphavpar[10]*f[19])+8.660254037844387*(alphavpar[11]*f[17]+f[11]*alphavpar[17])+7.745966692414834*(alphavpar[6]*f[16]+alphavpar[5]*f[15])+8.660254037844387*(alphavpar[7]*f[13]+f[7]*alphavpar[13])+8.660254037844386*(alphavpar[4]*f[10]+f[4]*alphavpar[10])+7.745966692414834*alphavpar[3]*f[9]+8.660254037844386*(alphavpar[2]*f[6]+f[2]*alphavpar[6]+alphavpar[1]*f[5]+f[1]*alphavpar[5]+alphavpar[0]*f[3]+f[0]*alphavpar[3])); 
  out[7] += 0.07071067811865474*(17.32050807568877*(alphax[12]*f[20]+f[12]*alphax[20])+19.36491673103708*(alphax[8]*f[12]+f[8]*alphax[12])+17.32050807568877*(alphax[4]*f[11]+f[4]*alphax[11])+17.32050807568877*(alphax[1]*f[7]+f[1]*alphax[7])+19.36491673103709*(alphax[2]*f[4]+f[2]*alphax[4]+alphax[0]*f[1]+f[0]*alphax[1])); 
  out[8] += 0.07071067811865474*(17.32050807568877*alphavpar[17]*f[23]+17.32050807568877*alphavpar[11]*f[20]+17.32050807568877*alphavpar[10]*f[18]+19.36491673103708*(alphavpar[13]*f[17]+f[13]*alphavpar[17])+17.32050807568877*(alphavpar[6]*f[14]+alphavpar[4]*f[12])+19.36491673103708*(alphavpar[7]*f[11]+f[7]*alphavpar[11])+19.36491673103709*(alphavpar[5]*f[10]+f[5]*alphavpar[10])+17.32050807568877*alphavpar[2]*f[8]+19.36491673103709*(alphavpar[3]*f[6]+f[3]*alphavpar[6]+alphavpar[1]*f[4]+f[1]*alphavpar[4]+alphavpar[0]*f[2]+f[0]*alphavpar[2])); 
  out[10] += 0.07071067811865474*(6.928203230275509*alphavpar[10]*f[24]+7.745966692414834*alphax[11]*f[23]+6.928203230275509*alphavpar[5]*f[21]+7.745966692414834*f[17]*alphax[20]+6.928203230275509*alphavpar[17]*f[19]+7.745966692414834*(alphavpar[6]*f[19]+alphax[4]*f[18])+8.660254037844386*alphax[7]*f[17]+7.745966692414834*(alphavpar[4]*f[17]+f[4]*alphavpar[17]+alphavpar[10]*f[16])+6.928203230275509*alphavpar[13]*f[15]+7.745966692414834*(alphavpar[3]*f[15]+alphax[2]*f[14])+8.660254037844386*alphax[11]*f[13]+7.745966692414834*(alphavpar[1]*f[13]+f[1]*alphavpar[13]+f[10]*alphax[12]+alphavpar[10]*f[11]+f[10]*alphavpar[11])+8.660254037844386*((alphavpar[2]+alphax[1])*f[10]+f[2]*alphavpar[10])+7.745966692414834*(alphavpar[5]*f[9]+f[6]*alphax[8]+alphavpar[5]*f[7]+f[5]*alphavpar[7])+8.660254037844386*((alphavpar[4]+alphax[0])*f[6]+f[4]*alphavpar[6]+(alphax[4]+alphavpar[0])*f[5]+f[0]*alphavpar[5]+(alphax[2]+alphavpar[1])*f[3]+f[1]*alphavpar[3])); 
  out[11] += 0.01010152544552211*(108.4435336938077*(alphax[4]*f[20]+f[4]*alphax[20])+38.72983346207417*alphavpar[17]*f[17]+60.62177826491071*(alphavpar[6]*f[17]+f[6]*alphavpar[17])+38.72983346207417*alphavpar[13]*f[13]+60.6217782649107*(alphavpar[3]*f[13]+f[3]*alphavpar[13])+(108.4435336938077*alphax[11]+121.2435565298214*alphax[2])*f[12]+(108.4435336938077*f[11]+121.2435565298214*f[2])*alphax[12]+(38.72983346207417*alphavpar[11]+60.6217782649107*alphavpar[2])*f[11]+121.2435565298214*(alphax[1]*f[11]+f[1]*alphax[11])+60.6217782649107*f[2]*alphavpar[11]+54.22176684690384*alphavpar[10]*f[10]+121.2435565298214*(alphax[4]*f[8]+f[4]*alphax[8])+(38.72983346207417*alphavpar[7]+121.2435565298214*alphax[4]+60.62177826491071*alphavpar[0])*f[7]+121.2435565298214*f[4]*alphax[7]+60.62177826491071*f[0]*alphavpar[7]+54.22176684690384*(alphavpar[5]*f[5]+alphavpar[4]*f[4])+135.5544171172596*(alphax[0]*f[4]+f[0]*alphax[4]+alphax[1]*f[2])+f[1]*(135.5544171172596*alphax[2]+54.22176684690384*alphavpar[1])); 
  out[12] += 0.01010152544552211*(108.4435336938077*alphavpar[10]*f[23]+(38.72983346207417*alphax[20]+60.62177826491071*alphax[7]+108.4435336938077*alphavpar[4])*f[20]+60.62177826491071*f[7]*alphax[20]+108.4435336938077*alphavpar[17]*f[18]+121.2435565298214*(alphavpar[6]*f[18]+alphavpar[5]*f[17]+f[5]*alphavpar[17])+121.2435565298214*(alphavpar[10]*(f[14]+f[13])+f[10]*alphavpar[13])+(38.72983346207417*alphax[12]+108.4435336938077*alphavpar[11]+121.2435565298214*alphavpar[2])*f[12]+60.6217782649107*(alphax[1]*f[12]+f[1]*alphax[12])+54.22176684690384*alphax[11]*f[11]+121.2435565298214*(alphavpar[1]*f[11]+f[1]*alphavpar[11])+135.5544171172596*(alphavpar[3]*f[10]+f[3]*alphavpar[10])+(38.72983346207417*alphax[8]+121.2435565298214*alphavpar[4])*f[8]+60.62177826491071*(alphax[0]*f[8]+f[0]*alphax[8])+121.2435565298214*(alphavpar[4]*f[7]+f[4]*alphavpar[7])+135.5544171172596*(alphavpar[5]*f[6]+f[5]*alphavpar[6])+54.22176684690384*alphax[4]*f[4]+135.5544171172596*(alphavpar[0]*f[4]+f[0]*alphavpar[4])+54.22176684690384*alphax[2]*f[2]+135.5544171172596*(alphavpar[1]*f[2]+f[1]*alphavpar[2])); 
  out[13] += 0.07071067811865474*(17.32050807568877*alphax[12]*f[23]+f[18]*(17.32050807568877*alphax[20]+19.36491673103708*alphax[8])+17.32050807568877*alphax[4]*f[17]+19.36491673103708*alphax[12]*f[14]+17.32050807568877*alphax[1]*f[13]+f[10]*(17.32050807568877*alphax[11]+19.36491673103708*alphax[2])+17.32050807568877*f[5]*alphax[7]+19.36491673103708*(alphax[4]*f[6]+alphax[0]*f[5]+alphax[1]*f[3])); 
  out[14] += 0.07071067811865474*(15.49193338482967*(alphavpar[17]*f[26]+alphavpar[10]*f[25])+17.32050807568877*(alphavpar[13]*f[24]+alphavpar[11]*f[23])+15.49193338482967*alphavpar[6]*f[22]+17.32050807568877*(alphavpar[17]*(f[21]+f[20])+alphavpar[5]*f[19]+alphavpar[4]*f[18])+19.36491673103708*(alphavpar[7]*f[17]+f[7]*alphavpar[17])+17.32050807568877*(alphavpar[3]*f[16]+alphavpar[10]*f[15]+alphavpar[2]*f[14])+19.36491673103708*(alphavpar[11]*f[13]+f[11]*alphavpar[13])+17.32050807568877*alphavpar[10]*f[12]+19.36491673103708*(alphavpar[1]*f[10]+f[1]*alphavpar[10])+17.32050807568877*alphavpar[6]*(f[9]+f[8])+19.36491673103708*(alphavpar[0]*f[6]+f[0]*alphavpar[6]+alphavpar[4]*f[5]+f[4]*alphavpar[5]+alphavpar[2]*f[3]+f[2]*alphavpar[3])); 
  out[15] += 0.07071067811865474*(8.660254037844387*alphax[20]*f[26]+8.660254037844386*(alphax[12]*f[25]+alphax[11]*f[24])+8.660254037844387*(alphax[8]*f[22]+alphax[7]*f[21]+alphax[4]*f[19])+8.660254037844386*(alphax[2]*f[16]+alphax[1]*f[15])+8.660254037844387*alphax[0]*f[9]); 
  out[16] += 0.07071067811865474*(8.660254037844386*alphavpar[11]*f[24]+8.660254037844387*(alphavpar[7]*f[21]+alphavpar[4]*f[19])+7.745966692414834*alphavpar[17]*f[17]+8.660254037844386*(alphavpar[2]*f[16]+alphavpar[1]*f[15])+7.745966692414834*(alphavpar[13]*f[13]+alphavpar[10]*f[10])+8.660254037844387*alphavpar[0]*f[9]+7.745966692414834*(alphavpar[6]*f[6]+alphavpar[5]*f[5]+alphavpar[3]*f[3])); 
  out[17] += 0.002020305089104421*((173.2050807568877*alphavpar[17]+271.1088342345192*alphavpar[6])*f[24]+542.2176684690385*alphax[4]*f[23]+(173.2050807568878*alphavpar[13]+271.1088342345192*alphavpar[3])*f[21]+542.2176684690385*f[10]*alphax[20]+242.4871130596428*alphavpar[10]*f[19]+(542.2176684690384*alphax[11]+606.217782649107*alphax[2])*f[18]+(542.2176684690384*alphax[12]+193.6491673103708*alphavpar[11]+303.1088913245535*alphavpar[2]+606.217782649107*alphax[1])*f[17]+(271.1088342345192*f[16]+193.6491673103708*f[11]+303.1088913245535*f[2])*alphavpar[17]+242.4871130596428*alphavpar[5]*f[15]+606.2177826491072*alphax[4]*f[14]+(193.6491673103708*alphavpar[7]+606.2177826491072*alphax[4]+303.1088913245536*alphavpar[0])*f[13]+(271.1088342345192*f[9]+193.6491673103708*f[7]+303.1088913245536*f[0])*alphavpar[13]+606.2177826491072*f[6]*alphax[12]+303.1088913245536*alphavpar[6]*f[11]+606.2177826491072*f[5]*alphax[11]+303.1088913245536*f[6]*alphavpar[11]+(606.217782649107*(alphax[8]+alphax[7])+271.1088342345192*alphavpar[4]+677.7720855862981*alphax[0])*f[10]+271.1088342345192*f[4]*alphavpar[10]+303.1088913245535*(alphavpar[3]*f[7]+f[3]*alphavpar[7])+677.7720855862981*(alphax[1]*f[6]+alphax[2]*f[5])+271.1088342345192*(alphavpar[1]*f[5]+f[1]*alphavpar[5])+677.7720855862981*f[3]*alphax[4]); 
  out[18] += 0.01010152544552211*(96.99484522385713*(alphavpar[10]*f[26]+alphavpar[17]*f[25])+108.4435336938077*(alphavpar[6]*f[25]+alphavpar[5]*f[24])+(38.72983346207418*alphax[20]+60.6217782649107*alphax[7])*f[23]+108.4435336938077*(alphavpar[4]*f[23]+alphavpar[10]*(f[22]+f[21]+f[20]))+60.62177826491071*f[13]*alphax[20]+(108.4435336938077*alphavpar[13]+121.2435565298214*alphavpar[3])*f[19]+(38.72983346207417*alphax[12]+108.4435336938077*alphavpar[11]+121.2435565298214*alphavpar[2]+60.6217782649107*alphax[1])*f[18]+(54.22176684690384*alphax[11]+121.2435565298214*alphavpar[1])*f[17]+(108.4435336938077*(f[15]+f[12])+121.2435565298214*f[1])*alphavpar[17]+121.2435565298214*(alphavpar[5]*f[16]+alphavpar[6]*f[15])+(38.72983346207417*alphax[8]+121.2435565298214*alphavpar[4]+60.62177826491071*alphax[0])*f[14]+121.2435565298214*(alphavpar[4]*f[13]+f[4]*alphavpar[13]+alphavpar[6]*f[12])+60.62177826491071*f[5]*alphax[12]+121.2435565298214*(alphavpar[5]*f[11]+f[5]*alphavpar[11])+(121.2435565298214*alphavpar[7]+54.22176684690384*alphax[4]+135.5544171172596*alphavpar[0])*f[10]+(121.2435565298214*(f[9]+f[8]+f[7])+135.5544171172596*f[0])*alphavpar[10]+60.6217782649107*f[3]*alphax[8]+54.22176684690384*alphax[2]*f[6]+135.5544171172596*(alphavpar[1]*f[6]+f[1]*alphavpar[6]+alphavpar[2]*f[5]+f[2]*alphavpar[5]+alphavpar[3]*f[4]+f[3]*alphavpar[4])); 
  out[19] += 0.01414213562373095*(38.72983346207417*alphax[11]*f[26]+38.72983346207418*alphax[4]*f[25]+(38.72983346207418*alphax[20]+43.30127018922193*alphax[7])*f[24]+38.72983346207418*(alphavpar[4]*f[24]+alphax[2]*f[22])+(43.30127018922195*alphax[11]+38.72983346207418*alphavpar[1])*f[21]+(38.72983346207417*(alphax[12]+alphavpar[11])+43.30127018922193*(alphavpar[2]+alphax[1]))*f[19]+34.64101615137754*(alphavpar[10]*f[17]+f[10]*alphavpar[17])+(38.72983346207417*alphax[8]+43.30127018922195*(alphavpar[4]+alphax[0]))*f[16]+(38.72983346207417*alphavpar[7]+43.30127018922195*(alphax[4]+alphavpar[0]))*f[15]+34.64101615137755*(alphavpar[5]*f[13]+f[5]*alphavpar[13])+38.72983346207418*(alphavpar[6]*f[10]+f[6]*alphavpar[10])+43.30127018922193*(alphax[2]+alphavpar[1])*f[9]+38.72983346207418*(alphavpar[3]*f[5]+f[3]*alphavpar[5])); 
  out[20] += 0.01010152544552211*((77.45966692414835*alphavpar[17]+121.2435565298214*alphavpar[6])*f[23]+(77.45966692414834*(alphax[12]+alphavpar[11])+121.2435565298214*(alphavpar[2]+alphax[1]))*f[20]+(77.45966692414834*f[12]+121.2435565298214*f[1])*alphax[20]+108.4435336938077*alphavpar[10]*f[18]+(86.60254037844389*alphavpar[13]+135.5544171172596*alphavpar[3])*f[17]+(121.2435565298214*f[14]+86.60254037844389*f[13]+135.5544171172596*f[3])*alphavpar[17]+135.5544171172596*(alphavpar[6]*f[13]+f[6]*alphavpar[13])+(86.60254037844389*alphax[8]+121.2435565298214*alphax[7]+108.4435336938077*alphavpar[4]+135.5544171172596*alphax[0])*f[12]+(86.60254037844389*f[8]+121.2435565298214*f[7]+135.5544171172596*f[0])*alphax[12]+(86.60254037844389*alphavpar[7]+108.4435336938077*alphax[4]+135.5544171172596*alphavpar[0])*f[11]+108.4435336938077*f[4]*alphax[11]+(121.2435565298214*f[8]+86.60254037844389*f[7]+135.5544171172596*f[0])*alphavpar[11]+121.2435565298214*(alphavpar[5]*f[10]+f[5]*alphavpar[10])+135.5544171172596*(alphax[1]*f[8]+f[1]*alphax[8]+alphavpar[2]*f[7]+f[2]*alphavpar[7])+121.2435565298214*((alphax[2]+alphavpar[1])*f[4]+f[2]*alphax[4]+f[1]*alphavpar[4])); 
  out[21] += 0.07071067811865474*(17.32050807568877*alphax[12]*f[26]+(17.32050807568877*alphax[20]+19.36491673103709*alphax[8])*f[25]+17.32050807568877*alphax[4]*f[24]+19.36491673103708*alphax[12]*f[22]+17.32050807568877*alphax[1]*f[21]+(17.32050807568877*alphax[11]+19.36491673103709*alphax[2])*f[19]+19.36491673103708*alphax[4]*f[16]+(17.32050807568877*alphax[7]+19.36491673103708*alphax[0])*f[15]+19.36491673103709*alphax[1]*f[9]); 
  out[22] += 0.07071067811865474*(17.32050807568877*alphavpar[11]*f[26]+17.32050807568877*alphavpar[4]*f[25]+19.36491673103709*alphavpar[7]*f[24]+15.49193338482967*alphavpar[17]*f[23]+17.32050807568877*alphavpar[2]*f[22]+19.36491673103708*alphavpar[11]*f[21]+19.36491673103709*alphavpar[1]*f[19]+15.49193338482967*alphavpar[10]*f[18]+17.32050807568877*(alphavpar[13]*f[17]+f[13]*alphavpar[17])+19.36491673103708*(alphavpar[0]*f[16]+alphavpar[4]*f[15])+15.49193338482967*alphavpar[6]*f[14]+17.32050807568877*(alphavpar[5]*f[10]+f[5]*alphavpar[10])+19.36491673103709*alphavpar[2]*f[9]+17.32050807568877*(alphavpar[3]*f[6]+f[3]*alphavpar[6])); 
  out[23] += 0.01010152544552211*((69.28203230275508*alphavpar[17]+108.4435336938077*alphavpar[6])*f[26]+96.99484522385713*alphavpar[10]*f[25]+(77.45966692414834*alphavpar[13]+121.2435565298214*alphavpar[3])*f[24]+(77.45966692414834*(alphax[12]+alphavpar[11])+121.2435565298214*(alphavpar[2]+alphax[1]))*f[23]+108.4435336938077*alphavpar[17]*f[22]+(77.45966692414835*alphavpar[17]+121.2435565298214*alphavpar[6])*f[21]+(77.45966692414835*alphavpar[17]+121.2435565298214*alphavpar[6])*f[20]+(77.45966692414835*f[18]+121.2435565298214*f[5])*alphax[20]+108.4435336938077*alphavpar[5]*f[19]+(86.60254037844386*alphax[8]+121.2435565298214*alphax[7]+108.4435336938077*alphavpar[4]+135.5544171172596*alphax[0])*f[18]+(86.60254037844386*alphavpar[7]+108.4435336938077*alphax[4]+135.5544171172596*alphavpar[0])*f[17]+(121.2435565298214*(f[9]+f[8])+86.60254037844386*f[7]+135.5544171172596*f[0])*alphavpar[17]+121.2435565298214*alphavpar[13]*f[16]+108.4435336938077*alphavpar[10]*f[15]+(86.60254037844386*alphax[12]+121.2435565298214*alphavpar[11]+135.5544171172596*alphax[1])*f[14]+(121.2435565298214*alphax[12]+86.60254037844386*alphavpar[11]+135.5544171172596*alphavpar[2])*f[13]+(86.60254037844386*f[11]+135.5544171172596*f[2])*alphavpar[13]+108.4435336938077*alphavpar[10]*f[12]+135.5544171172596*(f[3]*alphax[12]+alphavpar[3]*f[11])+108.4435336938077*f[10]*alphax[11]+135.5544171172596*f[3]*alphavpar[11]+121.2435565298214*((alphax[2]+alphavpar[1])*f[10]+f[1]*alphavpar[10])+135.5544171172596*(f[5]*alphax[8]+alphavpar[6]*f[7]+f[6]*alphavpar[7])+121.2435565298214*(alphax[4]*f[6]+alphavpar[4]*f[5]+f[4]*alphavpar[5])); 
  out[24] += 0.01010152544552211*(108.4435336938077*alphax[4]*f[26]+(108.4435336938077*alphax[11]+121.2435565298214*alphax[2])*f[25]+(108.4435336938077*alphax[12]+38.72983346207417*alphavpar[11]+60.6217782649107*alphavpar[2])*f[24]+121.2435565298214*(alphax[1]*f[24]+alphax[4]*f[22])+(38.72983346207418*alphavpar[7]+121.2435565298214*alphax[4]+60.6217782649107*alphavpar[0])*f[21]+f[19]*(108.4435336938077*alphax[20]+121.2435565298214*(alphax[8]+alphax[7])+54.22176684690384*alphavpar[4]+135.5544171172596*alphax[0])+34.64101615137754*alphavpar[17]*f[17]+54.22176684690384*(alphavpar[6]*f[17]+f[6]*alphavpar[17])+(121.2435565298214*alphax[12]+60.6217782649107*alphavpar[11]+135.5544171172596*alphax[1])*f[16]+(121.2435565298214*alphax[11]+135.5544171172596*alphax[2]+54.22176684690384*alphavpar[1])*f[15]+34.64101615137754*alphavpar[13]*f[13]+54.22176684690384*(alphavpar[3]*f[13]+f[3]*alphavpar[13])+48.49742261192856*alphavpar[10]*f[10]+(60.6217782649107*alphavpar[7]+135.5544171172596*alphax[4])*f[9]+48.49742261192856*alphavpar[5]*f[5]); 
  out[25] += 0.01010152544552211*((38.72983346207418*alphax[20]+60.6217782649107*alphax[7]+108.4435336938077*alphavpar[4])*f[26]+(38.72983346207417*alphax[12]+108.4435336938077*alphavpar[11]+121.2435565298214*alphavpar[2]+60.6217782649107*alphax[1])*f[25]+(54.22176684690384*alphax[11]+121.2435565298214*alphavpar[1])*f[24]+96.99484522385713*alphavpar[10]*f[23]+(38.72983346207418*alphax[8]+121.2435565298214*alphavpar[4]+60.6217782649107*alphax[0])*f[22]+(60.6217782649107*alphax[20]+121.2435565298214*alphavpar[4])*f[21]+(121.2435565298214*alphavpar[7]+54.22176684690384*alphax[4]+135.5544171172596*alphavpar[0])*f[19]+96.99484522385713*alphavpar[17]*f[18]+108.4435336938077*(alphavpar[6]*f[18]+alphavpar[5]*f[17]+f[5]*alphavpar[17])+(54.22176684690384*alphax[2]+135.5544171172596*alphavpar[1])*f[16]+(60.6217782649107*alphax[12]+121.2435565298214*alphavpar[11]+135.5544171172596*alphavpar[2])*f[15]+108.4435336938077*(alphavpar[10]*(f[14]+f[13])+f[10]*alphavpar[13])+121.2435565298214*(alphavpar[3]*f[10]+f[3]*alphavpar[10])+(60.6217782649107*alphax[8]+135.5544171172596*alphavpar[4])*f[9]+121.2435565298214*(alphavpar[5]*f[6]+f[5]*alphavpar[6])); 
  out[26] += 0.01010152544552211*((77.45966692414834*(alphax[12]+alphavpar[11])+121.2435565298214*(alphavpar[2]+alphax[1]))*f[26]+(77.45966692414835*alphax[20]+86.60254037844386*alphax[8]+121.2435565298214*alphax[7]+108.4435336938077*alphavpar[4]+135.5544171172596*alphax[0])*f[25]+(86.60254037844386*alphavpar[7]+108.4435336938077*alphax[4]+135.5544171172596*alphavpar[0])*f[24]+(69.28203230275508*alphavpar[17]+108.4435336938077*alphavpar[6])*f[23]+(86.60254037844389*alphax[12]+121.2435565298214*alphavpar[11]+135.5544171172596*alphax[1])*f[22]+(121.2435565298214*alphax[12]+86.60254037844389*alphavpar[11]+135.5544171172596*alphavpar[2])*f[21]+121.2435565298214*f[15]*alphax[20]+(108.4435336938077*alphax[11]+121.2435565298214*(alphax[2]+alphavpar[1]))*f[19]+96.99484522385713*alphavpar[10]*f[18]+(77.45966692414834*alphavpar[13]+121.2435565298214*alphavpar[3])*f[17]+(108.4435336938077*f[14]+77.45966692414834*f[13]+121.2435565298214*f[3])*alphavpar[17]+(135.5544171172596*alphavpar[7]+121.2435565298214*alphax[4])*f[16]+135.5544171172596*alphax[8]*f[15]+121.2435565298214*(alphavpar[4]*f[15]+alphavpar[6]*f[13]+f[6]*alphavpar[13])+135.5544171172596*f[9]*(alphax[12]+alphavpar[11])+108.4435336938077*(alphavpar[5]*f[10]+f[5]*alphavpar[10])); 
  return cflFreq; 
} 
double GyrokineticGenGeoVol1x2vTensorP2_Bvarsz(const double q_, const double m_, const double *w, const double *dxv, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *f, double *out) 
{ 
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
  // q_,m_: species charge and mass.
  // w[NDIM]: cell-center.
  // dxv[NDIM]: cell length.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // f: Distribution function.
  // out: output increment.

  double wx = w[0];
  double rdx2 = 2.0/dxv[0];
  double wvpar = w[1];
  double rdvpar2 = 2.0/dxv[1];
  double wmu = w[2];
  double rdmu2 = 2.0/dxv[2];

  double wxSq = w[0]*w[0];
  double rdx2Sq = rdx2*rdx2;
  double wvparSq = w[1]*w[1];
  double rdvpar2Sq = rdvpar2*rdvpar2;
  double wmuSq = w[2]*w[2];
  double rdmu2Sq = rdmu2*rdmu2;

  double hamil[27]; 
  hamil[0] = (0.2357022603955158*(3.0*rdvpar2Sq*(2.0*m_*wvparSq+2.828427124746191*(bmag[0]*wmu+phi[0]*q_))+2.0*m_))/rdvpar2Sq; 
  hamil[1] = 2.0*phi[1]*q_; 
  hamil[2] = (1.632993161855453*m_*wvpar)/rdvpar2; 
  hamil[3] = (1.154700538379252*bmag[0])/rdmu2; 
  hamil[7] = 2.0*phi[2]*q_; 
  hamil[8] = (0.421637021355784*m_)/rdvpar2Sq; 

  double BstarZdBmag[27]; 
  BstarZdBmag[0] = 1.414213562373095*cmag[0]*jacobTotInv[0]; 

  double cflFreq = 0.0; 
  double alphaL = 0.0; 
  double alphaR = 0.0; 
  double alphax[27]; 
  alphax[0] = (0.6123724356957944*BstarZdBmag[0]*hamil[2]*rdvpar2*rdx2)/m_; 
  alphax[2] = (1.369306393762915*BstarZdBmag[0]*hamil[8]*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = 0.1767766952966368*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.1767766952966368*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphax[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphax[0]-0.4743416490252568*alphax[2]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphax[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphax[2]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  double alphavpar[27]; 
  alphavpar[0] = -(0.6123724356957944*BstarZdBmag[0]*hamil[1]*rdvpar2*rdx2)/m_; 
  alphavpar[1] = -(1.369306393762915*BstarZdBmag[0]*hamil[7]*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = 0.1767766952966368*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.1767766952966368*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.0441941738241592*alphavpar[0]; 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.3535533905932737*alphavpar[0]-0.4743416490252568*alphavpar[1]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.0441941738241592*alphavpar[0]; 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  out[1] += 0.6123724356957944*(alphax[2]*f[2]+alphax[0]*f[0]); 
  out[2] += 0.6123724356957944*(alphavpar[1]*f[1]+alphavpar[0]*f[0]); 
  out[4] += 0.1224744871391589*(4.47213595499958*(alphax[2]*f[8]+alphavpar[1]*f[7])+5.0*(alphax[0]*f[2]+f[0]*alphax[2]+alphavpar[0]*f[1]+f[0]*alphavpar[1])); 
  out[5] += 0.6123724356957944*(alphax[2]*f[6]+alphax[0]*f[3]); 
  out[6] += 0.6123724356957944*(alphavpar[1]*f[5]+alphavpar[0]*f[3]); 
  out[7] += 1.369306393762915*(alphax[2]*f[4]+alphax[0]*f[1]); 
  out[8] += 1.369306393762915*(alphavpar[1]*f[4]+alphavpar[0]*f[2]); 
  out[10] += 0.07071067811865474*(7.745966692414834*(alphax[2]*f[14]+alphavpar[1]*f[13])+8.660254037844386*(alphax[0]*f[6]+alphavpar[0]*f[5]+(alphax[2]+alphavpar[1])*f[3])); 
  out[11] += 0.07071067811865474*(17.32050807568877*alphax[2]*f[12]+8.660254037844387*alphavpar[0]*f[7]+19.36491673103708*alphax[0]*f[4]+f[1]*(19.36491673103708*alphax[2]+7.745966692414834*alphavpar[1])); 
  out[12] += 0.07071067811865474*(17.32050807568877*alphavpar[1]*f[11]+8.660254037844387*alphax[0]*f[8]+19.36491673103708*alphavpar[0]*f[4]+(7.745966692414834*alphax[2]+19.36491673103708*alphavpar[1])*f[2]); 
  out[13] += 1.369306393762915*(alphax[2]*f[10]+alphax[0]*f[5]); 
  out[14] += 1.369306393762915*(alphavpar[1]*f[10]+alphavpar[0]*f[6]); 
  out[15] += 0.07071067811865474*(8.660254037844386*alphax[2]*f[16]+8.660254037844387*alphax[0]*f[9]); 
  out[16] += 0.07071067811865474*(8.660254037844386*alphavpar[1]*f[15]+8.660254037844387*alphavpar[0]*f[9]); 
  out[17] += 0.07071067811865474*(17.32050807568877*alphax[2]*f[18]+8.660254037844387*alphavpar[0]*f[13]+19.36491673103709*alphax[0]*f[10]+(19.36491673103709*alphax[2]+7.745966692414834*alphavpar[1])*f[5]); 
  out[18] += 0.07071067811865474*(17.32050807568877*alphavpar[1]*f[17]+8.660254037844387*alphax[0]*f[14]+19.36491673103709*alphavpar[0]*f[10]+(7.745966692414834*alphax[2]+19.36491673103709*alphavpar[1])*f[6]); 
  out[19] += 0.07071067811865474*(7.745966692414834*(alphax[2]*f[22]+alphavpar[1]*f[21])+8.660254037844387*(alphax[0]*f[16]+alphavpar[0]*f[15])+8.660254037844386*(alphax[2]+alphavpar[1])*f[9]); 
  out[20] += 0.3535533905932737*(3.872983346207417*(alphax[0]*f[12]+alphavpar[0]*f[11])+3.464101615137754*(alphax[2]+alphavpar[1])*f[4]); 
  out[21] += 1.369306393762915*(alphax[2]*f[19]+alphax[0]*f[15]); 
  out[22] += 1.369306393762915*(alphavpar[1]*f[19]+alphavpar[0]*f[16]); 
  out[23] += 0.6123724356957944*(2.23606797749979*(alphax[0]*f[18]+alphavpar[0]*f[17])+2.0*(alphax[2]+alphavpar[1])*f[10]); 
  out[24] += 0.07071067811865474*(17.32050807568877*alphax[2]*f[25]+8.660254037844386*alphavpar[0]*f[21]+19.36491673103709*alphax[0]*f[19]+(19.36491673103708*alphax[2]+7.745966692414834*alphavpar[1])*f[15]); 
  out[25] += 0.07071067811865474*(17.32050807568877*alphavpar[1]*f[24]+8.660254037844386*alphax[0]*f[22]+19.36491673103709*alphavpar[0]*f[19]+(7.745966692414834*alphax[2]+19.36491673103708*alphavpar[1])*f[16]); 
  out[26] += 0.6123724356957944*(2.23606797749979*(alphax[0]*f[25]+alphavpar[0]*f[24])+2.0*(alphax[2]+alphavpar[1])*f[19]); 
  return cflFreq; 
} 
double GyrokineticGenGeoVol1x2vTensorP2_Bvarsxz(const double q_, const double m_, const double *w, const double *dxv, const double *bmag, const double *jacobTotInv, const double *cmag, const double *b_x, const double *b_y, const double *b_z, const double *phi, const double *f, double *out) 
{ 
  // jacobTotInv: reciprocal of the conf-space jacobian time the guiding center coordinate Jacobian.
  // b_x,b_y,b_z: covariant components of the field aligned unit vector.
  // q_,m_: species charge and mass.
  // w[NDIM]: cell-center.
  // dxv[NDIM]: cell length.
  // bmag: magnetic field amplitude.
  // cmag: coefficient multiplying parallel gradient.
  // phi: electrostatic potential .
  // f: Distribution function.
  // out: output increment.

  double wx = w[0];
  double rdx2 = 2.0/dxv[0];
  double wvpar = w[1];
  double rdvpar2 = 2.0/dxv[1];
  double wmu = w[2];
  double rdmu2 = 2.0/dxv[2];

  double wxSq = w[0]*w[0];
  double rdx2Sq = rdx2*rdx2;
  double wvparSq = w[1]*w[1];
  double rdvpar2Sq = rdvpar2*rdvpar2;
  double wmuSq = w[2]*w[2];
  double rdmu2Sq = rdmu2*rdmu2;

  double hamil[27]; 
  hamil[0] = (0.2357022603955158*(3.0*rdvpar2Sq*(2.0*m_*wvparSq+2.828427124746191*(bmag[0]*wmu+phi[0]*q_))+2.0*m_))/rdvpar2Sq; 
  hamil[1] = 2.0*(bmag[1]*wmu+phi[1]*q_); 
  hamil[2] = (1.632993161855453*m_*wvpar)/rdvpar2; 
  hamil[3] = (1.154700538379252*bmag[0])/rdmu2; 
  hamil[5] = (1.154700538379252*bmag[1])/rdmu2; 
  hamil[7] = 2.0*(bmag[2]*wmu+phi[2]*q_); 
  hamil[8] = (0.421637021355784*m_)/rdvpar2Sq; 
  hamil[13] = (1.154700538379251*bmag[2])/rdmu2; 

  double BstarZdBmag[27]; 
  BstarZdBmag[0] = (1.414213562373095*(1.732050807568877*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2*wvpar+(cmag[2]*jacobTotInv[2]+cmag[1]*jacobTotInv[1]+cmag[0]*jacobTotInv[0])*q_))/q_; 
  BstarZdBmag[1] = (0.2828427124746191*(1.732050807568877*(b_y[2]*(10.0*jacobTotInv[2]+11.18033988749895*jacobTotInv[0])+5.0*b_y[1]*jacobTotInv[1])*m_*rdx2*wvpar+(4.47213595499958*(cmag[1]*jacobTotInv[2]+jacobTotInv[1]*cmag[2])+5.0*(cmag[0]*jacobTotInv[1]+jacobTotInv[0]*cmag[1]))*q_))/q_; 
  BstarZdBmag[2] = (1.414213562373095*(2.23606797749979*jacobTotInv[1]*b_y[2]+jacobTotInv[0]*b_y[1])*m_*rdx2)/(q_*rdvpar2); 
  BstarZdBmag[4] = (1.414213562373095*(b_y[2]*(2.0*jacobTotInv[2]+2.23606797749979*jacobTotInv[0])+b_y[1]*jacobTotInv[1])*m_*rdx2)/(q_*rdvpar2); 
  BstarZdBmag[7] = (0.04040610178208843*(60.6217782649107*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2*wvpar+((22.3606797749979*cmag[2]+35.0*cmag[0])*jacobTotInv[2]+7.0*(5.0*jacobTotInv[0]*cmag[2]+4.47213595499958*cmag[1]*jacobTotInv[1]))*q_))/q_; 
  BstarZdBmag[11] = (1.414213562373095*(b_y[1]*jacobTotInv[2]+2.0*jacobTotInv[1]*b_y[2])*m_*rdx2)/(q_*rdvpar2); 

  double cflFreq = 0.0; 
  double alphaL = 0.0; 
  double alphaR = 0.0; 
  double alphax[27]; 
  alphax[0] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[2]*hamil[8]+BstarZdBmag[0]*hamil[2])*rdvpar2*rdx2)/m_; 
  alphax[1] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[4]*hamil[8]+BstarZdBmag[1]*hamil[2])*rdvpar2*rdx2)/m_; 
  alphax[2] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[0]*hamil[8]+BstarZdBmag[2]*hamil[2])*rdvpar2*rdx2)/m_; 
  alphax[4] = (0.6123724356957944*(2.23606797749979*BstarZdBmag[1]*hamil[8]+hamil[2]*BstarZdBmag[4])*rdvpar2*rdx2)/m_; 
  alphax[7] = (0.3535533905932737*(3.872983346207417*hamil[8]*BstarZdBmag[11]+1.732050807568877*hamil[2]*BstarZdBmag[7])*rdvpar2*rdx2)/m_; 
  alphax[8] = (1.224744871391589*BstarZdBmag[2]*hamil[8]*rdvpar2*rdx2)/m_; 
  alphax[11] = (0.3535533905932737*(1.732050807568877*hamil[2]*BstarZdBmag[11]+3.872983346207417*BstarZdBmag[7]*hamil[8])*rdvpar2*rdx2)/m_; 
  alphax[12] = (1.224744871391589*BstarZdBmag[4]*hamil[8]*rdvpar2*rdx2)/m_; 
  alphax[20] = (1.224744871391589*hamil[8]*BstarZdBmag[11]*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = 0.125*(3.16227766016838*alphax[7]-2.449489742783178*alphax[1]+1.414213562373095*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.125*(3.16227766016838*alphax[7]+2.449489742783178*alphax[1]+1.414213562373095*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.883883476483184*alphax[20])+0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.883883476483184*alphax[20])+0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.883883476483184*alphax[20])+0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7071067811865475*alphax[20]-0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]-0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.883883476483184*alphax[20])-0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.883883476483184*alphax[20])-0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]-1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]-0.8215838362577489*alphax[4]-0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.883883476483184*alphax[20])-0.6846531968814574*alphax[12]-0.3952847075210473*alphax[8]+0.7905694150420947*alphax[7]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7071067811865475*alphax[20]+0.5477225575051661*alphax[12]+1.060660171779821*alphax[11]+0.3162277660168379*alphax[8]+0.7905694150420947*alphax[7]+0.8215838362577489*alphax[4]+0.4743416490252568*alphax[2]+0.6123724356957944*alphax[1]+0.3535533905932737*alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  double alphavpar[27]; 
  alphavpar[0] = -(0.6123724356957944*(2.23606797749979*BstarZdBmag[1]*hamil[7]+BstarZdBmag[0]*hamil[1])*rdvpar2*rdx2)/m_; 
  alphavpar[1] = -(0.6123724356957944*((2.0*BstarZdBmag[7]+2.23606797749979*BstarZdBmag[0])*hamil[7]+BstarZdBmag[1]*hamil[1])*rdvpar2*rdx2)/m_; 
  alphavpar[2] = -(0.6123724356957944*(2.23606797749979*BstarZdBmag[4]*hamil[7]+hamil[1]*BstarZdBmag[2])*rdvpar2*rdx2)/m_; 
  alphavpar[3] = -(0.3535533905932737*(3.872983346207417*BstarZdBmag[1]*hamil[13]+1.732050807568877*BstarZdBmag[0]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[4] = -(0.3535533905932737*(3.464101615137755*hamil[7]*BstarZdBmag[11]+1.732050807568877*(2.23606797749979*BstarZdBmag[2]*hamil[7]+hamil[1]*BstarZdBmag[4]))*rdvpar2*rdx2)/m_; 
  alphavpar[5] = -(0.3535533905932737*(3.872983346207417*(0.8944271909999159*BstarZdBmag[7]+BstarZdBmag[0])*hamil[13]+1.732050807568877*BstarZdBmag[1]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[6] = -(0.3535533905932737*(3.872983346207417*BstarZdBmag[4]*hamil[13]+1.732050807568877*BstarZdBmag[2]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[7] = -(0.6123724356957944*(2.0*BstarZdBmag[1]*hamil[7]+hamil[1]*BstarZdBmag[7])*rdvpar2*rdx2)/m_; 
  alphavpar[10] = -(0.3535533905932737*((3.464101615137754*BstarZdBmag[11]+3.872983346207417*BstarZdBmag[2])*hamil[13]+1.732050807568877*BstarZdBmag[4]*hamil[5])*rdvpar2*rdx2)/m_; 
  alphavpar[11] = -(0.3535533905932737*(1.732050807568877*hamil[1]*BstarZdBmag[11]+3.464101615137755*BstarZdBmag[4]*hamil[7])*rdvpar2*rdx2)/m_; 
  alphavpar[13] = -(0.3535533905932737*(3.464101615137754*BstarZdBmag[1]*hamil[13]+1.732050807568877*hamil[5]*BstarZdBmag[7])*rdvpar2*rdx2)/m_; 
  alphavpar[17] = -(0.6123724356957944*(2.0*BstarZdBmag[4]*hamil[13]+hamil[5]*BstarZdBmag[11])*rdvpar2*rdx2)/m_; 
#if cflType == SURFAVG 
  // Evaluate surface-averaged alpha on left.
  alphaL = -0.125*(2.449489742783178*alphavpar[2]-1.414213562373095*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate surface-averaged alpha on right.
  alphaR = 0.125*(2.449489742783178*alphavpar[2]+1.414213562373095*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // Evaluate alpha at left surface quadrature points.
  alphaL = 0.125*(0.7348469228349533*alphavpar[17]-0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.9185586535436913*alphavpar[17])+0.5303300858899104*alphavpar[13]+0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]+0.8215838362577489*alphavpar[6]-0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.7348469228349533*alphavpar[17]-0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.5477225575051661*alphavpar[11])+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[4]-0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]-0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.5477225575051661*alphavpar[11])+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[4]-0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.7348469228349533*alphavpar[17])+0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*(0.9185586535436913*alphavpar[17]-0.5303300858899104*alphavpar[13]+0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]-0.8215838362577489*alphavpar[6]+0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  alphaL = 0.125*((-0.7348469228349533*alphavpar[17])+0.4242640687119285*alphavpar[13]-0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]-0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // Evaluate alpha at right surface quadrature points.
  alphaR = 0.125*((-0.7348469228349533*alphavpar[17])-0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.9185586535436913*alphavpar[17]+0.5303300858899104*alphavpar[13]-0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]-0.8215838362577489*alphavpar[6]-0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.7348469228349533*alphavpar[17])-0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]-0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.5477225575051661*alphavpar[11]+0.3162277660168379*alphavpar[7]-0.8215838362577489*alphavpar[4]+0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.6846531968814574*alphavpar[11])-0.3952847075210473*alphavpar[7]+0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.5477225575051661*alphavpar[11]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[4]+0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7348469228349533*alphavpar[17]+0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]-1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]-0.6363961030678926*alphavpar[5]-0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]-0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*((-0.9185586535436913*alphavpar[17])-0.5303300858899104*alphavpar[13]-0.6846531968814574*alphavpar[11]-0.3952847075210473*alphavpar[7]+0.8215838362577489*alphavpar[6]+0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
  alphaR = 0.125*(0.7348469228349533*alphavpar[17]+0.4242640687119285*alphavpar[13]+0.5477225575051661*alphavpar[11]+1.10227038425243*alphavpar[10]+0.3162277660168379*alphavpar[7]+0.8215838362577489*alphavpar[6]+0.6363961030678926*alphavpar[5]+0.8215838362577489*alphavpar[4]+0.4743416490252568*alphavpar[3]+0.6123724356957944*alphavpar[2]+0.4743416490252568*alphavpar[1]+0.3535533905932737*alphavpar[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#endif 

  out[1] += 0.6123724356957944*(alphax[20]*f[20]+alphax[12]*f[12]+alphax[11]*f[11]+alphax[8]*f[8]+alphax[7]*f[7]+alphax[4]*f[4]+alphax[2]*f[2]+alphax[1]*f[1]+alphax[0]*f[0]); 
  out[2] += 0.6123724356957944*(alphavpar[17]*f[17]+alphavpar[13]*f[13]+alphavpar[11]*f[11]+alphavpar[10]*f[10]+alphavpar[7]*f[7]+alphavpar[6]*f[6]+alphavpar[5]*f[5]+alphavpar[4]*f[4]+alphavpar[3]*f[3]+alphavpar[2]*f[2]+alphavpar[1]*f[1]+alphavpar[0]*f[0]); 
  out[4] += 0.07071067811865474*(7.745966692414834*(alphax[11]*f[20]+f[11]*alphax[20]+alphavpar[10]*f[17]+f[10]*alphavpar[17]+alphavpar[5]*f[13]+f[5]*alphavpar[13]+alphax[4]*f[12]+f[4]*alphax[12])+(8.660254037844387*alphax[7]+7.745966692414834*alphavpar[4])*f[11]+8.660254037844387*f[7]*alphax[11]+7.745966692414834*f[4]*alphavpar[11]+8.660254037844386*(alphavpar[6]*f[10]+f[6]*alphavpar[10])+7.745966692414834*(alphax[2]*f[8]+f[2]*alphax[8]+alphavpar[1]*f[7]+f[1]*alphavpar[7])+8.660254037844386*(alphavpar[3]*f[5]+f[3]*alphavpar[5]+(alphavpar[2]+alphax[1])*f[4]+f[1]*alphax[4]+f[2]*(alphavpar[4]+alphax[0])+f[0]*alphax[2]+alphavpar[0]*f[1]+f[0]*alphavpar[1])); 
  out[5] += 0.07071067811865474*(8.660254037844386*alphax[20]*f[23]+8.660254037844387*(alphax[12]*f[18]+alphax[11]*f[17]+alphax[8]*f[14]+alphax[7]*f[13])+8.660254037844386*(alphax[4]*f[10]+alphax[2]*f[6]+alphax[1]*f[5]+alphax[0]*f[3])); 
  out[6] += 0.07071067811865474*(7.745966692414834*(alphavpar[17]*f[24]+alphavpar[13]*f[21]+alphavpar[10]*f[19])+8.660254037844387*(alphavpar[11]*f[17]+f[11]*alphavpar[17])+7.745966692414834*(alphavpar[6]*f[16]+alphavpar[5]*f[15])+8.660254037844387*(alphavpar[7]*f[13]+f[7]*alphavpar[13])+8.660254037844386*(alphavpar[4]*f[10]+f[4]*alphavpar[10])+7.745966692414834*alphavpar[3]*f[9]+8.660254037844386*(alphavpar[2]*f[6]+f[2]*alphavpar[6]+alphavpar[1]*f[5]+f[1]*alphavpar[5]+alphavpar[0]*f[3]+f[0]*alphavpar[3])); 
  out[7] += 0.07071067811865474*(17.32050807568877*(alphax[12]*f[20]+f[12]*alphax[20])+19.36491673103708*(alphax[8]*f[12]+f[8]*alphax[12])+17.32050807568877*(alphax[4]*f[11]+f[4]*alphax[11])+17.32050807568877*(alphax[1]*f[7]+f[1]*alphax[7])+19.36491673103709*(alphax[2]*f[4]+f[2]*alphax[4]+alphax[0]*f[1]+f[0]*alphax[1])); 
  out[8] += 0.07071067811865474*(17.32050807568877*alphavpar[17]*f[23]+17.32050807568877*alphavpar[11]*f[20]+17.32050807568877*alphavpar[10]*f[18]+19.36491673103708*(alphavpar[13]*f[17]+f[13]*alphavpar[17])+17.32050807568877*(alphavpar[6]*f[14]+alphavpar[4]*f[12])+19.36491673103708*(alphavpar[7]*f[11]+f[7]*alphavpar[11])+19.36491673103709*(alphavpar[5]*f[10]+f[5]*alphavpar[10])+17.32050807568877*alphavpar[2]*f[8]+19.36491673103709*(alphavpar[3]*f[6]+f[3]*alphavpar[6]+alphavpar[1]*f[4]+f[1]*alphavpar[4]+alphavpar[0]*f[2]+f[0]*alphavpar[2])); 
  out[10] += 0.07071067811865474*(6.928203230275509*alphavpar[10]*f[24]+7.745966692414834*alphax[11]*f[23]+6.928203230275509*alphavpar[5]*f[21]+7.745966692414834*f[17]*alphax[20]+6.928203230275509*alphavpar[17]*f[19]+7.745966692414834*(alphavpar[6]*f[19]+alphax[4]*f[18])+8.660254037844386*alphax[7]*f[17]+7.745966692414834*(alphavpar[4]*f[17]+f[4]*alphavpar[17]+alphavpar[10]*f[16])+6.928203230275509*alphavpar[13]*f[15]+7.745966692414834*(alphavpar[3]*f[15]+alphax[2]*f[14])+8.660254037844386*alphax[11]*f[13]+7.745966692414834*(alphavpar[1]*f[13]+f[1]*alphavpar[13]+f[10]*alphax[12]+alphavpar[10]*f[11]+f[10]*alphavpar[11])+8.660254037844386*((alphavpar[2]+alphax[1])*f[10]+f[2]*alphavpar[10])+7.745966692414834*(alphavpar[5]*f[9]+f[6]*alphax[8]+alphavpar[5]*f[7]+f[5]*alphavpar[7])+8.660254037844386*((alphavpar[4]+alphax[0])*f[6]+f[4]*alphavpar[6]+(alphax[4]+alphavpar[0])*f[5]+f[0]*alphavpar[5]+(alphax[2]+alphavpar[1])*f[3]+f[1]*alphavpar[3])); 
  out[11] += 0.01010152544552211*(108.4435336938077*(alphax[4]*f[20]+f[4]*alphax[20])+38.72983346207417*alphavpar[17]*f[17]+60.62177826491071*(alphavpar[6]*f[17]+f[6]*alphavpar[17])+38.72983346207417*alphavpar[13]*f[13]+60.6217782649107*(alphavpar[3]*f[13]+f[3]*alphavpar[13])+(108.4435336938077*alphax[11]+121.2435565298214*alphax[2])*f[12]+(108.4435336938077*f[11]+121.2435565298214*f[2])*alphax[12]+(38.72983346207417*alphavpar[11]+60.6217782649107*alphavpar[2])*f[11]+121.2435565298214*(alphax[1]*f[11]+f[1]*alphax[11])+60.6217782649107*f[2]*alphavpar[11]+54.22176684690384*alphavpar[10]*f[10]+121.2435565298214*(alphax[4]*f[8]+f[4]*alphax[8])+(38.72983346207417*alphavpar[7]+121.2435565298214*alphax[4]+60.62177826491071*alphavpar[0])*f[7]+121.2435565298214*f[4]*alphax[7]+60.62177826491071*f[0]*alphavpar[7]+54.22176684690384*(alphavpar[5]*f[5]+alphavpar[4]*f[4])+135.5544171172596*(alphax[0]*f[4]+f[0]*alphax[4]+alphax[1]*f[2])+f[1]*(135.5544171172596*alphax[2]+54.22176684690384*alphavpar[1])); 
  out[12] += 0.01010152544552211*(108.4435336938077*alphavpar[10]*f[23]+(38.72983346207417*alphax[20]+60.62177826491071*alphax[7]+108.4435336938077*alphavpar[4])*f[20]+60.62177826491071*f[7]*alphax[20]+108.4435336938077*alphavpar[17]*f[18]+121.2435565298214*(alphavpar[6]*f[18]+alphavpar[5]*f[17]+f[5]*alphavpar[17])+121.2435565298214*(alphavpar[10]*(f[14]+f[13])+f[10]*alphavpar[13])+(38.72983346207417*alphax[12]+108.4435336938077*alphavpar[11]+121.2435565298214*alphavpar[2])*f[12]+60.6217782649107*(alphax[1]*f[12]+f[1]*alphax[12])+54.22176684690384*alphax[11]*f[11]+121.2435565298214*(alphavpar[1]*f[11]+f[1]*alphavpar[11])+135.5544171172596*(alphavpar[3]*f[10]+f[3]*alphavpar[10])+(38.72983346207417*alphax[8]+121.2435565298214*alphavpar[4])*f[8]+60.62177826491071*(alphax[0]*f[8]+f[0]*alphax[8])+121.2435565298214*(alphavpar[4]*f[7]+f[4]*alphavpar[7])+135.5544171172596*(alphavpar[5]*f[6]+f[5]*alphavpar[6])+54.22176684690384*alphax[4]*f[4]+135.5544171172596*(alphavpar[0]*f[4]+f[0]*alphavpar[4])+54.22176684690384*alphax[2]*f[2]+135.5544171172596*(alphavpar[1]*f[2]+f[1]*alphavpar[2])); 
  out[13] += 0.07071067811865474*(17.32050807568877*alphax[12]*f[23]+f[18]*(17.32050807568877*alphax[20]+19.36491673103708*alphax[8])+17.32050807568877*alphax[4]*f[17]+19.36491673103708*alphax[12]*f[14]+17.32050807568877*alphax[1]*f[13]+f[10]*(17.32050807568877*alphax[11]+19.36491673103708*alphax[2])+17.32050807568877*f[5]*alphax[7]+19.36491673103708*(alphax[4]*f[6]+alphax[0]*f[5]+alphax[1]*f[3])); 
  out[14] += 0.07071067811865474*(15.49193338482967*(alphavpar[17]*f[26]+alphavpar[10]*f[25])+17.32050807568877*(alphavpar[13]*f[24]+alphavpar[11]*f[23])+15.49193338482967*alphavpar[6]*f[22]+17.32050807568877*(alphavpar[17]*(f[21]+f[20])+alphavpar[5]*f[19]+alphavpar[4]*f[18])+19.36491673103708*(alphavpar[7]*f[17]+f[7]*alphavpar[17])+17.32050807568877*(alphavpar[3]*f[16]+alphavpar[10]*f[15]+alphavpar[2]*f[14])+19.36491673103708*(alphavpar[11]*f[13]+f[11]*alphavpar[13])+17.32050807568877*alphavpar[10]*f[12]+19.36491673103708*(alphavpar[1]*f[10]+f[1]*alphavpar[10])+17.32050807568877*alphavpar[6]*(f[9]+f[8])+19.36491673103708*(alphavpar[0]*f[6]+f[0]*alphavpar[6]+alphavpar[4]*f[5]+f[4]*alphavpar[5]+alphavpar[2]*f[3]+f[2]*alphavpar[3])); 
  out[15] += 0.07071067811865474*(8.660254037844387*alphax[20]*f[26]+8.660254037844386*(alphax[12]*f[25]+alphax[11]*f[24])+8.660254037844387*(alphax[8]*f[22]+alphax[7]*f[21]+alphax[4]*f[19])+8.660254037844386*(alphax[2]*f[16]+alphax[1]*f[15])+8.660254037844387*alphax[0]*f[9]); 
  out[16] += 0.07071067811865474*(8.660254037844386*alphavpar[11]*f[24]+8.660254037844387*(alphavpar[7]*f[21]+alphavpar[4]*f[19])+7.745966692414834*alphavpar[17]*f[17]+8.660254037844386*(alphavpar[2]*f[16]+alphavpar[1]*f[15])+7.745966692414834*(alphavpar[13]*f[13]+alphavpar[10]*f[10])+8.660254037844387*alphavpar[0]*f[9]+7.745966692414834*(alphavpar[6]*f[6]+alphavpar[5]*f[5]+alphavpar[3]*f[3])); 
  out[17] += 0.002020305089104421*((173.2050807568877*alphavpar[17]+271.1088342345192*alphavpar[6])*f[24]+542.2176684690385*alphax[4]*f[23]+(173.2050807568878*alphavpar[13]+271.1088342345192*alphavpar[3])*f[21]+542.2176684690385*f[10]*alphax[20]+242.4871130596428*alphavpar[10]*f[19]+(542.2176684690384*alphax[11]+606.217782649107*alphax[2])*f[18]+(542.2176684690384*alphax[12]+193.6491673103708*alphavpar[11]+303.1088913245535*alphavpar[2]+606.217782649107*alphax[1])*f[17]+(271.1088342345192*f[16]+193.6491673103708*f[11]+303.1088913245535*f[2])*alphavpar[17]+242.4871130596428*alphavpar[5]*f[15]+606.2177826491072*alphax[4]*f[14]+(193.6491673103708*alphavpar[7]+606.2177826491072*alphax[4]+303.1088913245536*alphavpar[0])*f[13]+(271.1088342345192*f[9]+193.6491673103708*f[7]+303.1088913245536*f[0])*alphavpar[13]+606.2177826491072*f[6]*alphax[12]+303.1088913245536*alphavpar[6]*f[11]+606.2177826491072*f[5]*alphax[11]+303.1088913245536*f[6]*alphavpar[11]+(606.217782649107*(alphax[8]+alphax[7])+271.1088342345192*alphavpar[4]+677.7720855862981*alphax[0])*f[10]+271.1088342345192*f[4]*alphavpar[10]+303.1088913245535*(alphavpar[3]*f[7]+f[3]*alphavpar[7])+677.7720855862981*(alphax[1]*f[6]+alphax[2]*f[5])+271.1088342345192*(alphavpar[1]*f[5]+f[1]*alphavpar[5])+677.7720855862981*f[3]*alphax[4]); 
  out[18] += 0.01010152544552211*(96.99484522385713*(alphavpar[10]*f[26]+alphavpar[17]*f[25])+108.4435336938077*(alphavpar[6]*f[25]+alphavpar[5]*f[24])+(38.72983346207418*alphax[20]+60.6217782649107*alphax[7])*f[23]+108.4435336938077*(alphavpar[4]*f[23]+alphavpar[10]*(f[22]+f[21]+f[20]))+60.62177826491071*f[13]*alphax[20]+(108.4435336938077*alphavpar[13]+121.2435565298214*alphavpar[3])*f[19]+(38.72983346207417*alphax[12]+108.4435336938077*alphavpar[11]+121.2435565298214*alphavpar[2]+60.6217782649107*alphax[1])*f[18]+(54.22176684690384*alphax[11]+121.2435565298214*alphavpar[1])*f[17]+(108.4435336938077*(f[15]+f[12])+121.2435565298214*f[1])*alphavpar[17]+121.2435565298214*(alphavpar[5]*f[16]+alphavpar[6]*f[15])+(38.72983346207417*alphax[8]+121.2435565298214*alphavpar[4]+60.62177826491071*alphax[0])*f[14]+121.2435565298214*(alphavpar[4]*f[13]+f[4]*alphavpar[13]+alphavpar[6]*f[12])+60.62177826491071*f[5]*alphax[12]+121.2435565298214*(alphavpar[5]*f[11]+f[5]*alphavpar[11])+(121.2435565298214*alphavpar[7]+54.22176684690384*alphax[4]+135.5544171172596*alphavpar[0])*f[10]+(121.2435565298214*(f[9]+f[8]+f[7])+135.5544171172596*f[0])*alphavpar[10]+60.6217782649107*f[3]*alphax[8]+54.22176684690384*alphax[2]*f[6]+135.5544171172596*(alphavpar[1]*f[6]+f[1]*alphavpar[6]+alphavpar[2]*f[5]+f[2]*alphavpar[5]+alphavpar[3]*f[4]+f[3]*alphavpar[4])); 
  out[19] += 0.01414213562373095*(38.72983346207417*alphax[11]*f[26]+38.72983346207418*alphax[4]*f[25]+(38.72983346207418*alphax[20]+43.30127018922193*alphax[7])*f[24]+38.72983346207418*(alphavpar[4]*f[24]+alphax[2]*f[22])+(43.30127018922195*alphax[11]+38.72983346207418*alphavpar[1])*f[21]+(38.72983346207417*(alphax[12]+alphavpar[11])+43.30127018922193*(alphavpar[2]+alphax[1]))*f[19]+34.64101615137754*(alphavpar[10]*f[17]+f[10]*alphavpar[17])+(38.72983346207417*alphax[8]+43.30127018922195*(alphavpar[4]+alphax[0]))*f[16]+(38.72983346207417*alphavpar[7]+43.30127018922195*(alphax[4]+alphavpar[0]))*f[15]+34.64101615137755*(alphavpar[5]*f[13]+f[5]*alphavpar[13])+38.72983346207418*(alphavpar[6]*f[10]+f[6]*alphavpar[10])+43.30127018922193*(alphax[2]+alphavpar[1])*f[9]+38.72983346207418*(alphavpar[3]*f[5]+f[3]*alphavpar[5])); 
  out[20] += 0.01010152544552211*((77.45966692414835*alphavpar[17]+121.2435565298214*alphavpar[6])*f[23]+(77.45966692414834*(alphax[12]+alphavpar[11])+121.2435565298214*(alphavpar[2]+alphax[1]))*f[20]+(77.45966692414834*f[12]+121.2435565298214*f[1])*alphax[20]+108.4435336938077*alphavpar[10]*f[18]+(86.60254037844389*alphavpar[13]+135.5544171172596*alphavpar[3])*f[17]+(121.2435565298214*f[14]+86.60254037844389*f[13]+135.5544171172596*f[3])*alphavpar[17]+135.5544171172596*(alphavpar[6]*f[13]+f[6]*alphavpar[13])+(86.60254037844389*alphax[8]+121.2435565298214*alphax[7]+108.4435336938077*alphavpar[4]+135.5544171172596*alphax[0])*f[12]+(86.60254037844389*f[8]+121.2435565298214*f[7]+135.5544171172596*f[0])*alphax[12]+(86.60254037844389*alphavpar[7]+108.4435336938077*alphax[4]+135.5544171172596*alphavpar[0])*f[11]+108.4435336938077*f[4]*alphax[11]+(121.2435565298214*f[8]+86.60254037844389*f[7]+135.5544171172596*f[0])*alphavpar[11]+121.2435565298214*(alphavpar[5]*f[10]+f[5]*alphavpar[10])+135.5544171172596*(alphax[1]*f[8]+f[1]*alphax[8]+alphavpar[2]*f[7]+f[2]*alphavpar[7])+121.2435565298214*((alphax[2]+alphavpar[1])*f[4]+f[2]*alphax[4]+f[1]*alphavpar[4])); 
  out[21] += 0.07071067811865474*(17.32050807568877*alphax[12]*f[26]+(17.32050807568877*alphax[20]+19.36491673103709*alphax[8])*f[25]+17.32050807568877*alphax[4]*f[24]+19.36491673103708*alphax[12]*f[22]+17.32050807568877*alphax[1]*f[21]+(17.32050807568877*alphax[11]+19.36491673103709*alphax[2])*f[19]+19.36491673103708*alphax[4]*f[16]+(17.32050807568877*alphax[7]+19.36491673103708*alphax[0])*f[15]+19.36491673103709*alphax[1]*f[9]); 
  out[22] += 0.07071067811865474*(17.32050807568877*alphavpar[11]*f[26]+17.32050807568877*alphavpar[4]*f[25]+19.36491673103709*alphavpar[7]*f[24]+15.49193338482967*alphavpar[17]*f[23]+17.32050807568877*alphavpar[2]*f[22]+19.36491673103708*alphavpar[11]*f[21]+19.36491673103709*alphavpar[1]*f[19]+15.49193338482967*alphavpar[10]*f[18]+17.32050807568877*(alphavpar[13]*f[17]+f[13]*alphavpar[17])+19.36491673103708*(alphavpar[0]*f[16]+alphavpar[4]*f[15])+15.49193338482967*alphavpar[6]*f[14]+17.32050807568877*(alphavpar[5]*f[10]+f[5]*alphavpar[10])+19.36491673103709*alphavpar[2]*f[9]+17.32050807568877*(alphavpar[3]*f[6]+f[3]*alphavpar[6])); 
  out[23] += 0.01010152544552211*((69.28203230275508*alphavpar[17]+108.4435336938077*alphavpar[6])*f[26]+96.99484522385713*alphavpar[10]*f[25]+(77.45966692414834*alphavpar[13]+121.2435565298214*alphavpar[3])*f[24]+(77.45966692414834*(alphax[12]+alphavpar[11])+121.2435565298214*(alphavpar[2]+alphax[1]))*f[23]+108.4435336938077*alphavpar[17]*f[22]+(77.45966692414835*alphavpar[17]+121.2435565298214*alphavpar[6])*f[21]+(77.45966692414835*alphavpar[17]+121.2435565298214*alphavpar[6])*f[20]+(77.45966692414835*f[18]+121.2435565298214*f[5])*alphax[20]+108.4435336938077*alphavpar[5]*f[19]+(86.60254037844386*alphax[8]+121.2435565298214*alphax[7]+108.4435336938077*alphavpar[4]+135.5544171172596*alphax[0])*f[18]+(86.60254037844386*alphavpar[7]+108.4435336938077*alphax[4]+135.5544171172596*alphavpar[0])*f[17]+(121.2435565298214*(f[9]+f[8])+86.60254037844386*f[7]+135.5544171172596*f[0])*alphavpar[17]+121.2435565298214*alphavpar[13]*f[16]+108.4435336938077*alphavpar[10]*f[15]+(86.60254037844386*alphax[12]+121.2435565298214*alphavpar[11]+135.5544171172596*alphax[1])*f[14]+(121.2435565298214*alphax[12]+86.60254037844386*alphavpar[11]+135.5544171172596*alphavpar[2])*f[13]+(86.60254037844386*f[11]+135.5544171172596*f[2])*alphavpar[13]+108.4435336938077*alphavpar[10]*f[12]+135.5544171172596*(f[3]*alphax[12]+alphavpar[3]*f[11])+108.4435336938077*f[10]*alphax[11]+135.5544171172596*f[3]*alphavpar[11]+121.2435565298214*((alphax[2]+alphavpar[1])*f[10]+f[1]*alphavpar[10])+135.5544171172596*(f[5]*alphax[8]+alphavpar[6]*f[7]+f[6]*alphavpar[7])+121.2435565298214*(alphax[4]*f[6]+alphavpar[4]*f[5]+f[4]*alphavpar[5])); 
  out[24] += 0.01010152544552211*(108.4435336938077*alphax[4]*f[26]+(108.4435336938077*alphax[11]+121.2435565298214*alphax[2])*f[25]+(108.4435336938077*alphax[12]+38.72983346207417*alphavpar[11]+60.6217782649107*alphavpar[2])*f[24]+121.2435565298214*(alphax[1]*f[24]+alphax[4]*f[22])+(38.72983346207418*alphavpar[7]+121.2435565298214*alphax[4]+60.6217782649107*alphavpar[0])*f[21]+f[19]*(108.4435336938077*alphax[20]+121.2435565298214*(alphax[8]+alphax[7])+54.22176684690384*alphavpar[4]+135.5544171172596*alphax[0])+34.64101615137754*alphavpar[17]*f[17]+54.22176684690384*(alphavpar[6]*f[17]+f[6]*alphavpar[17])+(121.2435565298214*alphax[12]+60.6217782649107*alphavpar[11]+135.5544171172596*alphax[1])*f[16]+(121.2435565298214*alphax[11]+135.5544171172596*alphax[2]+54.22176684690384*alphavpar[1])*f[15]+34.64101615137754*alphavpar[13]*f[13]+54.22176684690384*(alphavpar[3]*f[13]+f[3]*alphavpar[13])+48.49742261192856*alphavpar[10]*f[10]+(60.6217782649107*alphavpar[7]+135.5544171172596*alphax[4])*f[9]+48.49742261192856*alphavpar[5]*f[5]); 
  out[25] += 0.01010152544552211*((38.72983346207418*alphax[20]+60.6217782649107*alphax[7]+108.4435336938077*alphavpar[4])*f[26]+(38.72983346207417*alphax[12]+108.4435336938077*alphavpar[11]+121.2435565298214*alphavpar[2]+60.6217782649107*alphax[1])*f[25]+(54.22176684690384*alphax[11]+121.2435565298214*alphavpar[1])*f[24]+96.99484522385713*alphavpar[10]*f[23]+(38.72983346207418*alphax[8]+121.2435565298214*alphavpar[4]+60.6217782649107*alphax[0])*f[22]+(60.6217782649107*alphax[20]+121.2435565298214*alphavpar[4])*f[21]+(121.2435565298214*alphavpar[7]+54.22176684690384*alphax[4]+135.5544171172596*alphavpar[0])*f[19]+96.99484522385713*alphavpar[17]*f[18]+108.4435336938077*(alphavpar[6]*f[18]+alphavpar[5]*f[17]+f[5]*alphavpar[17])+(54.22176684690384*alphax[2]+135.5544171172596*alphavpar[1])*f[16]+(60.6217782649107*alphax[12]+121.2435565298214*alphavpar[11]+135.5544171172596*alphavpar[2])*f[15]+108.4435336938077*(alphavpar[10]*(f[14]+f[13])+f[10]*alphavpar[13])+121.2435565298214*(alphavpar[3]*f[10]+f[3]*alphavpar[10])+(60.6217782649107*alphax[8]+135.5544171172596*alphavpar[4])*f[9]+121.2435565298214*(alphavpar[5]*f[6]+f[5]*alphavpar[6])); 
  out[26] += 0.01010152544552211*((77.45966692414834*(alphax[12]+alphavpar[11])+121.2435565298214*(alphavpar[2]+alphax[1]))*f[26]+(77.45966692414835*alphax[20]+86.60254037844386*alphax[8]+121.2435565298214*alphax[7]+108.4435336938077*alphavpar[4]+135.5544171172596*alphax[0])*f[25]+(86.60254037844386*alphavpar[7]+108.4435336938077*alphax[4]+135.5544171172596*alphavpar[0])*f[24]+(69.28203230275508*alphavpar[17]+108.4435336938077*alphavpar[6])*f[23]+(86.60254037844389*alphax[12]+121.2435565298214*alphavpar[11]+135.5544171172596*alphax[1])*f[22]+(121.2435565298214*alphax[12]+86.60254037844389*alphavpar[11]+135.5544171172596*alphavpar[2])*f[21]+121.2435565298214*f[15]*alphax[20]+(108.4435336938077*alphax[11]+121.2435565298214*(alphax[2]+alphavpar[1]))*f[19]+96.99484522385713*alphavpar[10]*f[18]+(77.45966692414834*alphavpar[13]+121.2435565298214*alphavpar[3])*f[17]+(108.4435336938077*f[14]+77.45966692414834*f[13]+121.2435565298214*f[3])*alphavpar[17]+(135.5544171172596*alphavpar[7]+121.2435565298214*alphax[4])*f[16]+135.5544171172596*alphax[8]*f[15]+121.2435565298214*(alphavpar[4]*f[15]+alphavpar[6]*f[13]+f[6]*alphavpar[13])+135.5544171172596*f[9]*(alphax[12]+alphavpar[11])+108.4435336938077*(alphavpar[5]*f[10]+f[5]*alphavpar[10])); 
  return cflFreq; 
} 
