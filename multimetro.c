//Realizzazione dell'istogramma normalizzato su cui viene tracciata la relativa curva di Gauss
void multimetro()
{
	//Costruzione istogramma
	int nbins = 7;
	float xmin = 807.5;
	float xmax = 814.5;
				
	TH1F *h = new TH1F("h","", nbins, xmin, xmax);
	
	//Lettura da un file
	const char *myFile = "multimetro.txt";
	fstream file (myFile, ios::in);
	if (file.is_open()){
		int x[50]; //array contenente i dati 
		for(int i=0; i<50; i++){
			file >> x[i];
			h->Fill(x[i]); //riempimento istogramma
		}
	}
	file.close();	
	
	//Caratteristiche istogramma
	//h->SetStats(0);
	
 	//Normalizzazione dell'istogramma 
     	h->Scale(1/h->Integral(), "width");
	
	//Estetica dell'istogramma
	h->SetFillColor(38);
	h->GetXaxis()->SetTitle("Resistenza (#Omega)");
	h->GetYaxis()->SetTitle("Frequenza normale");
	h->GetXaxis()->CenterTitle(true);	
	h->GetYaxis()->CenterTitle(true);
	h->GetXaxis()->SetRangeUser(806,815);
	
	//Rappresentazione istogramma
	TCanvas *c1 = new TCanvas("c1","Istogramma normalizzato",800,600);
	h->Draw("histo");
	 
	//Fit gaussiano
	TF1 *ffit = new TF1("ffit","gaus",xmin-1,xmax+1);
	h->Fit(ffit);
	ffit->Draw("same");
	
}
