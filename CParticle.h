class CParticle
{

Float_t m; // MeV
Int_t q; // e
Float_t s;
Double_t T;  //fm
TLorentzVector p; // sqrt(MeV)
TLorentzVector x; //fm
Double_t born_time; //fm

private:
//	CParticle() { }
private:
	CParticle(Float_t mass, Int_t charge, Float_t spine, Float_t life_time,TLorentzVector X, TVector3 P);
//	~CParticle();
public:
	CParticle() { }
	~CParticle();
	virtual TVector3 GetSpeed();
	virtual TVector3 GetP();
	virtual TLorentzVector GetX();
	virtual Float_t GetM();
	virtual Float_t GetE();
	virtual Int_t GetQ();
	virtual void TimeEvol(Float_t dt);
	TLorentzVector LorentzTransform(TLorentzVector _a4);
	void Decay_Phys(Float_t m1, Float_t m2, TLorentzVector *p12);
	virtual Bool_t IsDecay();
	virtual list<CParticle*> Decay() { }
};
