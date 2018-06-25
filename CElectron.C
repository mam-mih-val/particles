#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CElectron.h"

CElectron::CElectron(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 0.5109; // MeV
        Int_t q = -1; // e
        Float_t s = 1/2;
        Float_t T = -100; //  stable
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CElectron::~CElectron()
{
       	delete particle;
}

TVector3 CElectron::GetP()
{
	return particle->GetP();
}

TLorentzVector CElectron::GetX()
{
	return particle->GetX();
}

Float_t CElectron::GetM()
{
	return particle->GetM();
}

Float_t CElectron::GetE()
{
	return particle->GetE();
}

Int_t CElectron::GetQ()
{
	return particle->GetQ();
}

TVector3 CElectron::GetSpeed()
{
	return particle->GetSpeed();
}

void CElectron::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CElectron::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CElectron::Decay()
{
	list<CParticle*> chldrn;
	CParticle* particle1 = new CElectron(particle->GetP(), particle->GetX());
	chldrn.push_back(particle1);
        return chldrn;
}
