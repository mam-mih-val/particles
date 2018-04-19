#include "CParticles.h"
#include <cstdlib>

CParticle::CParticle(float mass, short int charge, float spine, float life_time, TLorentzVector X, TLorentzVector P)
{
        cout << "Misha Mamaev production" << endl;
        cout <<"All rights are reserved" << endl;
	m = mass;
	q = charge;
	s = spine;
	T = life_time;
	TLorentzVector* p = new TLorentzVector;
	p = P;
	TLorentzVector* x = new TLorentzVector;
	x = X;
}

CParticle::~CParticle()
{
	delete [] p;
	delete [] x;
}

float* CParticle::Decay(float m1, float m2)
{
	p_abs = sqrt( (m1^2 - m^2 - m2^2)^2/(4*m^2) - m1^2) );
	float _alpha = cos(pi*rand() / RAND_MAX);
	float _beta = cos(pi*rand() / RAND_MAX);
	float _gama = sqrt(1 - _alpha^2 - _beta^2);
	float* _p = new float[3];
	*(_p+0) = _alpha*p_abs;
	*(_p+1) = _beta*p_abs;
	*(_p+1) = _gama*p_abs;
	return *_p;
}

float CParticle::GetSpeed()
{
	float u = sqrt( (p[0]^2+p[1]^2+p[2]^2)/(p[3]^2) );
	return u;
}
