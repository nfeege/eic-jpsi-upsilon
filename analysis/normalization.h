
double get_norm_solid_simulation( TTree* T )
{
  /* get simulation normalization factor */
  Double_t phasespace;
  T->SetBranchAddress("phasespace",&phasespace);
  Int_t neve;
  T->SetBranchAddress("neve",&neve);
  T->GetEntry(T->GetEntries()-1);
  cout << " throw events: " << neve << " , phasespace: " << phasespace << endl;

  Double_t norm_simulation=phasespace/neve;
  cout << "Norm simulation: " << norm_simulation << endl;
  /* end get simulation normalization */

  return norm_simulation;
}

double get_norm_solid_experiment( )
{
  /* get experiment normalizaton */
  //Ebeam
  Double_t cov= 1e-9 * 1e-24; //nb to cm2 coversion
  Double_t br = 5.94/100.;  //Branching ratio: How often does J/Psi decay into e+e-?
  Double_t time = 50*3600*24;  //50 days in seconds
  Double_t eff = 0.85;

  Double_t lumi = 1.2e37;  // 1.2e37/cm2/s is from 3uA on 15cm long LH2 target

  //Gbeam
  //   double lumi_g = 8e35; // 10e-9/1.6e-19*30*0.071*6.02e23  100nA e and 30cm LH2
  Double_t rad = 1.7e-2;    // 15cm LH2, 15/890.4=1.7e-2 radiator

  Double_t norm_experiment;

  string type="e";
  if (type=="e")  {
    norm_experiment = cov * br * eff * time * lumi;
    cout << "Norm experiment: " << norm_experiment << endl;
  }
  /* end get experiment normalization */

  return norm_experiment;

}

double get_norm_solid_overall( TTree* T )
{
  Double_t norm_experiment = get_norm_solid_experiment();

  Double_t norm_simulation = get_norm_solid_simulation(T);

  Double_t overall = norm_experiment*norm_simulation;

  return overall;

}

/** EIC normalization */
double get_norm_eic_overall( TTree* T )
{

  /* get experiment normalizaton */
  //Ebeam
  Double_t cov= 1e-9 * 1e-24; //nb to cm2 coversion (because lumi given in cm^-2s^-1 and cross section in nb)
  Double_t br = 5.94/100.; //Branching ratio: How often does J/Psi decay into e+e-?
  Double_t time = 100*3600*24;  //100 days in seconds
  Double_t eff = 1.0;

  Double_t lumi = 1.0e33;  // for which beam?

  Double_t norm_experiment;

  string type="e";
  if (type=="e")  {
    norm_experiment = cov * br * eff * time * lumi;
    cout << "Norm experiment: " << norm_experiment << endl;
  }
  /* end get experiment normalization */

  Double_t norm_simulation = get_norm_solid_simulation(T);

  /* crossection scaling to match ratio J/psi / Uspilon cross section to existing collider data */
  Double_t xsection_scaling = 0.0143;

  Double_t overall=norm_experiment*norm_simulation*xsection_scaling;

  return overall;
}
