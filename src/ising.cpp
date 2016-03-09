//============================================================================
// Name        : MetodiComp2Ising.cpp
// Author      : Francesco Forcher
// Version     :
// Copyright   : All rights reserved © 2015
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cmath>
#include <cstdlib>     /* srand, rand */
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>

struct atomo {
	//K correlazione dell'atomo col precedente
	double k;
	//S spin, s=+-1
	short s;
};

//Gaussiana con media mu e varianza sigma
double boxmuller(double mu, double sigma) {

	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
		return z1 * sigma + mu;

	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	}
	while ( u1 <= epsilon );

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}

long double magnetization(const std::vector<atomo>& ret) {

	long double mag = 0;
	const unsigned L = ret.size();

	for (unsigned i = 0; i < L; ++i) {
		mag += ret[i].s;
	}

	return mag;
}

long double energy(const std::vector<atomo>& ret) {
	const unsigned L = ret.size();

	// menergy = Meno l'energia potenziale, -V
	// V = - Sum_1^L k_i s_(i-1) s
	// i va da 0 a L-1
	// Condizioni al contorno periodiche
	long double menergy = ret[0].k * ret[L-1].s * ret[0].s;
	for (unsigned i = 1; i < L; ++i) {


		menergy += ret[i].k * ret[i-1].s * ret[i].s;
	}

	// menergy = -V
	return -menergy;
}


int main(int argc, char* argv[]) {
	using namespace std;
	if (argc != 5) {
		cerr << "Inserire 4 argomenti:\n\n"
				"int L: Num atomi nel reticolo\n"
				"float T: Temperatura\n"
				"int seed: seed generatore numeri casuali\n"
				"int Nsweep: numero di sweep di Monte Carlo\n";
		return -1;
	}

	//Numero di atomi nel reticolo
	const long L = atol(argv[1]);
	// Temperatura
	const double T = atof(argv[2]);
	// Seed di rand
	const long seed = atol(argv[3]);
	const long Nsweep = atol(argv[4]);


	//Inizializzo rand con il seed "seed"
	srand(seed);

	// Reticolo di spin con cond periodiche
	std::vector<atomo> ret(L);

	//File per salvare i valori del k_i degli atomi per plottarli e vedere se sono gaussiani
	ofstream ki_reticolo("risultati/ki_reticolo");
	ofstream medie_temporali("risultati/medie_temporali");

	// Riempo il reticolo con i k gaussiani dai vetri di spin, e metto inizialmente tutti gli spin in alto

	/*
	//Test con ising normale, commentare anche e.k = boxmuller(0,1) più sotto
	int i = 0;
	for (auto& e : ret) {
		//if (i < ret.size()/2) e.k = -1; else
			e.k = 1;
		i++;
	}*/


	for (auto& e : ret) {
		e.k = boxmuller(0,1);
		e.s = 1;
		// Cerchio pieno. Cerchio pieno = 1, cerchio vuoto = -1
		//clog << "\u25CF";
		ki_reticolo << e.k << endl;
	}
	clog << endl;

	// Ogni quanto stampare i risultati
	int nprint = L;
	double E = energy(ret);
	double M = magnetization(ret);
	double sumenergy = 0;
	double summagnet = 0;
	long nzeromenon = 0;

	for (int i = 0; i < Nsweep*L; ++i) {
		//TODO Per il debug
		auto ret_old = ret;


		//Spin da girare, numero casuale tra 0 e L-1
		int isel = int(floor(rand()/double(RAND_MAX) * L));
		//cerr << "isel " << isel << endl;

		// 2 perchè da -1 a 1 (o da 1 a -1, il segno dipende anche dal segno di ret[isel]) ci sono 2 numeri...
		double dM = -2.0*ret[isel].s;
		//Condizioni al contorno periodiche, se isel è 0 conta anche l'ultimo spin come collegato al primo

		double dE = 100;
		if (isel == 0) {
			dE = -(ret[0].k * ret[L - 1].s * dM + ret[1].k * dM * ret[1].s);
		}

		else if (isel == L - 1) {
			dE = -(ret[L - 1].k * ret[L - 2].s * dM + ret[0].k * dM * ret[0].s);
		}

		else {
			dE = -(ret[isel].k * ret[isel - 1].s * dM
					+ ret[isel + 1].k * dM * ret[isel + 1].s);
		}


		/*double dE =
				(isel == 0) ?
						-(ret[0].k * ret[L - 1].s * dM  +  ret[1].k * dM * ret[1].s):
						-(ret[isel].k * ret[isel - 1].s * dM + ret[isel+1].k * dM * ret[isel+1].s);*/

		//Test di Metropolis
		if (dE < 0 or exp(-dE/T) > (rand()/double(RAND_MAX)) ) {
			//Flippa lo spin
			ret[isel].s = -ret[isel].s;
		    E += dE;                      // update energy
		    M += dM;                      // update magnetization
		    //cerr << "Cambiato " << isel << endl;
		} else {
			//do nothing
		}

		/*
		//TODO Debug
		cerr << "DeltaE: " << energy(ret) - energy(ret_old) << endl;
		cerr << "dM " << dM << ", "<< "dE " << dE << endl;
		cerr << endl;
		*/



		if (i % nprint == 0) {
			if (i == Nsweep*L - L or L < 191) {
				for (const auto& e : ret) {
					//Cerchio pieno = 1, cerchio vuoto = -1
					if (e.s == 1)
						// Cerchio pieno = \u25CF.
						clog << "\u25CF";
					else if (e.s == -1)
						// Cerchio vuoto = \u25CB.
						clog << "\u25CB";
					else {
						cerr << "ERRORE!! Qualche spin non è +-1!\n";
						return -1;
					}
				}
				clog << endl;
			}

			/*/cout << i/nprint << "	"
			 << E/double(L) << "	"
			 << M/double(L) << endl;*/
			medie_temporali << i / nprint << "	" << E / double(L) << "	"
					<< M / double(L) << endl;
			if (i > Nsweep*L / 3) {
				nzeromenon++;
				sumenergy += E/double(L);
				summagnet += M/double(L);
			}
		}

	}

	for (const auto& e : ret) {
		//Fai in quartili i k, e metti un simbolo adeguato
		//
		if (e.k < -0.68)
			// triangolo in basso vuoto = \u25BD.
			clog << "\u25BD";
		else if (e.k >= -0.68 and e.k < 0)
			// triangolino in basso vuoto = \25BF.
			clog << "\u25BF";
		else if (e.k >= 0 and e.k < 0.68)
			// triangolino in alto pieno = \25B4.
			clog << "\u25B4";
		else if (e.k >= 0.68)
			// triangolo in alto pieno = \25B2.
			clog << "\u25B2";
		else {
			clog << endl;
			cerr << "ERRORE!! Qualche k non funziona??";
			return -1;
		}
	}

	clog << endl << endl;
	clog << "Media temporale E: " << sumenergy/double(nzeromenon) << endl;
	clog << "Media temporale M: " << summagnet/double(nzeromenon) << endl;
	clog << endl;
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
