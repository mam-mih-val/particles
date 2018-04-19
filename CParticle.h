class CParticle
{
float m;
short int q;
float s;
float T;
private:
	CParticle() { };
protected:
	CParticle(float mass, short int charge, float spine, float life_time,TLorentzVector X, TLorentzVector P);
	~CParticle();
	float* Decay(float m1, float m2);
public:
	float GetSpeed();
}
