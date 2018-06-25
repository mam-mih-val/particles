#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom.h"
#include "CParticle.h"
#include "CLambda.h"
#include "CPi_Minus.h"
#include "CProton.h"
#include "CPi_Null.h"

CLambda::CLambda(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 1115.683; // MeV
        Int_t q = 0; // e
        Float_t s = 1/2;
        Float_t T = 2.631*3*pow(10,-2); //  m/c
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CLambda::~CLambda()
{
       	delete particle;
}

TVector3 CLambda::GetP()
{
	return particle->GetP();
}

TLorentzVector CLambda::GetX()
{
	return particle->GetX();
}

Float_t CLambda::GetM()
{
	return particle->GetM();
}

Float_t CLambda::GetE()
{
	return particle->GetE();
}

Int_t CLambda::GetQ()
{
	return particle->GetQ();
}

TVector3 CLambda::GetSpeed()
{
	return particle->GetSpeed();
}

void CLambda::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CLambda::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CLambda::Decay()
{
	list<CParticle*> chldrn;
	TLorentzVector* p12 = new TLorentzVector[2];
	Float_t p_dec = gRandom->Uniform(0.,1.);
	if( p_dec>= 0.35)
	{
		particle->Decay_Phys(938.2720813, 139.57018, p12);
		CParticle* particle1 = new CProton(p12[0].Vect(), particle->GetX());
		chldrn.push_back(particle1);
		CParticle* particle2 = new CPi_Minus(p12[1].Vect(),particle->GetX());
		chldrn.push_back(particle2);
	}
	else
	{
		particle->Decay_Phys(134.9766,134.9766, p12);
		CParticle* particle1 = new CPi_Null(p12[0].Vect(), particle->GetX());
		chldrn.push_back(particle1);
		CParticle* particle2 = new CPi_Null(p12[1].Vect(),particle->GetX());
		chldrn.push_back(particle2);
	}
        return chldrn;
}
