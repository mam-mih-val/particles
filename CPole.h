class CPole
{
protected:
	CPole() { };
	Double_t E; //MeV
	//Int_t amnt;
	Double_t time;
	list<CParticle*> pole;
	list<CParticle*>::iterator it;
public:
	CPole(Double_t _E, Double_t _time);
	~CPole();
	virtual void TimeEvol(Double_t dt);
	virtual void Born(Float_t e);
	virtual CParticle* operator[](Int_t idx);
	virtual unsigned int Size() { return pole.size(); }
	virtual void Del(Int_t idx);
	virtual void NewEvent();
private:
	virtual void Decay();
        virtual TVector3 PGen(Float_t e, Float_t m);
};
