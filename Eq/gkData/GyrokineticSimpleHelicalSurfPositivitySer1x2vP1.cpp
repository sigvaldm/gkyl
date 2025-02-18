#include <GyrokineticModDecl.h> 
double GyrokineticSimpleHelicalSurfPositivity1x2vSer_x_P1_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double dfac_m = 2.0/dxv[2]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wm = w[2]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[8]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = 0.3535533905932737*Gradpar[0]*wv; 

  double alpha[4]; 
  alpha[0] = 1.414213562373095*Gradpar[0]*wv; 
  double rCtrlL[4], rCtrlR[4];  // rCtrl=f1/f0 at each control node in dimensions other than x 
  rCtrlL[0] = (1.414213562373095*(3.0*fl[7]-5.196152422706631*(fl[5]+fl[4])+9.0*fl[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[6]-3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])); 
  rCtrlL[1] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*fl[5]-1.0*(5.196152422706631*fl[4]+9.0*fl[1])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[6])+3.0*(fl[2]-1.0*fl[3])+5.196152422706631*fl[0])); 
  rCtrlL[2] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[4]-1.0*fl[5])-9.0*fl[1]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[6])+3.0*(fl[3]-1.0*fl[2])+5.196152422706631*fl[0])); 
  rCtrlL[3] = (1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[5]+fl[4])+9.0*fl[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[6]+3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])); 
  rCtrlR[0] = (1.414213562373095*(3.0*fr[7]-5.196152422706631*(fr[5]+fr[4])+9.0*fr[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[6]-3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])); 
  rCtrlR[1] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*fr[5]-1.0*(5.196152422706631*fr[4]+9.0*fr[1])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[6])+3.0*(fr[2]-1.0*fr[3])+5.196152422706631*fr[0])); 
  rCtrlR[2] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[4]-1.0*fr[5])-9.0*fr[1]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[6])+3.0*(fr[3]-1.0*fr[2])+5.196152422706631*fr[0])); 
  rCtrlR[3] = (1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[5]+fr[4])+9.0*fr[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[6]+3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])); 
  double fCtrlL[4], fCtrlR[4];  // fCtrl = anti-limited f evaluated at each control node on x surface 
  fCtrlL[0] = 0.06804138174397717*(1.732050807568877*fl[6]-3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])*limTheta(rCtrlL[0],1.0); 
  fCtrlL[1] = -0.06804138174397717*(1.732050807568877*fl[6]+3.0*fl[3]-1.0*(3.0*fl[2]+5.196152422706631*fl[0]))*limTheta(rCtrlL[1],1.0); 
  fCtrlL[2] = -0.06804138174397717*(1.732050807568877*fl[6]+3.0*(fl[2]-1.0*fl[3])-5.196152422706631*fl[0])*limTheta(rCtrlL[2],1.0); 
  fCtrlL[3] = 0.06804138174397717*(1.732050807568877*fl[6]+3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])*limTheta(rCtrlL[3],1.0); 
  fCtrlR[0] = 0.06804138174397717*(1.732050807568877*fr[6]-3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])*limTheta(rCtrlR[0],-1.0); 
  fCtrlR[1] = -0.06804138174397717*(1.732050807568877*fr[6]+3.0*fr[3]-1.0*(3.0*fr[2]+5.196152422706631*fr[0]))*limTheta(rCtrlR[1],-1.0); 
  fCtrlR[2] = -0.06804138174397717*(1.732050807568877*fr[6]+3.0*(fr[2]-1.0*fr[3])-5.196152422706631*fr[0])*limTheta(rCtrlR[2],-1.0); 
  fCtrlR[3] = 0.06804138174397717*(1.732050807568877*fr[6]+3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])*limTheta(rCtrlR[3],-1.0); 
  double fL_AL[4], fR_AL[4];  // f_AL = mode coefficients of anti-limited f on surface 
  fL_AL[0] = 0.5*(fCtrlL[3]+fCtrlL[2]+fCtrlL[1]+fCtrlL[0]); 
  fL_AL[1] = 0.8660254037844386*(fCtrlL[3]-1.0*fCtrlL[2]+fCtrlL[1]-1.0*fCtrlL[0]); 
  fL_AL[2] = 0.8660254037844386*(fCtrlL[3]+fCtrlL[2]-1.0*(fCtrlL[1]+fCtrlL[0])); 
  fL_AL[3] = 1.5*(fCtrlL[3]-1.0*(fCtrlL[2]+fCtrlL[1])+fCtrlL[0]); 
  fR_AL[0] = 0.5*(fCtrlR[3]+fCtrlR[2]+fCtrlR[1]+fCtrlR[0]); 
  fR_AL[1] = 0.8660254037844386*(fCtrlR[3]-1.0*fCtrlR[2]+fCtrlR[1]-1.0*fCtrlR[0]); 
  fR_AL[2] = 0.8660254037844386*(fCtrlR[3]+fCtrlR[2]-1.0*(fCtrlR[1]+fCtrlR[0])); 
  fR_AL[3] = 1.5*(fCtrlR[3]-1.0*(fCtrlR[2]+fCtrlR[1])+fCtrlR[0]); 
  double alphaQuad; 
  // determine upwinding and enforce limiters at each surface quadrature node 
  double fhatALQuad[4], fhatAL[4]; 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fL_AL[2]-1.732050807568877*fL_AL[3]))-1.0*fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fR_AL[2]-1.732050807568877*fR_AL[3]))-1.0*fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[1] = std::max(0., std::min(0.5*((-1.0*(fL_AL[3]+fL_AL[2]))+fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[1] = std::max(0., std::min(0.5*((-1.0*(fR_AL[3]+fR_AL[2]))+fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[2] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fL_AL[2]-1.732050807568877*fL_AL[3])-1.0*fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[2] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fR_AL[2]-1.732050807568877*fR_AL[3])-1.0*fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fL_AL[3]+fL_AL[2])+fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fR_AL[3]+fR_AL[2])+fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  fhatAL[0] = 0.5*(fhatALQuad[3]+fhatALQuad[2]+fhatALQuad[1]+fhatALQuad[0]); 
  fhatAL[1] = 0.5*(fhatALQuad[3]-1.0*fhatALQuad[2]+fhatALQuad[1]-1.0*fhatALQuad[0]); 
  fhatAL[2] = 0.5*(fhatALQuad[3]+fhatALQuad[2]-1.0*(fhatALQuad[1]+fhatALQuad[0])); 
  fhatAL[3] = 0.5*(fhatALQuad[3]-1.0*(fhatALQuad[2]+fhatALQuad[1])+fhatALQuad[0]); 

  // begin surface update 
 
  incr[0] = 0.3535533905932737*alpha[0]*fhatAL[0]*dfac_x; 
  incr[1] = -0.6123724356957944*alpha[0]*fhatAL[0]*dfac_x; 
  incr[2] = 0.3535533905932737*alpha[0]*fhatAL[1]*dfac_x; 
  incr[3] = 0.3535533905932737*alpha[0]*fhatAL[2]*dfac_x; 
  incr[4] = -0.6123724356957944*alpha[0]*fhatAL[1]*dfac_x; 
  incr[5] = -0.6123724356957944*alpha[0]*fhatAL[2]*dfac_x; 
  incr[6] = 0.3535533905932737*alpha[0]*fhatAL[3]*dfac_x; 
  incr[7] = -0.6123724356957944*alpha[0]*fhatAL[3]*dfac_x; 

  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 
  outr[4] += incr[4]; 
  outr[5] += incr[5]; 
  outr[6] += incr[6]; 
  outr[7] += incr[7]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += incr[1]; 
  outl[2] += -1.0*incr[2]; 
  outl[3] += -1.0*incr[3]; 
  outl[4] += incr[4]; 
  outl[5] += incr[5]; 
  outl[6] += -1.0*incr[6]; 
  outl[7] += incr[7]; 
  return std::abs(alpha0); 
} 
double GyrokineticSimpleHelicalSurfPositivity1x2vSer_vpar_P1_Bvars(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double dfac_m = 2.0/dxv[2]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wm = w[2]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[8]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = -(0.4330127018922193*Gradpar[0]*Phi[1]*dfac_x*q_)/m_; 

  double alpha[4]; 
  alpha[0] = -(1.732050807568877*Gradpar[0]*Phi[1]*dfac_x*q_)/m_; 
  double rCtrlL[4], rCtrlR[4];  // rCtrl=f1/f0 at each control node in dimensions other than vx 
  rCtrlL[0] = (1.414213562373095*(3.0*fl[7]-5.196152422706631*(fl[6]+fl[4])+9.0*fl[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[5]-3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])); 
  rCtrlL[1] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*fl[6]-1.0*(5.196152422706631*fl[4]+9.0*fl[2])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[5])+3.0*(fl[1]-1.0*fl[3])+5.196152422706631*fl[0])); 
  rCtrlL[2] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[4]-1.0*fl[6])-9.0*fl[2]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[5])+3.0*(fl[3]-1.0*fl[1])+5.196152422706631*fl[0])); 
  rCtrlL[3] = (1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[6]+fl[4])+9.0*fl[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[5]+3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])); 
  rCtrlR[0] = (1.414213562373095*(3.0*fr[7]-5.196152422706631*(fr[6]+fr[4])+9.0*fr[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[5]-3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])); 
  rCtrlR[1] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*fr[6]-1.0*(5.196152422706631*fr[4]+9.0*fr[2])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[5])+3.0*(fr[1]-1.0*fr[3])+5.196152422706631*fr[0])); 
  rCtrlR[2] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[4]-1.0*fr[6])-9.0*fr[2]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[5])+3.0*(fr[3]-1.0*fr[1])+5.196152422706631*fr[0])); 
  rCtrlR[3] = (1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[6]+fr[4])+9.0*fr[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[5]+3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])); 
  double fCtrlL[4], fCtrlR[4];  // fCtrl = anti-limited f evaluated at each control node on vx surface 
  fCtrlL[0] = 0.06804138174397717*(1.732050807568877*fl[5]-3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])*limTheta(rCtrlL[0],1.0); 
  fCtrlL[1] = -0.06804138174397717*(1.732050807568877*fl[5]+3.0*fl[3]-1.0*(3.0*fl[1]+5.196152422706631*fl[0]))*limTheta(rCtrlL[1],1.0); 
  fCtrlL[2] = -0.06804138174397717*(1.732050807568877*fl[5]+3.0*(fl[1]-1.0*fl[3])-5.196152422706631*fl[0])*limTheta(rCtrlL[2],1.0); 
  fCtrlL[3] = 0.06804138174397717*(1.732050807568877*fl[5]+3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])*limTheta(rCtrlL[3],1.0); 
  fCtrlR[0] = 0.06804138174397717*(1.732050807568877*fr[5]-3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])*limTheta(rCtrlR[0],-1.0); 
  fCtrlR[1] = -0.06804138174397717*(1.732050807568877*fr[5]+3.0*fr[3]-1.0*(3.0*fr[1]+5.196152422706631*fr[0]))*limTheta(rCtrlR[1],-1.0); 
  fCtrlR[2] = -0.06804138174397717*(1.732050807568877*fr[5]+3.0*(fr[1]-1.0*fr[3])-5.196152422706631*fr[0])*limTheta(rCtrlR[2],-1.0); 
  fCtrlR[3] = 0.06804138174397717*(1.732050807568877*fr[5]+3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])*limTheta(rCtrlR[3],-1.0); 
  double fL_AL[4], fR_AL[4];  // f_AL = mode coefficients of anti-limited f on surface 
  fL_AL[0] = 0.5*(fCtrlL[3]+fCtrlL[2]+fCtrlL[1]+fCtrlL[0]); 
  fL_AL[1] = 0.8660254037844386*(fCtrlL[3]-1.0*fCtrlL[2]+fCtrlL[1]-1.0*fCtrlL[0]); 
  fL_AL[2] = 0.8660254037844386*(fCtrlL[3]+fCtrlL[2]-1.0*(fCtrlL[1]+fCtrlL[0])); 
  fL_AL[3] = 1.5*(fCtrlL[3]-1.0*(fCtrlL[2]+fCtrlL[1])+fCtrlL[0]); 
  fR_AL[0] = 0.5*(fCtrlR[3]+fCtrlR[2]+fCtrlR[1]+fCtrlR[0]); 
  fR_AL[1] = 0.8660254037844386*(fCtrlR[3]-1.0*fCtrlR[2]+fCtrlR[1]-1.0*fCtrlR[0]); 
  fR_AL[2] = 0.8660254037844386*(fCtrlR[3]+fCtrlR[2]-1.0*(fCtrlR[1]+fCtrlR[0])); 
  fR_AL[3] = 1.5*(fCtrlR[3]-1.0*(fCtrlR[2]+fCtrlR[1])+fCtrlR[0]); 
  double alphaQuad; 
  // determine upwinding and enforce limiters at each surface quadrature node 
  double fhatALQuad[4], fhatAL[4]; 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fL_AL[1]-1.732050807568877*fL_AL[3]))-1.0*fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fR_AL[1]-1.732050807568877*fR_AL[3]))-1.0*fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[1] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fL_AL[1]-1.732050807568877*fL_AL[3])-1.0*fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[1] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fR_AL[1]-1.732050807568877*fR_AL[3])-1.0*fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[2] = std::max(0., std::min(0.5*((-1.0*(fL_AL[3]+fL_AL[1]))+fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[2] = std::max(0., std::min(0.5*((-1.0*(fR_AL[3]+fR_AL[1]))+fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fL_AL[3]+fL_AL[1])+fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fR_AL[3]+fR_AL[1])+fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  fhatAL[0] = 0.5*(fhatALQuad[3]+fhatALQuad[2]+fhatALQuad[1]+fhatALQuad[0]); 
  fhatAL[1] = 0.5*(fhatALQuad[3]-1.0*fhatALQuad[2]+fhatALQuad[1]-1.0*fhatALQuad[0]); 
  fhatAL[2] = 0.5*(fhatALQuad[3]+fhatALQuad[2]-1.0*(fhatALQuad[1]+fhatALQuad[0])); 
  fhatAL[3] = 0.5*(fhatALQuad[3]-1.0*(fhatALQuad[2]+fhatALQuad[1])+fhatALQuad[0]); 

  // begin surface update 
 
  incr[0] = 0.3535533905932737*alpha[0]*fhatAL[0]*dfac_v; 
  incr[1] = 0.3535533905932737*alpha[0]*fhatAL[1]*dfac_v; 
  incr[2] = -0.6123724356957944*alpha[0]*fhatAL[0]*dfac_v; 
  incr[3] = 0.3535533905932737*alpha[0]*fhatAL[2]*dfac_v; 
  incr[4] = -0.6123724356957944*alpha[0]*fhatAL[1]*dfac_v; 
  incr[5] = 0.3535533905932737*alpha[0]*fhatAL[3]*dfac_v; 
  incr[6] = -0.6123724356957944*alpha[0]*fhatAL[2]*dfac_v; 
  incr[7] = -0.6123724356957944*alpha[0]*fhatAL[3]*dfac_v; 

  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 
  outr[4] += incr[4]; 
  outr[5] += incr[5]; 
  outr[6] += incr[6]; 
  outr[7] += incr[7]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += -1.0*incr[1]; 
  outl[2] += incr[2]; 
  outl[3] += -1.0*incr[3]; 
  outl[4] += incr[4]; 
  outl[5] += -1.0*incr[5]; 
  outl[6] += incr[6]; 
  outl[7] += incr[7]; 
  return std::abs(alpha0); 
} 
double GyrokineticSimpleHelicalSurfPositivity1x2vSer_x_P1_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double dfac_m = 2.0/dxv[2]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wm = w[2]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[8]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = -0.3535533905932737*(1.732050807568877*Gradpar[1]-1.0*Gradpar[0])*wv; 

  double alpha[4]; 
  alpha[0] = (1.414213562373095*Gradpar[0]-2.449489742783178*Gradpar[1])*wv; 
  double rCtrlL[4], rCtrlR[4];  // rCtrl=f1/f0 at each control node in dimensions other than x 
  rCtrlL[0] = (1.414213562373095*(3.0*fl[7]-5.196152422706631*(fl[5]+fl[4])+9.0*fl[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[6]-3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])); 
  rCtrlL[1] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*fl[5]-1.0*(5.196152422706631*fl[4]+9.0*fl[1])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[6])+3.0*(fl[2]-1.0*fl[3])+5.196152422706631*fl[0])); 
  rCtrlL[2] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[4]-1.0*fl[5])-9.0*fl[1]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[6])+3.0*(fl[3]-1.0*fl[2])+5.196152422706631*fl[0])); 
  rCtrlL[3] = (1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[5]+fl[4])+9.0*fl[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[6]+3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])); 
  rCtrlR[0] = (1.414213562373095*(3.0*fr[7]-5.196152422706631*(fr[5]+fr[4])+9.0*fr[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[6]-3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])); 
  rCtrlR[1] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*fr[5]-1.0*(5.196152422706631*fr[4]+9.0*fr[1])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[6])+3.0*(fr[2]-1.0*fr[3])+5.196152422706631*fr[0])); 
  rCtrlR[2] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[4]-1.0*fr[5])-9.0*fr[1]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[6])+3.0*(fr[3]-1.0*fr[2])+5.196152422706631*fr[0])); 
  rCtrlR[3] = (1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[5]+fr[4])+9.0*fr[1]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[6]+3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])); 
  double fCtrlL[4], fCtrlR[4];  // fCtrl = anti-limited f evaluated at each control node on x surface 
  fCtrlL[0] = 0.06804138174397717*(1.732050807568877*fl[6]-3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])*limTheta(rCtrlL[0],1.0); 
  fCtrlL[1] = -0.06804138174397717*(1.732050807568877*fl[6]+3.0*fl[3]-1.0*(3.0*fl[2]+5.196152422706631*fl[0]))*limTheta(rCtrlL[1],1.0); 
  fCtrlL[2] = -0.06804138174397717*(1.732050807568877*fl[6]+3.0*(fl[2]-1.0*fl[3])-5.196152422706631*fl[0])*limTheta(rCtrlL[2],1.0); 
  fCtrlL[3] = 0.06804138174397717*(1.732050807568877*fl[6]+3.0*(fl[3]+fl[2])+5.196152422706631*fl[0])*limTheta(rCtrlL[3],1.0); 
  fCtrlR[0] = 0.06804138174397717*(1.732050807568877*fr[6]-3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])*limTheta(rCtrlR[0],-1.0); 
  fCtrlR[1] = -0.06804138174397717*(1.732050807568877*fr[6]+3.0*fr[3]-1.0*(3.0*fr[2]+5.196152422706631*fr[0]))*limTheta(rCtrlR[1],-1.0); 
  fCtrlR[2] = -0.06804138174397717*(1.732050807568877*fr[6]+3.0*(fr[2]-1.0*fr[3])-5.196152422706631*fr[0])*limTheta(rCtrlR[2],-1.0); 
  fCtrlR[3] = 0.06804138174397717*(1.732050807568877*fr[6]+3.0*(fr[3]+fr[2])+5.196152422706631*fr[0])*limTheta(rCtrlR[3],-1.0); 
  double fL_AL[4], fR_AL[4];  // f_AL = mode coefficients of anti-limited f on surface 
  fL_AL[0] = 0.5*(fCtrlL[3]+fCtrlL[2]+fCtrlL[1]+fCtrlL[0]); 
  fL_AL[1] = 0.8660254037844386*(fCtrlL[3]-1.0*fCtrlL[2]+fCtrlL[1]-1.0*fCtrlL[0]); 
  fL_AL[2] = 0.8660254037844386*(fCtrlL[3]+fCtrlL[2]-1.0*(fCtrlL[1]+fCtrlL[0])); 
  fL_AL[3] = 1.5*(fCtrlL[3]-1.0*(fCtrlL[2]+fCtrlL[1])+fCtrlL[0]); 
  fR_AL[0] = 0.5*(fCtrlR[3]+fCtrlR[2]+fCtrlR[1]+fCtrlR[0]); 
  fR_AL[1] = 0.8660254037844386*(fCtrlR[3]-1.0*fCtrlR[2]+fCtrlR[1]-1.0*fCtrlR[0]); 
  fR_AL[2] = 0.8660254037844386*(fCtrlR[3]+fCtrlR[2]-1.0*(fCtrlR[1]+fCtrlR[0])); 
  fR_AL[3] = 1.5*(fCtrlR[3]-1.0*(fCtrlR[2]+fCtrlR[1])+fCtrlR[0]); 
  double alphaQuad; 
  // determine upwinding and enforce limiters at each surface quadrature node 
  double fhatALQuad[4], fhatAL[4]; 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fL_AL[2]-1.732050807568877*fL_AL[3]))-1.0*fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fR_AL[2]-1.732050807568877*fR_AL[3]))-1.0*fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[1] = std::max(0., std::min(0.5*((-1.0*(fL_AL[3]+fL_AL[2]))+fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[1] = std::max(0., std::min(0.5*((-1.0*(fR_AL[3]+fR_AL[2]))+fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[2] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fL_AL[2]-1.732050807568877*fL_AL[3])-1.0*fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[2] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fR_AL[2]-1.732050807568877*fR_AL[3])-1.0*fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fL_AL[3]+fL_AL[2])+fL_AL[1]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fR_AL[3]+fR_AL[2])+fR_AL[1]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  fhatAL[0] = 0.5*(fhatALQuad[3]+fhatALQuad[2]+fhatALQuad[1]+fhatALQuad[0]); 
  fhatAL[1] = 0.5*(fhatALQuad[3]-1.0*fhatALQuad[2]+fhatALQuad[1]-1.0*fhatALQuad[0]); 
  fhatAL[2] = 0.5*(fhatALQuad[3]+fhatALQuad[2]-1.0*(fhatALQuad[1]+fhatALQuad[0])); 
  fhatAL[3] = 0.5*(fhatALQuad[3]-1.0*(fhatALQuad[2]+fhatALQuad[1])+fhatALQuad[0]); 

  // begin surface update 
 
  incr[0] = 0.3535533905932737*alpha[0]*fhatAL[0]*dfac_x; 
  incr[1] = -0.6123724356957944*alpha[0]*fhatAL[0]*dfac_x; 
  incr[2] = 0.3535533905932737*alpha[0]*fhatAL[1]*dfac_x; 
  incr[3] = 0.3535533905932737*alpha[0]*fhatAL[2]*dfac_x; 
  incr[4] = -0.6123724356957944*alpha[0]*fhatAL[1]*dfac_x; 
  incr[5] = -0.6123724356957944*alpha[0]*fhatAL[2]*dfac_x; 
  incr[6] = 0.3535533905932737*alpha[0]*fhatAL[3]*dfac_x; 
  incr[7] = -0.6123724356957944*alpha[0]*fhatAL[3]*dfac_x; 

  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 
  outr[4] += incr[4]; 
  outr[5] += incr[5]; 
  outr[6] += incr[6]; 
  outr[7] += incr[7]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += incr[1]; 
  outl[2] += -1.0*incr[2]; 
  outl[3] += -1.0*incr[3]; 
  outl[4] += incr[4]; 
  outl[5] += incr[5]; 
  outl[6] += -1.0*incr[6]; 
  outl[7] += incr[7]; 
  return std::abs(alpha0); 
} 
double GyrokineticSurfPositivity1x2vSer_vpar_P1_Bvarsx(const double q_, const double m_, const double cflL, const double cflR, const double *wL, const double *dxvL, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double dfac_m = 2.0/dxv[2]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wm = w[2]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[8]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = -(0.4330127018922193*Gradpar[0]*dfac_x*(Bmag[1]*wm+Phi[1]*q_))/m_; 

  double alpha[4]; 
  alpha[0] = -(1.732050807568877*Gradpar[0]*dfac_x*(Bmag[1]*wm+Phi[1]*q_))/m_; 
  alpha[1] = -(1.732050807568877*Gradpar[1]*dfac_x*(Bmag[1]*wm+Phi[1]*q_))/m_; 
  alpha[2] = -(1.0*Gradpar[0]*Bmag[1]*dfac_x)/(dfac_m*m_); 
  alpha[3] = -(1.0*Bmag[1]*Gradpar[1]*dfac_x)/(dfac_m*m_); 
  double rCtrlL[4], rCtrlR[4];  // rCtrl=f1/f0 at each control node in dimensions other than vx 
  rCtrlL[0] = (1.414213562373095*(3.0*fl[7]-5.196152422706631*(fl[6]+fl[4])+9.0*fl[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[5]-3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])); 
  rCtrlL[1] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*fl[6]-1.0*(5.196152422706631*fl[4]+9.0*fl[2])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[5])+3.0*(fl[1]-1.0*fl[3])+5.196152422706631*fl[0])); 
  rCtrlL[2] = -(1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[4]-1.0*fl[6])-9.0*fl[2]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fl[5])+3.0*(fl[3]-1.0*fl[1])+5.196152422706631*fl[0])); 
  rCtrlL[3] = (1.414213562373095*(3.0*fl[7]+5.196152422706631*(fl[6]+fl[4])+9.0*fl[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fl[5]+3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])); 
  rCtrlR[0] = (1.414213562373095*(3.0*fr[7]-5.196152422706631*(fr[6]+fr[4])+9.0*fr[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[5]-3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])); 
  rCtrlR[1] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*fr[6]-1.0*(5.196152422706631*fr[4]+9.0*fr[2])))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[5])+3.0*(fr[1]-1.0*fr[3])+5.196152422706631*fr[0])); 
  rCtrlR[2] = -(1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[4]-1.0*fr[6])-9.0*fr[2]))/(20.78460969082652*EPSILON+1.414213562373095*((-1.732050807568877*fr[5])+3.0*(fr[3]-1.0*fr[1])+5.196152422706631*fr[0])); 
  rCtrlR[3] = (1.414213562373095*(3.0*fr[7]+5.196152422706631*(fr[6]+fr[4])+9.0*fr[2]))/(20.78460969082652*EPSILON+1.414213562373095*(1.732050807568877*fr[5]+3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])); 
  double fCtrlL[4], fCtrlR[4];  // fCtrl = anti-limited f evaluated at each control node on vx surface 
  fCtrlL[0] = 0.06804138174397717*(1.732050807568877*fl[5]-3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])*limTheta(rCtrlL[0],1.0); 
  fCtrlL[1] = -0.06804138174397717*(1.732050807568877*fl[5]+3.0*fl[3]-1.0*(3.0*fl[1]+5.196152422706631*fl[0]))*limTheta(rCtrlL[1],1.0); 
  fCtrlL[2] = -0.06804138174397717*(1.732050807568877*fl[5]+3.0*(fl[1]-1.0*fl[3])-5.196152422706631*fl[0])*limTheta(rCtrlL[2],1.0); 
  fCtrlL[3] = 0.06804138174397717*(1.732050807568877*fl[5]+3.0*(fl[3]+fl[1])+5.196152422706631*fl[0])*limTheta(rCtrlL[3],1.0); 
  fCtrlR[0] = 0.06804138174397717*(1.732050807568877*fr[5]-3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])*limTheta(rCtrlR[0],-1.0); 
  fCtrlR[1] = -0.06804138174397717*(1.732050807568877*fr[5]+3.0*fr[3]-1.0*(3.0*fr[1]+5.196152422706631*fr[0]))*limTheta(rCtrlR[1],-1.0); 
  fCtrlR[2] = -0.06804138174397717*(1.732050807568877*fr[5]+3.0*(fr[1]-1.0*fr[3])-5.196152422706631*fr[0])*limTheta(rCtrlR[2],-1.0); 
  fCtrlR[3] = 0.06804138174397717*(1.732050807568877*fr[5]+3.0*(fr[3]+fr[1])+5.196152422706631*fr[0])*limTheta(rCtrlR[3],-1.0); 
  double fL_AL[4], fR_AL[4];  // f_AL = mode coefficients of anti-limited f on surface 
  fL_AL[0] = 0.5*(fCtrlL[3]+fCtrlL[2]+fCtrlL[1]+fCtrlL[0]); 
  fL_AL[1] = 0.8660254037844386*(fCtrlL[3]-1.0*fCtrlL[2]+fCtrlL[1]-1.0*fCtrlL[0]); 
  fL_AL[2] = 0.8660254037844386*(fCtrlL[3]+fCtrlL[2]-1.0*(fCtrlL[1]+fCtrlL[0])); 
  fL_AL[3] = 1.5*(fCtrlL[3]-1.0*(fCtrlL[2]+fCtrlL[1])+fCtrlL[0]); 
  fR_AL[0] = 0.5*(fCtrlR[3]+fCtrlR[2]+fCtrlR[1]+fCtrlR[0]); 
  fR_AL[1] = 0.8660254037844386*(fCtrlR[3]-1.0*fCtrlR[2]+fCtrlR[1]-1.0*fCtrlR[0]); 
  fR_AL[2] = 0.8660254037844386*(fCtrlR[3]+fCtrlR[2]-1.0*(fCtrlR[1]+fCtrlR[0])); 
  fR_AL[3] = 1.5*(fCtrlR[3]-1.0*(fCtrlR[2]+fCtrlR[1])+fCtrlR[0]); 
  double alphaQuad; 
  // determine upwinding and enforce limiters at each surface quadrature node 
  double fhatALQuad[4], fhatAL[4]; 
  alphaQuad = 0.5*alpha[3]-0.5*(alpha[2]+alpha[1])+0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fL_AL[1]-1.732050807568877*fL_AL[3]))-1.0*fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[0] = std::max(0., std::min(0.5*((-0.5773502691896258*(1.732050807568877*fR_AL[1]-1.732050807568877*fR_AL[3]))-1.0*fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*(alpha[1]+alpha[0])-0.5*(alpha[3]+alpha[2]); 
  if(alphaQuad > 0) {
  fhatALQuad[1] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fL_AL[1]-1.732050807568877*fL_AL[3])-1.0*fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[1] = std::max(0., std::min(0.5*(0.5773502691896258*(1.732050807568877*fR_AL[1]-1.732050807568877*fR_AL[3])-1.0*fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = (-0.5*alpha[3])+0.5*alpha[2]-0.5*alpha[1]+0.5*alpha[0]; 
  if(alphaQuad > 0) {
  fhatALQuad[2] = std::max(0., std::min(0.5*((-1.0*(fL_AL[3]+fL_AL[1]))+fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[2] = std::max(0., std::min(0.5*((-1.0*(fR_AL[3]+fR_AL[1]))+fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  alphaQuad = 0.5*(alpha[3]+alpha[2]+alpha[1]+alpha[0]); 
  if(alphaQuad > 0) {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fL_AL[3]+fL_AL[1])+fL_AL[2]+fL_AL[0]), fl[0]/cflL*0.3535533905932737)); 
  } else {
  fhatALQuad[3] = std::max(0., std::min(0.5*(1.0*(fR_AL[3]+fR_AL[1])+fR_AL[2]+fR_AL[0]), fr[0]/cflR*0.3535533905932737)); 
  } 
  fhatAL[0] = 0.5*(fhatALQuad[3]+fhatALQuad[2]+fhatALQuad[1]+fhatALQuad[0]); 
  fhatAL[1] = 0.5*(fhatALQuad[3]-1.0*fhatALQuad[2]+fhatALQuad[1]-1.0*fhatALQuad[0]); 
  fhatAL[2] = 0.5*(fhatALQuad[3]+fhatALQuad[2]-1.0*(fhatALQuad[1]+fhatALQuad[0])); 
  fhatAL[3] = 0.5*(fhatALQuad[3]-1.0*(fhatALQuad[2]+fhatALQuad[1])+fhatALQuad[0]); 

  // begin surface update 
 
  incr[0] = 0.3535533905932737*(alpha[3]*fhatAL[3]+alpha[2]*fhatAL[2]+alpha[1]*fhatAL[1]+alpha[0]*fhatAL[0])*dfac_v; 
  incr[1] = 0.3535533905932737*(alpha[2]*fhatAL[3]+fhatAL[2]*alpha[3]+alpha[0]*fhatAL[1]+fhatAL[0]*alpha[1])*dfac_v; 
  incr[2] = -0.6123724356957944*(alpha[3]*fhatAL[3]+alpha[2]*fhatAL[2]+alpha[1]*fhatAL[1]+alpha[0]*fhatAL[0])*dfac_v; 
  incr[3] = 0.3535533905932737*(alpha[1]*fhatAL[3]+fhatAL[1]*alpha[3]+alpha[0]*fhatAL[2]+fhatAL[0]*alpha[2])*dfac_v; 
  incr[4] = -0.6123724356957944*(alpha[2]*fhatAL[3]+fhatAL[2]*alpha[3]+alpha[0]*fhatAL[1]+fhatAL[0]*alpha[1])*dfac_v; 
  incr[5] = 0.3535533905932737*(alpha[0]*fhatAL[3]+fhatAL[0]*alpha[3]+alpha[1]*fhatAL[2]+fhatAL[1]*alpha[2])*dfac_v; 
  incr[6] = -0.6123724356957944*(alpha[1]*fhatAL[3]+fhatAL[1]*alpha[3]+alpha[0]*fhatAL[2]+fhatAL[0]*alpha[2])*dfac_v; 
  incr[7] = -0.6123724356957944*(alpha[0]*fhatAL[3]+fhatAL[0]*alpha[3]+alpha[1]*fhatAL[2]+fhatAL[1]*alpha[2])*dfac_v; 

  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 
  outr[4] += incr[4]; 
  outr[5] += incr[5]; 
  outr[6] += incr[6]; 
  outr[7] += incr[7]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += -1.0*incr[1]; 
  outl[2] += incr[2]; 
  outl[3] += -1.0*incr[3]; 
  outl[4] += incr[4]; 
  outl[5] += -1.0*incr[5]; 
  outl[6] += incr[6]; 
  outl[7] += incr[7]; 
  return std::abs(alpha0); 
} 
