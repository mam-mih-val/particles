#include <list>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "CParticle.h"
#include "CPi_Minus.h"
#include "CMuon.h"
#include "CElectron.h"
#include "CNeutrino.h"

CPi_Minus::CPi_Minus(TVector3 _P, TLorentzVector _X)
{
        Float_t m = 139.57018; // MeV
        Int_t q = -1; // e
        Float_t s = 1;
        Float_t T = 2.6033*3; //  m/c
	particle = new CParticle(m, q, s, T, _X, _P); // Float_t mass, Int_t charge, Float_t spine, Float_t life_time, TLorentzVector X, TVector3 P
}

CPi_Minus::~CPi_Minus()
{
       	delete particle;
}

TVector3 CPi_Minus::GetP()
{
	return particle->GetP();
}

TLorentzVector CPi_Minus::GetX()
{
	return particle->GetX();
}

Float_t CPi_Minus::GetM()
{
	return particle->GetM();
}

Float_t CPi_Minus::GetE()
{
	return particle->GetE();
}

Int_t CPi_Minus::GetQ()
{
	return particle->GetQ();
}

TVector3 CPi_Minus::GetSpeed()
{
	return particle->GetSpeed();
}

void CPi_Minus::TimeEvol(Float_t dt)
{
	particle->TimeEvol(dt);
}

Bool_t CPi_Minus::IsDecay()
{
	return particle->IsDecay();
}

list<CParticle*> CPi_Minus::Decay()
{
	list<CParticle*> chldrn;
	TLorentzVector* p12 = new TLorentzVector[2];
	particle->Decay_Phys(105.6583745, 0, p12);
	CParticle* particle1 = new CMuon(p12[0].Vect(), particle->GetX());
	chldrn.push_back(particle1);
	CParticle* particle2 = new CNeutrino(p12[1].Vect(),particle->GetX());
	chldrn.push_back(particle2);
        return chldrn;
}
