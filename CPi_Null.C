#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CPi_Null.h"
#include "CPhoton.h"

CPi_Null::CPi_Null(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 134.9766; // MeV
        Int_t q = 0; // e
        Float_t s = 1;
        Float_t T = 8.2*3*pow(10,-9); //  m/c
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CPi_Null::~CPi_Null()
{
       	delete particle;
}

TVector3 CPi_Null::GetP()
{
	return particle->GetP();
}

TLorentzVector CPi_Null::GetX()
{
	return particle->GetX();
}

Float_t CPi_Null::GetM()
{
	return particle->GetM();
}

Float_t CPi_Null::GetE()
{
	return particle->GetE();
}

Int_t CPi_Null::GetQ()
{
	return particle->GetQ();
}

TVector3 CPi_Null::GetSpeed()
{
	return particle->GetSpeed();
}

void CPi_Null::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CPi_Null::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CPi_Null::Decay()
{
	list<CParticle*> chldrn;
	TLorentzVector* p12 = new TLorentzVector[2];
	particle->Decay_Phys(0, 0, p12);
	CParticle* particle1 = new CPhoton(p12[0].Vect(), particle->GetX());
	chldrn.push_back(particle1);
	CParticle* particle2 = new CPhoton(p12[1].Vect(),particle->GetX());
	chldrn.push_back(particle2);
        return chldrn;
}
