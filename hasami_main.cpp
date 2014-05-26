// Q[?C[v
// hasami_main.cpp

#include <stdio.h>
#include "func.h"
#include <stdlib.h>

// 1���̋�A2���̋�A�O��̃}�X
#define aki 0
#define sente 1 //���
#define gote 2//���
class Bord {
	char bord[9][9]; // ??1???2 0
	int turn;		// �^�[���ϐ��@���P�@���Q
	int countsente;	//����̎擾����
	int countgote;	//����̎擾����
	int sosaroop;		//�{���ł̕ϐ�
public:
	Bord();
	void show_bord();
	int move(int movefrom, int moveto);
	int sosa(int x, int y, int turn);
	int show_turn();
	void turnChange();

};


Bord::Bord() {
	// �Ղ̏�����
	for(int i=0; i<9; i++) {
		for(int j=0; j<9; j++) {
			bord[i][j] = aki;
		}
	}
	for(int i=0; i<9; i++) {
		bord[0][i] = gote;
	}
	for(int i=0; i<9; i++) {
		bord[8][i] = sente;
	}

	turn = 1;		// �^�[��������
	countsente=0;	//���̋�̎擾����������
	countgote=0;	//���̋�̎擾����������
}

// �Ղ̕\��
void Bord::show_bord() {
	printf(" 0  1  2  3  4  5  6  7  8\n");
	for(int i=0; i<9; i++) {
		printf(" �Q �Q �Q �Q �Q �Q �Q �Q �Q \n");	
		for(int j=0; j<9; j++) {
			printf("|");
			if(bord[i][j] == sente) printf("��");
			else if(bord[i][j] == gote) printf("��");
			else printf("�@");
			
		}
		printf("|");
		printf("\n �[ �[ �[ �[ �[ �[ �[ �[ �[ %d\n", i);
	}

}

int Bord::move(int movefrom, int moveto) {//�ق��̋�������Ƃ��ɋ���щz���邱�Ƃ͂ł��Ȃ��������Ȃ�
	// char thisTurn;
	/*
if (turn == 1) thisTurn = 1;
	else if (turn == 2) thisTurn = 2;
	
	else {
		printf("�G���[���������܂����BBord.move()\n");
	}
	 */

	int fromx = movefrom / 10;
	int fromy = movefrom % 10;

	int movetox = moveto / 10;
	int movetoy = moveto % 10;

	if((fromx!=movetox)&(fromy!=movetoy)) return -1;	// �}�X�͏c���ɂ����ړ��ł��Ȃ�
	if((bord[fromy][fromx]==turn)&(bord[movetoy][movetox] == aki)){   // �����̋�ňړ��悪��̏ꍇ�����ړ�����������
			bord[movetoy][movetox] = bord[fromy][fromx];
			bord[fromy][fromx] = aki;
	}else {
		return -1;
	}
	sosaroop=1;
	sosa(movetox-1, movetoy,turn); //���{����
	sosaroop=2;
	sosa(movetox+1, movetoy,turn); //�E�{����
	sosaroop=3;
	sosa(movetox, movetoy+1,turn); //��{����
	sosaroop=4;
	sosa(movetox, movetoy-1,turn); //���{����
	sosaroop=0;
	return 0;
}

// �㉺���E�ɑ��삵�Ă���
int Bord::sosa(int x, int y, int turn) {
	int ret;
	int teki = abs(turn - 3);
	// �����̋����������A�P��Ԃ��ďI������B
	if(bord[y][x] == turn) {
		return 1;

	// �G�̋����������A���W��1���炵�āAsosa���Ăяo���B
	}else if(bord[y][x] == teki) {
		
		if(sosaroop==1)ret = sosa(x-1, y, turn);
		else if(sosaroop==2)ret = sosa(x+1, y, turn);
		else if(sosaroop==3)ret = sosa(x, y+1, turn);
		else if(sosaroop==4)ret = sosa(x, y-1, turn);
		// �P���A���Ă����獡�̍��W�������̋�ɒu��������
		if(ret == 1){
		 bord[y][x] = 0;
		 if(turn==sente){countsente+=1;
		 				printf("\n���̋�擾��%d��\n",countsente);}
		 else if(turn==gote){countgote+=1;
						printf("\n���̋�擾��%d��\n",countgote);}
		}
		return ret;

	// ��̍��W�������邩�A�Ղ̊O�ɏo�Ă��܂�����-1��Ԃ��ďI������B
	}else if((bord[y][x] == 0)||(x<0||x>8||y<0||y>8)) {
		return -1; 

	}

	return -2;
	
}


int Bord::show_turn() {
	return turn;
}

void Bord::turnChange(){
turn=abs(turn - 3);
}
	
int main() {
	Bord mainBord;		// ??
	printf("�ŐV�̃t�@�C���ł��B\n");
	// ?
	int movefrom, moveto;
	int movetox;
	int movetoy;


	while(1) {
		while(1) {
			mainBord.show_bord();
			if(mainBord.show_turn() == sente ) printf("���̔Ԃł��B��̈ړ��i�ړ����̋�̍��W�A�ړ���̋�̍��W�jturn:%d :", mainBord.show_turn());
			else if(mainBord.show_turn()== gote) printf("���̔Ԃł��B��̈ړ��i�ړ����̋�̍��W�A�ړ���̋�̍��W�jturn%d:",mainBord.show_turn());
			else { 
				printf("�G���[���������܂����Bmain()��\n");
				return -1;
			}
			scanf("%d %d", &movefrom, &moveto);
			if(mainBord.move(movefrom, moveto)) printf("�ړ��ł��܂���@�w���Ȃ����Ă��������B\n");
			else break;
		}
		// ��̏���
	movetox = moveto / 10;
	movetoy = moveto % 10;
	

	mainBord.turnChange();//���̃^�[����
	}
	// ��菈��
	// ��̏���
	return 0;
}