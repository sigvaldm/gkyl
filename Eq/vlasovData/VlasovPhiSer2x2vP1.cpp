#include <VlasovModDecl.h> 

__host__ __device__ double VlasovPhiVol2x2vSerP1(const double *w, const double *dxv, const double qDm, const double *phi, const double *EM, const double *f, double *out) 
{ 
  // w[NDIM]:   Cell-center coordinates.
  // dxv[NDIM]: Cell spacing.
  // qDm:       Species charge (q) divided by its mass (m).
  // phi:       Input phi-field.
  // EM:        Input (external) EM field vectors.
  // f:         Input distribution function.
  // out:       Incremented output.
  const double dv0dx0 = dxv[2]/dxv[0]; 
  const double w0dx0 = w[2]/dxv[0]; 
  const double dv1dx1 = dxv[3]/dxv[1]; 
  const double w1dx1 = w[3]/dxv[1]; 
  const double rdx2qDm = 2.*qDm/dxv[0]; 
  const double rdy2qDm = 2.*qDm/dxv[1]; 
  const double dv10 = 2./dxv[2]; 
  const double dv1 = dxv[2], wv1 = w[2]; 
  const double dv11 = 2./dxv[3]; 
  const double dv2 = dxv[3], wv2 = w[3]; 

  const double *E0 = &EM[0]; 
  const double *E1 = &EM[4]; 

  double alpha_mid = 0.0; 
  double alpha_cdim[32]; 
  double alpha_vdim[32]; 

  alpha_cdim[0] = 8.0*w0dx0; 
  alpha_cdim[3] = 2.309401076758503*dv0dx0; 
  alpha_mid += std::abs(w0dx0)+0.5*dv0dx0; 

  alpha_cdim[16] = 8.0*w1dx1; 
  alpha_cdim[20] = 2.309401076758503*dv1dx1; 
  alpha_mid += std::abs(w1dx1)+0.5*dv1dx1; 

  alpha_vdim[0] = dv10*(2.0*E0[0]-3.464101615137754*phi[1]*rdx2qDm); 
  alpha_vdim[1] = 2.0*E0[1]*dv10; 
  alpha_vdim[2] = dv10*(2.0*E0[2]-3.464101615137754*phi[3]*rdx2qDm); 
  alpha_vdim[5] = 2.0*E0[3]*dv10; 
  alpha_mid += std::abs(0.125*alpha_vdim[0]); 

  alpha_vdim[16] = dv11*(2.0*E1[0]-3.464101615137754*phi[2]*rdy2qDm); 
  alpha_vdim[17] = dv11*(2.0*E1[1]-3.464101615137754*phi[3]*rdy2qDm); 
  alpha_vdim[18] = 2.0*E1[2]*dv11; 
  alpha_vdim[21] = 2.0*E1[3]*dv11; 
  alpha_mid += std::abs(0.125*alpha_vdim[16]); 

  out[1] += 0.4330127018922193*(alpha_cdim[3]*f[3]+alpha_cdim[0]*f[0]); 
  out[2] += 0.4330127018922193*(f[4]*alpha_cdim[20]+f[0]*alpha_cdim[16]); 
  out[3] += 0.4330127018922193*(alpha_vdim[5]*f[5]+alpha_vdim[2]*f[2]+alpha_vdim[1]*f[1]+alpha_vdim[0]*f[0]); 
  out[4] += 0.4330127018922193*(f[5]*alpha_vdim[21]+f[2]*alpha_vdim[18]+f[1]*alpha_vdim[17]+f[0]*alpha_vdim[16]); 
  out[5] += 0.4330127018922193*(f[8]*alpha_cdim[20]+f[1]*alpha_cdim[16]+alpha_cdim[3]*f[7]+alpha_cdim[0]*f[2]); 
  out[6] += 0.4330127018922193*(alpha_vdim[2]*f[5]+f[2]*alpha_vdim[5]+alpha_cdim[0]*f[3]+f[0]*alpha_cdim[3]+alpha_vdim[0]*f[1]+f[0]*alpha_vdim[1]); 
  out[7] += 0.4330127018922193*(f[10]*alpha_cdim[20]+f[3]*alpha_cdim[16]+alpha_vdim[1]*f[5]+f[1]*alpha_vdim[5]+alpha_vdim[0]*f[2]+f[0]*alpha_vdim[2]); 
  out[8] += 0.4330127018922193*(f[2]*alpha_vdim[21]+f[5]*alpha_vdim[18]+f[0]*alpha_vdim[17]+f[1]*alpha_vdim[16]+alpha_cdim[3]*f[10]+alpha_cdim[0]*f[4]); 
  out[9] += 0.4330127018922193*(f[1]*alpha_vdim[21]+f[0]*(alpha_cdim[20]+alpha_vdim[18])+f[5]*alpha_vdim[17]+f[2]*alpha_vdim[16]+f[4]*alpha_cdim[16]); 
  out[10] += 0.4330127018922193*(f[11]*alpha_vdim[21]+f[7]*alpha_vdim[18]+f[6]*alpha_vdim[17]+f[3]*alpha_vdim[16]+alpha_vdim[5]*f[12]+alpha_vdim[2]*f[9]+alpha_vdim[1]*f[8]+alpha_vdim[0]*f[4]); 
  out[11] += 0.4330127018922193*(f[13]*alpha_cdim[20]+f[6]*alpha_cdim[16]+alpha_cdim[0]*f[7]+alpha_vdim[0]*f[5]+f[0]*alpha_vdim[5]+f[2]*(alpha_cdim[3]+alpha_vdim[1])+f[1]*alpha_vdim[2]); 
  out[12] += 0.4330127018922193*(f[0]*alpha_vdim[21]+f[1]*(alpha_cdim[20]+alpha_vdim[18])+f[2]*alpha_vdim[17]+f[5]*alpha_vdim[16]+f[8]*alpha_cdim[16]+alpha_cdim[3]*f[14]+alpha_cdim[0]*f[9]); 
  out[13] += 0.4330127018922193*(f[7]*alpha_vdim[21]+f[11]*alpha_vdim[18]+f[3]*alpha_vdim[17]+f[6]*alpha_vdim[16]+alpha_vdim[2]*f[12]+alpha_cdim[0]*f[10]+alpha_vdim[5]*f[9]+alpha_vdim[0]*f[8]+(alpha_cdim[3]+alpha_vdim[1])*f[4]); 
  out[14] += 0.4330127018922193*(f[6]*alpha_vdim[21]+f[3]*(alpha_cdim[20]+alpha_vdim[18])+f[11]*alpha_vdim[17]+f[7]*alpha_vdim[16]+f[10]*alpha_cdim[16]+alpha_vdim[1]*f[12]+alpha_vdim[0]*f[9]+alpha_vdim[5]*f[8]+alpha_vdim[2]*f[4]); 
  out[15] += 0.4330127018922193*(f[3]*alpha_vdim[21]+f[6]*(alpha_cdim[20]+alpha_vdim[18])+f[7]*alpha_vdim[17]+f[11]*alpha_vdim[16]+f[13]*alpha_cdim[16]+alpha_cdim[0]*f[14]+alpha_vdim[0]*f[12]+(alpha_cdim[3]+alpha_vdim[1])*f[9]+alpha_vdim[2]*f[8]+f[4]*alpha_vdim[5]); 

  return alpha_mid; 
} 

