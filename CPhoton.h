class CPhoton : public CParticle
{
	CParticle* particle;
private:
        CPhoton() { }
public:
        CPhoton(TVector3 _P, TLorentzVector _X);
        ~CPhoton();
        TVector3 GetP();
        TLorentzVector GetX();
        Float_t GetM();
        Float_t GetE();
        Int_t GetQ();
	TVector3 GetSpeed();
	void TimeEvol(Float_t dt);
	Bool_t IsDecay();
	list<CParticle*> Decay();
};
