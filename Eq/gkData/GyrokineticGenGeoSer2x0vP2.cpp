#include <GyrokineticGenGeoModDecl.h> 
double GyrokineticGenGeoVol2x0vSerP2_Bvars_0(const double q_, const double m_, const double *w, const double *dxv, const double *Bmag, const double *jacobTotInv, const double *Gradpar, const double *geoX, const double *geoY, const double *geoZ, const double *Phi, const double *f, double *out) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_y = 2.0/dxv[1]; 
  double wx = w[0]; 
  double wy = w[1]; 
  double q2 = q_*q_; 
  double m2 = m_*m_; 
  double hamil[8]; 
  hamil[0] = Phi[0]*q_; 
  hamil[1] = Phi[1]*q_; 
  hamil[2] = Phi[2]*q_; 
  hamil[3] = Phi[3]*q_; 
  hamil[4] = Phi[4]*q_; 
  hamil[5] = Phi[5]*q_; 
  hamil[6] = Phi[6]*q_; 
  hamil[7] = Phi[7]*q_; 
  double BstarX_by_Bmag[8]; 

  double BstarY_by_Bmag[8]; 

  double cflFreq = 0.0; 
  double alphaL = 0.0; 
  double alphaR = 0.0; 
  double alphax[8]; 
  alphax[0] = -(0.4330127018922193*geoZ[0]*jacobTotInv[0]*hamil[2]*dfac_x*dfac_y)/q_; 
  alphax[1] = -(0.4330127018922193*geoZ[0]*jacobTotInv[0]*hamil[3]*dfac_x*dfac_y)/q_; 
  alphax[2] = -(0.9682458365518543*geoZ[0]*jacobTotInv[0]*hamil[5]*dfac_x*dfac_y)/q_; 
  alphax[3] = -(0.9682458365518543*geoZ[0]*jacobTotInv[0]*hamil[7]*dfac_x*dfac_y)/q_; 
  alphax[4] = -(0.4330127018922193*geoZ[0]*jacobTotInv[0]*hamil[6]*dfac_x*dfac_y)/q_; 