__host__ __device__ double VlasovPhiBextVol2x2vSerP1(const double *w, const double *dxv, const double qDm, const double *phi, const double *EM, const double *f, double *out) 
{ 
  // w[NDIM]:   Cell-center coordinates.
  // dxv[NDIM]: Cell spacing.
  // qDm:       Species charge (q) divided by its mass (m).
  // phi:       Input phi-field.
  // EM:        Input (external) EM field vectors.
  // f:         Input distribution function.
  // out:       Incremented output.
  const double dv0dx0 = dxv[2]/dxv[0]; 
  const double w0dx0 = w[2]/dxv[0]; 
  const double dv1dx1 = dxv[3]/dxv[1]; 
  const double w1dx1 = w[3]/dxv[1]; 
  const double rdx2qDm = 2.*qDm/dxv[0]; 
  const double rdy2qDm = 2.*qDm/dxv[1]; 
  const double dv10 = 2./dxv[2]; 
  const double dv1 = dxv[2], wv1 = w[2]; 
  const double dv11 = 2./dxv[3]; 
  const double dv2 = dxv[3], wv2 = w[3]; 

  const double *E0 = &EM[0]; 
  const double *E1 = &EM[4]; 
  const double *B2 = &EM[20]; 

  double alpha_mid = 0.0; 
  double alpha_cdim[32]; 
  double alpha_vdim[32]; 

  alpha_cdim[0] = 8.0*w0dx0; 
  alpha_cdim[3] = 2.309401076758503*dv0dx0; 
  alpha_mid += std::abs(w0dx0)+0.5*dv0dx0; 

  alpha_cdim[16] = 8.0*w1dx1; 
  alpha_cdim[20] = 2.309401076758503*dv1dx1; 
  alpha_mid += std::abs(w1dx1)+0.5*dv1dx1; 

  alpha_vdim[0] = dv10*(2.0*B2[0]*wv2-3.464101615137754*phi[1]*rdx2qDm+2.0*E0[0]); 
  alpha_vdim[1] = 2.0*dv10*(B2[1]*wv2+E0[1]); 
  alpha_vdim[2] = dv10*(2.0*B2[2]*wv2-3.464101615137754*phi[3]*rdx2qDm+2.0*E0[2]); 
  alpha_vdim[4] = 0.5773502691896258*B2[0]*dv10*dv2; 
  alpha_vdim[5] = 2.0*dv10*(B2[3]*wv2+E0[3]); 
  alpha_vdim[8] = 0.5773502691896258*B2[1]*dv10*dv2; 
  alpha_vdim[9] = 0.5773502691896258*B2[2]*dv10*dv2; 
  alpha_vdim[12] = 0.5773502691896258*B2[3]*dv10*dv2; 
  alpha_mid += std::abs(0.125*alpha_vdim[0]); 

  alpha_vdim[16] = dv11*((-2.0*B2[0]*wv1)-3.464101615137754*phi[2]*rdy2qDm+2.0*E1[0]); 
  alpha_vdim[17] = dv11*((-2.0*B2[1]*wv1)-3.464101615137754*phi[3]*rdy2qDm+2.0*E1[1]); 
  alpha_vdim[18] = dv11*(2.0*E1[2]-2.0*B2[2]*wv1); 
  alpha_vdim[19] = -0.5773502691896258*B2[0]*dv1*dv11; 
  alpha_vdim[21] = dv11*(2.0*E1[3]-2.0*B2[3]*wv1); 
  alpha_vdim[22] = -0.5773502691896258*B2[1]*dv1*dv11; 
  alpha_vdim[23] = -0.5773502691896258*B2[2]*dv1*dv11; 
  alpha_vdim[27] = -0.5773502691896258*B2[3]*dv1*dv11; 
  alpha_mid += std::abs(0.125*alpha_vdim[16]); 

  out[1] += 0.4330127018922193*(alpha_cdim[3]*f[3]+alpha_cdim[0]*f[0]); 
  out[2] += 0.4330127018922193*(f[4]*alpha_cdim[20]+f[0]*alpha_cdim[16]); 
  out[3] += 0.4330127018922193*(alpha_vdim[12]*f[12]+alpha_vdim[9]*f[9]+alpha_vdim[8]*f[8]+alpha_vdim[5]*f[5]+alpha_vdim[4]*f[4]+alpha_vdim[2]*f[2]+alpha_vdim[1]*f[1]+alpha_vdim[0]*f[0]); 
  out[4] += 0.4330127018922193*(f[11]*alpha_vdim[27]+f[7]*alpha_vdim[23]+f[6]*alpha_vdim[22]+f[5]*alpha_vdim[21]+f[3]*alpha_vdim[19]+f[2]*alpha_vdim[18]+f[1]*alpha_vdim[17]+f[0]*alpha_vdim[16]); 
  out[5] += 0.4330127018922193*(f[8]*alpha_cdim[20]+f[1]*alpha_cdim[16]+alpha_cdim[3]*f[7]+alpha_cdim[0]*f[2]); 
  out[6] += 0.4330127018922193*(alpha_vdim[9]*f[12]+f[9]*alpha_vdim[12]+alpha_vdim[4]*f[8]+f[4]*alpha_vdim[8]+alpha_vdim[2]*f[5]+f[2]*alpha_vdim[5]+alpha_cdim[0]*f[3]+f[0]*alpha_cdim[3]+alpha_vdim[0]*f[1]+f[0]*alpha_vdim[1]); 
  out[7] += 0.4330127018922193*(f[10]*alpha_cdim[20]+f[3]*alpha_cdim[16]+alpha_vdim[8]*f[12]+f[8]*alpha_vdim[12]+alpha_vdim[4]*f[9]+f[4]*alpha_vdim[9]+alpha_vdim[1]*f[5]+f[1]*alpha_vdim[5]+alpha_vdim[0]*f[2]+f[0]*alpha_vdim[2]); 
  out[8] += 0.4330127018922193*(f[7]*alpha_vdim[27]+f[11]*alpha_vdim[23]+f[3]*alpha_vdim[22]+f[2]*alpha_vdim[21]+f[6]*alpha_vdim[19]+f[5]*alpha_vdim[18]+f[0]*alpha_vdim[17]+f[1]*alpha_vdim[16]+alpha_cdim[3]*f[10]+alpha_cdim[0]*f[4]); 
  out[9] += 0.4330127018922193*(f[6]*alpha_vdim[27]+f[3]*alpha_vdim[23]+f[11]*alpha_vdim[22]+f[1]*alpha_vdim[21]+f[0]*alpha_cdim[20]+f[7]*alpha_vdim[19]+f[0]*alpha_vdim[18]+f[5]*alpha_vdim[17]+f[2]*alpha_vdim[16]+f[4]*alpha_cdim[16]); 
  out[10] += 0.4330127018922193*(f[5]*alpha_vdim[27]+f[2]*alpha_vdim[23]+f[1]*alpha_vdim[22]+f[11]*alpha_vdim[21]+f[0]*alpha_vdim[19]+f[7]*alpha_vdim[18]+f[6]*alpha_vdim[17]+f[3]*alpha_vdim[16]+alpha_vdim[5]*f[12]+f[5]*alpha_vdim[12]+alpha_vdim[2]*f[9]+f[2]*alpha_vdim[9]+alpha_vdim[1]*f[8]+f[1]*alpha_vdim[8]+alpha_vdim[0]*f[4]+f[0]*alpha_vdim[4]); 
  out[11] += 0.4330127018922193*(f[13]*alpha_cdim[20]+f[6]*alpha_cdim[16]+alpha_vdim[4]*f[12]+f[4]*alpha_vdim[12]+alpha_vdim[8]*f[9]+f[8]*alpha_vdim[9]+alpha_cdim[0]*f[7]+alpha_vdim[0]*f[5]+f[0]*alpha_vdim[5]+f[2]*(alpha_cdim[3]+alpha_vdim[1])+f[1]*alpha_vdim[2]); 
  out[12] += 0.4330127018922193*(f[3]*alpha_vdim[27]+f[6]*alpha_vdim[23]+f[7]*alpha_vdim[22]+f[0]*alpha_vdim[21]+f[1]*alpha_cdim[20]+f[11]*alpha_vdim[19]+f[1]*alpha_vdim[18]+f[2]*alpha_vdim[17]+f[5]*alpha_vdim[16]+f[8]*alpha_cdim[16]+alpha_cdim[3]*f[14]+alpha_cdim[0]*f[9]); 
  out[13] += 0.4330127018922193*(f[2]*alpha_vdim[27]+f[5]*alpha_vdim[23]+f[0]*alpha_vdim[22]+f[7]*alpha_vdim[21]+f[1]*alpha_vdim[19]+f[11]*alpha_vdim[18]+f[3]*alpha_vdim[17]+f[6]*alpha_vdim[16]+alpha_vdim[2]*f[12]+f[2]*alpha_vdim[12]+alpha_cdim[0]*f[10]+alpha_vdim[5]*f[9]+f[5]*alpha_vdim[9]+alpha_vdim[0]*f[8]+f[0]*alpha_vdim[8]+(alpha_cdim[3]+alpha_vdim[1])*f[4]+f[1]*alpha_vdim[4]); 
  out[14] += 0.4330127018922193*(f[1]*alpha_vdim[27]+f[0]*alpha_vdim[23]+f[5]*alpha_vdim[22]+f[6]*alpha_vdim[21]+f[3]*alpha_cdim[20]+f[2]*alpha_vdim[19]+f[3]*alpha_vdim[18]+f[11]*alpha_vdim[17]+f[7]*alpha_vdim[16]+f[10]*alpha_cdim[16]+alpha_vdim[1]*f[12]+f[1]*alpha_vdim[12]+alpha_vdim[0]*f[9]+f[0]*alpha_vdim[9]+alpha_vdim[5]*f[8]+f[5]*alpha_vdim[8]+alpha_vdim[2]*f[4]+f[2]*alpha_vdim[4]); 
  out[15] += 0.4330127018922193*(f[0]*alpha_vdim[27]+f[1]*alpha_vdim[23]+f[2]*alpha_vdim[22]+f[3]*alpha_vdim[21]+f[6]*alpha_cdim[20]+f[5]*alpha_vdim[19]+f[6]*alpha_vdim[18]+f[7]*alpha_vdim[17]+f[11]*alpha_vdim[16]+f[13]*alpha_cdim[16]+alpha_cdim[0]*f[14]+alpha_vdim[0]*f[12]+f[0]*alpha_vdim[12]+(alpha_cdim[3]+alpha_vdim[1])*f[9]+f[1]*alpha_vdim[9]+alpha_vdim[2]*f[8]+f[2]*alpha_vdim[8]+alpha_vdim[4]*f[5]+f[4]*alpha_vdim[5]); 

  return alpha_mid; 
} 

