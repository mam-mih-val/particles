#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CNeutrino.h"

CNeutrino::CNeutrino(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 0; // MeV
        Int_t q = 0; // e
        Float_t s = 1/2;
        Float_t T = -100; //  fm
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CNeutrino::~CNeutrino()
{
       	delete particle;
}

TVector3 CNeutrino::GetP()
{
	return particle->GetP();
}

TLorentzVector CNeutrino::GetX()
{
	return particle->GetX();
}

Float_t CNeutrino::GetM()
{
	return particle->GetM();
}

Float_t CNeutrino::GetE()
{
	return particle->GetE();
}

Int_t CNeutrino::GetQ()
{
	return particle->GetQ();
}

TVector3 CNeutrino::GetSpeed()
{
	return particle->GetSpeed();
}

void CNeutrino::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CNeutrino::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CNeutrino::Decay()
{
	list<CParticle*> chldrn;
	CParticle* particle1 = new CNeutrino(particle->GetP(), particle->GetX());
	chldrn.push_back(particle1);
        return chldrn;
}
