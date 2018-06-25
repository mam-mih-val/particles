#include "CPole.h"
#include <iostream>

int world()
{
	Float_t Rad = 1; // радиус камеры детектора, [m]
	Float_t duration = 6; // [m/c] = 1/3*10^-8 [sec]
	Float_t step = pow(10,-2); // [m/c]
	Double_t trans_const = pow(10,-8)/3; // константа перехода от [nm/c] к [sec]

	TFile f("experiments/mixed.root","recreate");
	TTree t("t","Simple Tree");
	Float_t px,py,pz, E, M, _E; // для записи компонент 4-импульса
	Double_t time = 0, dt = step*trans_const; // Время [sec]
	Double_t max_time = pow(10,-4); // Время [sec]
        Int_t event = 0;

	// Объявление ветвей дерева
        t.Branch("Event",&event,"Event/I");
	t.Branch("time",&time, "time/D");
	t.Branch("M",&M,"M/F");
	t.Branch("E",&E,"E/F");
	t.Branch("px",&px,"px/F");
	t.Branch("py",&py,"py/F");
	t.Branch("pz",&pz,"pz/F");

	CPole pole(1000000.,time); // инициализация поля с заданной энергией и в момент времени time
	// векторы для получения информации и записи в дерево
	TLorentzVector pos;
	TVector3 pos3;
	TVector3 mom;

	for(time=0; time<max_time; time+=dt)
	{
		pole.TimeEvol(step); // временная эволюция поля частиц
		int i=0;
		while(i<pole.Size() ) // проверка состояния поля
		{
			pos = pole[i]->GetX();
			pos3= pos.Vect();
			if (pos3.Mag() > Rad )
			{
                                mom = pole[i]->GetP();
                                px = gRandom->Gaus( mom.X(), 0.00001*mom.X());
                                py = gRandom->Gaus( mom.Y(), 0.00001*mom.X());
                                pz = gRandom->Gaus( mom.Z(), 0.00001*mom.X());
                                M =  pole[i]->GetM();
                                _E =  pole[i]->GetE();
                                E = gRandom->Gaus(_E, 0.00001*_E);
				t.Fill();
				pole.Del(i);
				continue;
			}
			i++;
		}
		Float_t p_rand = gRandom->Uniform(0,1);
                if(p_rand > 0.9990)
                {
                    pole.NewEvent();
                    event++;
                }
	cout << "time progress " << time/max_time*100 << " particles amount "  << pole.Size()  << endl;
	}
	t.Write();
	return 0;
}
