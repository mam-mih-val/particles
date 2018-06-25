#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CProton.h"

CProton::CProton(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 938.2720813; // MeV
        Int_t q = 1; // e
        Float_t s = 1/2;
        Float_t T = -100; //  fm
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CProton::~CProton()
{
       	delete particle;
}

TVector3 CProton::GetP()
{
	return particle->GetP();
}

TLorentzVector CProton::GetX()
{
	return particle->GetX();
}

Float_t CProton::GetM()
{
	return particle->GetM();
}

Float_t CProton::GetE()
{
	return particle->GetE();
}

Int_t CProton::GetQ()
{
	return particle->GetQ();
}

TVector3 CProton::GetSpeed()
{
	return particle->GetSpeed();
}

void CProton::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CProton::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CProton::Decay()
{
	list<CParticle*> chldrn;
	CParticle* particle1 = new CProton(particle->GetP(), particle->GetX());
	chldrn.push_back(particle1);
        return chldrn;
}
