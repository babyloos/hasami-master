// hasami_main.h

class Bord {
	char bord[9][9]; 
public:
	Bord();
	void show_bord();
};

Bord::Bord() {
	// ”Õ‚Ì‰Šú‰»
	for(int i=0; i<9; i++) {
		for(int j=0; j<9; j++){
			bord[i][j] = '0';
		}
	}
}

void Bord::show_bord() {
	// :TODO
}



int hasami_main() {
	return 0;
}
