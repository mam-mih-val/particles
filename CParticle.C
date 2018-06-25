#include <list>
#include <iostream>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom.h"
#include "CParticle.h"

CParticle::CParticle(Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P)
{

	m = mass;
	q = charge;
	s = spine;
	born_time = X.T();
	p.SetVectM(P,m);
	x = X;
	TVector3 u = this->GetSpeed();
	if( (u.Mag() < 1) && (life_time>0) )
		T = life_time/sqrt( 1-u.Mag2() );
	else
		T = life_time;
}

CParticle::~CParticle() { }

TVector3 CParticle::GetSpeed()
{
	Float_t E = p.E();
	TVector3 p3 = p.Vect();
	TVector3 v3 = p3;
	v3*=1/E;
	return v3;
}

TVector3 CParticle::GetP()
{
	return p.Vect();
}

TLorentzVector CParticle::GetX()
{
	return x;
}

Float_t CParticle::GetM()
{
	return m;
}

Float_t CParticle::GetE()
{
	return p.E();
}

Int_t CParticle::GetQ()
{
	return q;
}

void CParticle::TimeEvol(Float_t dt)
{
        TVector3  v = this->GetSpeed();
        TLorentzVector dx;
        dx.SetVect(v);
        dx.SetT(1.);
        dx*=dt;
        x+=dx;
}

TLorentzVector CParticle::LorentzTransform(TLorentzVector _a4)
{
//    cout << "old " << _a4.Mag() << endl;    
    TVector3 u = this->GetSpeed();
    Double_t gama = 1/sqrt( 1 - u.Mag2() );
    TLorentzVector a;
    Double_t _a0 = _a4.T();
    Double_t a0;
    TVector3 _a3 = _a4.Vect();
    TVector3 a3(0,0,0);
    Float_t u_a3 = u*_a3;
    a0 = gama*(_a0 - (u_a3));
    a3 = -gama*_a0*u + _a3 + (gama-1)/u.Mag2()*u_a3*u;
    a.SetT(a0);
    a.SetVect(a3);
//    cout << "new " << a.Mag() << endl;
    return a;
}

void CParticle::Decay_Phys(Float_t m1, Float_t m2, TLorentzVector *p12)
{
    Double_t p_abs = sqrt( pow( (m1*m1-m*m-m2*m2)/(2*m),2 ) - m2*m2 );
    TVector3 _p;
    _p.SetXYZ(1.0,0.,0.);
    Double_t theta, phi;
    theta = gRandom->Uniform(0.,180.);
    phi = gRandom->Uniform(0.,360.);
    _p.SetMag(p_abs);
    _p.SetPhi(phi);
    _p.SetTheta(theta);
    p12[0].SetVectM(_p,m1);
    p12[0] = this->LorentzTransform(p12[0]);
    _p*=-1;
    p12[1].SetVectM(_p,m2);
    p12[1] = this->LorentzTransform(p12[1]);
}

Bool_t CParticle::IsDecay()
{
	if (T<0)
		return 0;
        Double_t cur_time = x.T()-born_time;
        Double_t p_rand = gRandom->Uniform(0,1);
        Double_t p_life = exp(-cur_time/T);
        if(p_rand > p_life)
                return 1;
        else
                return 0;
}

