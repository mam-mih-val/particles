class CPi_Minus : public CParticle
{
        CParticle* particle;
private:
        CPi_Minus() { }
public:
        CPi_Minus(TVector3 _P, TLorentzVector _X);
        ~CPi_Minus();
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

