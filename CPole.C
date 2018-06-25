#include <iostream>
#include <list>
#include <iterator>
#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TVector2.h"
#include "TRandom.h"
#include "CParticle.h"
#include "CProton.h"
#include "CElectron.h"
#include "CPhoton.h"
#include "CNeutrino.h"
#include "CMuon.h"
#include "CPi_Minus.h"
#include "CPi_Null.h"
#include "CLambda.h"
#include "CPole.h"

CPole::CPole(Double_t _E, Double_t _time)
{
	E = _E;
	time = _time;
	it = pole.begin();
	this->NewEvent();
}

CPole::~CPole() { }

CParticle* CPole::operator[](Int_t idx)
{
	it = pole.begin();
	advance(it,idx);
	return *it;
}


void CPole::Decay()
{
	for(unsigned int i=0; i< pole.size(); i++)
		if( this->operator[](i)->IsDecay() == 1 )
		{
			list <CParticle*> children = this->operator[](i)->Decay();
			it = pole.erase(it);
			pole.merge(children);
		}
}

void CPole::TimeEvol(Double_t dt)
{
	time+=dt;
	for (unsigned int i=0; i< pole.size(); i++)
	{
		(*this)[i]->TimeEvol(dt);
	}
	CPole::Decay();
	float p_rand = gRandom->Uniform(0,1);
}

void CPole::Born(Float_t e)
{
	TLorentzVector X;
	X.SetXYZT(0,0,0,time);
        TVector3 p;
	CParticle* particle;
	int type = gRandom->Uniform(0,7);
//	type = 0;
	switch (type)
	{
		// лямбда-гиперон
            	case 0:
                        p = this->PGen(e,1115.683);
			particle = new CLambda(p,X);
			pole.push_back(particle);
			break;
		// электрон
		case 1:
                        p = this->PGen(e,0.510998);
			particle = new CElectron(p,X);
			pole.push_back(particle);
			break;
		// протон
		case 2:
                        p = this->PGen(e,938.272);
			particle = new CProton(p,X);
			pole.push_back(particle);
			break;
		// фотон
		case 3:
                        p = this->PGen(e,0);
			particle = new CPhoton(p,X);
			pole.push_back(particle);
			break;
		// нейтрино
		case 4:
                        p = this->PGen(e,0.28*pow(10,-6));
			particle = new CNeutrino(p,X);
			pole.push_back(particle);
			break;
		// мюон
		case 5:
                        p = this->PGen(e,105.658);
			particle = new CMuon(p,X);
			pole.push_back(particle);
			break;
		// пи-минус мезон
		case 6:
                        p = this->PGen(e,139.570);
			particle = new CPi_Minus(p,X);
			pole.push_back(particle);
			break;
		// пи-ноль мезон
		case 7:
                        p = this->PGen(e,134.976);
			particle = new CPi_Null(p,X);
			pole.push_back(particle);
			break;
	}
}

void CPole::Del(Int_t idx)
{
	it = pole.begin();
	advance(it,idx);
	it = pole.erase(it);
}

void CPole::NewEvent()
{
	Int_t amnt = gRandom->Uniform(2,100);
        Float_t midE = E/amnt;
	Float_t Epep;
	for(int i=0;i<amnt;i++)
        {
		do
		{
            		Epep = fabs( gRandom->Gaus( midE,0.01*midE ) );
		} while(Epep<0.5*midE);
	    	this->Born( Epep );
        }
}

TVector3 CPole::PGen(Float_t e, Float_t m)
{
    TVector3 p;
    Float_t phi = gRandom->Uniform(0.,2*3.14159265359);
    Float_t px=0, py=0, pz=0;
    Float_t pT=0;
    Float_t a_rand=gRandom->Uniform(0,1);
    Float_t a;
    do
    {
        pT+=0.001;
        a = 1 - exp(1-pT*2.303);
    } while( a_rand > a );
    pT*=1000;
    px = pT*cos(phi);
    py = pT*sin(phi);
    if( e*e-m*m-pT*pT > 0 )
    	pz = sqrt( e*e - m*m - pT*pT );
    else if( e*e-m*m > 0 )
    {
	px = 0;
	py = 0;
	pz = sqrt( e*e - m*m);
    }
    else
    {
	px = 0;
	pz = 0;
	pz = e;
    }
    p.SetXYZ( px, py, pz );
    return p;
}
