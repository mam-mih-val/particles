class CElectron : public CParticle
{
	CParticle* particle;
private:
        CElectron() { }
public:
        CElectron(TVector3 _P, TLorentzVector _X);
        ~CElectron();
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