#if cflType == SURFAVG 
  // evaluate surface-averaged alpha on left 
  alphaL = 0.25*(2.23606797749979*alphax[4]-1.732050807568877*alphax[1]+alphax[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // evaluate surface-averaged alpha on right 
  alphaR = 0.25*(2.23606797749979*alphax[4]+1.732050807568877*alphax[1]+alphax[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // evaluate alpha at left surface quadrature points 
  alphaL = 0.25*(1.118033988749895*alphax[4]+1.161895003862225*alphax[3]-0.6708203932499369*alphax[2]-0.8660254037844386*alphax[1]+0.5*alphax[0]); 
  cflFreq = std::max(cflFreq,-0.5*(alphaL-std::abs(alphaL))); 
  alphaL = 0.25*(1.118033988749895*alphax[4]-0.8660254037844386*alphax[1]+0.5*alphax[0]); 
  cflFreq = std::max(cflFreq,-0.5*(alphaL-std::abs(alphaL))); 
  alphaL = 0.25*(1.118033988749895*alphax[4]-1.161895003862225*alphax[3]+0.6708203932499369*alphax[2]-0.8660254037844386*alphax[1]+0.5*alphax[0]); 
  cflFreq = std::max(cflFreq,-0.5*(alphaL-std::abs(alphaL))); 
  // evaluate alpha at right surface quadrature points 
  alphaR = 0.25*(1.118033988749895*alphax[4]-1.161895003862225*alphax[3]-0.6708203932499369*alphax[2]+0.8660254037844386*alphax[1]+0.5*alphax[0]); 
  cflFreq = std::max(cflFreq,0.5*(alphaR+std::abs(alphaR))); 
  alphaR = 0.25*(1.118033988749895*alphax[4]+0.8660254037844386*alphax[1]+0.5*alphax[0]); 
  cflFreq = std::max(cflFreq,0.5*(alphaR+std::abs(alphaR))); 
  alphaR = 0.25*(1.118033988749895*alphax[4]+1.161895003862225*alphax[3]+0.6708203932499369*alphax[2]+0.8660254037844386*alphax[1]+0.5*alphax[0]); 
  cflFreq = std::max(cflFreq,0.5*(alphaR+std::abs(alphaR))); 
#endif 

  double alphay[8]; 
  alphay[0] = (0.4330127018922193*geoZ[0]*jacobTotInv[0]*hamil[1]*dfac_x*dfac_y)/q_; 
  alphay[1] = (0.9682458365518543*geoZ[0]*jacobTotInv[0]*hamil[4]*dfac_x*dfac_y)/q_; 
  alphay[2] = (0.4330127018922193*geoZ[0]*jacobTotInv[0]*hamil[3]*dfac_x*dfac_y)/q_; 
  alphay[3] = (0.9682458365518543*geoZ[0]*jacobTotInv[0]*hamil[6]*dfac_x*dfac_y)/q_; 
  alphay[5] = (0.4330127018922194*geoZ[0]*jacobTotInv[0]*hamil[7]*dfac_x*dfac_y)/q_; 
#if cflType == SURFAVG 
  // evaluate surface-averaged alpha on left 
  alphaL = 0.25*(2.23606797749979*alphay[5]-1.732050807568877*alphay[2]+alphay[0]); 
  cflFreq += -0.5*(alphaL-std::abs(alphaL)); 
  // evaluate surface-averaged alpha on right 
  alphaR = 0.25*(2.23606797749979*alphay[5]+1.732050807568877*alphay[2]+alphay[0]); 
  cflFreq += 0.5*(alphaR+std::abs(alphaR)); 
#elif cflType == QUAD 
  // evaluate alpha at left surface quadrature points 
  alphaL = 0.25*(1.118033988749895*alphay[5]+1.161895003862225*alphay[3]-0.8660254037844386*alphay[2]-0.6708203932499369*alphay[1]+0.5*alphay[0]); 
  cflFreq = std::max(cflFreq,-0.5*(alphaL-std::abs(alphaL))); 
  alphaL = 0.25*(1.118033988749895*alphay[5]-0.8660254037844386*alphay[2]+0.5*alphay[0]); 
  cflFreq = std::max(cflFreq,-0.5*(alphaL-std::abs(alphaL))); 
  alphaL = 0.25*(1.118033988749895*alphay[5]-1.161895003862225*alphay[3]-0.8660254037844386*alphay[2]+0.6708203932499369*alphay[1]+0.5*alphay[0]); 
  cflFreq = std::max(cflFreq,-0.5*(alphaL-std::abs(alphaL))); 
  // evaluate alpha at right surface quadrature points 
  alphaR = 0.25*(1.118033988749895*alphay[5]-1.161895003862225*alphay[3]+0.8660254037844386*alphay[2]-0.6708203932499369*alphay[1]+0.5*alphay[0]); 
  cflFreq = std::max(cflFreq,0.5*(alphaR+std::abs(alphaR))); 
  alphaR = 0.25*(1.118033988749895*alphay[5]+0.8660254037844386*alphay[2]+0.5*alphay[0]); 
  cflFreq = std::max(cflFreq,0.5*(alphaR+std::abs(alphaR))); 
  alphaR = 0.25*(1.118033988749895*alphay[5]+1.161895003862225*alphay[3]+0.8660254037844386*alphay[2]+0.6708203932499369*alphay[1]+0.5*alphay[0]); 
  cflFreq = std::max(cflFreq,0.5*(alphaR+std::abs(alphaR))); 
#endif 

  out[1] += 0.8660254037844386*(alphax[4]*f[4]+alphax[3]*f[3]+alphax[2]*f[2]+alphax[1]*f[1]+alphax[0]*f[0]); 
  out[2] += 0.8660254037844386*(alphay[5]*f[5]+alphay[3]*f[3]+alphay[2]*f[2]+alphay[1]*f[1]+alphay[0]*f[0]); 
  out[3] += 0.1*((8.660254037844387*alphay[5]+7.745966692414834*alphax[3])*f[7]+8.660254037844387*alphax[4]*f[6]+7.745966692414834*(alphay[3]*f[6]+alphax[2]*f[5]+alphay[1]*f[4])+8.660254037844386*((alphay[2]+alphax[1])*f[3]+f[2]*alphay[3]+f[1]*alphax[3]+alphax[0]*f[2]+f[0]*alphax[2]+alphay[0]*f[1]+f[0]*alphay[1])); 
  out[4] += 0.1*(17.32050807568877*alphax[3]*f[6]+17.32050807568877*(alphax[1]*f[4]+f[1]*alphax[4])+19.36491673103709*(alphax[2]*f[3]+f[2]*alphax[3]+alphax[0]*f[1]+f[0]*alphax[1])); 
  out[5] += 0.1*(17.32050807568877*alphay[3]*f[7]+17.32050807568877*(alphay[2]*f[5]+f[2]*alphay[5])+19.36491673103709*(alphay[1]*f[3]+f[1]*alphay[3]+alphay[0]*f[2]+f[0]*alphay[2])); 
  out[6] += 0.1*(17.32050807568877*alphax[2]*f[7]+(8.660254037844386*alphay[2]+17.32050807568877*alphax[1])*f[6]+17.32050807568877*alphax[3]*f[5]+(17.32050807568877*alphax[3]+8.660254037844387*alphay[0])*f[4]+f[3]*(17.32050807568877*alphax[4]+7.745966692414834*alphay[3])+19.36491673103708*(alphax[0]*f[3]+f[0]*alphax[3]+alphax[1]*f[2])+f[1]*(19.36491673103708*alphax[2]+7.745966692414834*alphay[1])); 
  out[7] += 0.1*((17.32050807568877*alphay[2]+8.660254037844386*alphax[1])*f[7]+17.32050807568877*alphay[1]*f[6]+(17.32050807568877*alphay[3]+8.660254037844387*alphax[0])*f[5]+17.32050807568877*(f[3]*alphay[5]+alphay[3]*f[4])+7.745966692414834*alphax[3]*f[3]+19.36491673103708*(alphay[0]*f[3]+f[0]*alphay[3])+7.745966692414834*alphax[2]*f[2]+19.36491673103708*(alphay[1]*f[2]+f[1]*alphay[2])); 
  return cflFreq; 
} 
