#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CPhoton.h"

CPhoton::CPhoton(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 0; // MeV
        Int_t q = 0; // e
        Float_t s = 1;
        Float_t T = -100; //  fm
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CPhoton::~CPhoton()
{
       	delete particle;
}

TVector3 CPhoton::GetP()
{
	return particle->GetP();
}

TLorentzVector CPhoton::GetX()
{
	return particle->GetX();
}

Float_t CPhoton::GetM()
{
	return particle->GetM();
}

Float_t CPhoton::GetE()
{
	return particle->GetE();
}

Int_t CPhoton::GetQ()
{
	return particle->GetQ();
}

TVector3 CPhoton::GetSpeed()
{
	return particle->GetSpeed();
}

void CPhoton::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CPhoton::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CPhoton::Decay()
{
	list<CParticle*> chldrn;
	CParticle* particle1 = new CPhoton(particle->GetP(), particle->GetX());
	chldrn.push_back(particle1);
        return chldrn;
}
