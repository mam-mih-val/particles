class CMuon : public CParticle
{
        CParticle* particle;
private:
        CMuon() { }
public:
        CMuon(TVector3 _P, TLorentzVector _X);
        ~CMuon();
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

