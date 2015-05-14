//CMPS 335
//mid335.cpp
//Brandon Ware
//
//with tolerance = 0.005
//how many bad values?
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4

typedef enum {
	C = 1,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
	END = B,
	HALF_STEPS_PER_OCTAVE = B 
} note_t;

double freq(note_t note, int octave_delta);


int main(int argc, char *argv[])
{
	note_t note;
	int octave_delta;
	double tolerance;

	if (argc != 3 && argc != 4) {
		cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA> /<TOLERANCE>/" << endl;
		return 0;
	}
	//
	note = (note_t)(toupper(argv[1][0]) - 64);
	switch(toupper(argv[1][0])) {
		case 'A': note = A; break;
		case 'B': note = B; break;
		case 'C': note = C; break;
		case 'D': note = D; break;
		case 'E': note = E; break;
		case 'F': note = F; break;
	}
	//You may call your unit test here...
	fstream fre("freq.txt", ios_base::in);
	double a, storedfreq[107];
	int flag = 1, count = 0;
		while (fre >> a) {
			storedfreq[count] = a;
			count++;
		}

	if (argc == 4) {
		tolerance = atof(argv[3]);
		cout<<"tolerance: " << tolerance << endl;
	}

	char c = (char)toupper(argv[1][0]);
	int b = atoi(argv[2]);
	cout<< c << ", " << b << endl;
	if (c == 'Z' && b == 0) {
		cout<< "freq function unit-test\n\n\n";
	    	cout<< "note octave value       diff\n";
		cout<< "---- ------ -------     ---------\n";
		int cnt = 0;
		int wcnt = 0;
		for (int i = 0; i < 9; i++) {
		    	for (int j = 1; j < 13; j++) {
				switch(j) {
					case 1: note = C;  break;
					case 2: note = Cs; break;
					case 3: note = D;  break;
					case 4: note = Ds; break;
					case 5: note = E;  break;
					case 6: note = F;  break;
					case 7: note = Fs; break;
					case 8: note = G;  break;
					case 9: note = Gs; break;
					case 10: note = A; break;
					case 11: note = As;break;
					case 12: note = B; break;
				}
				octave_delta = i;
				double diff; 
	    			double freeq = freq(note, octave_delta);
				string gorb;
				if (freeq > storedfreq[cnt]) {
					diff = freeq - storedfreq[cnt];
				} else {
					diff = storedfreq[cnt] - freeq;
				}

				if (diff > tolerance) {
					gorb = "<---bad";
					wcnt++;
				} else {
					gorb = "good";
				}
				cout << setw(2) << j << setw(7) << i << setw(10) << setprecision(6)<< 
					freeq << setw(15) << setprecision(6) << diff << setw(7) <<
					gorb <<endl;
				cnt++;
				if (note > END) {
					cout << "Invalid note!" << endl;
					return 1;
				}
			}
		}
		cout << "Bad word count: " << wcnt << endl;
		cout << "unit-test complete" << endl;
	} else {
		octave_delta = atoi(argv[2]);
		cout << HALF_STEPS_PER_OCTAVE << endl;
		cout << freq(note, octave_delta) << endl;
		return 0;
	}
}
//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
	double freq;
	double factor;
	double a;
	int n;
	int octave = octave_delta - F0_octave;

	a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
	n = note - F0_note;
	freq = F0 * pow(a, (double)n);
	factor = pow(2.0, (double)octave);
	freq = freq * factor;
	return freq;
}

