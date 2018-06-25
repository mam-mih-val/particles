#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CMuon.h"
#include "CElectron.h"
#include "CNeutrino.h"

CMuon::CMuon(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 105.6583745; // MeV
        Int_t q = -1; // e
        Float_t s = 1/2;
        Float_t T = 2.19703*3*pow(10,2); //  nm/c
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CMuon::~CMuon()
{
       	delete particle;
}

TVector3 CMuon::GetP()
{
	return particle->GetP();
}

TLorentzVector CMuon::GetX()
{
	return particle->GetX();
}

Float_t CMuon::GetM()
{
	return particle->GetM();
}

Float_t CMuon::GetE()
{
	return particle->GetE();
}

Int_t CMuon::GetQ()
{
	return particle->GetQ();
}

TVector3 CMuon::GetSpeed()
{
	return particle->GetSpeed();
}

void CMuon::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CMuon::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CMuon::Decay()
{
	list<CParticle*> chldrn;
	TLorentzVector* p12 = new TLorentzVector[2];
	particle->Decay_Phys(0.5109989461, 0, p12);
	CParticle* particle1 = new CElectron(p12[0].Vect(), particle->GetX());
	chldrn.push_back(particle1);
	CParticle* particle2 = new CNeutrino(p12[1].Vect(),particle->GetX());
	chldrn.push_back(particle2);
        return chldrn;
}
