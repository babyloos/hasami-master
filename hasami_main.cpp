// Q[?C[v
// hasami_main.cpp

#include <stdio.h>
#include "func.h"
#include <stdlib.h>

// 1���̋�A2���̋�A�O��̃}�X
#define aki 0
#define sente 1 //���
#define gote 2//���
	int countsente;	//����̎擾����
	int countgote;	//����̎擾����

class Bord {
	char bord[9][9]; // ??1???2 0
	int turn;		// �^�[���ϐ��@���P�@���Q
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

int Bord::move(int movefrom, int moveto) {
	int x;
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
	
	if((bord[movetoy+1][movetox]==abs(turn-3))&&(bord[movetoy-1][movetox]==abs(turn-3)))return -1;	//���܂�Ă���Ƃ���Ɉړ��͂ł��Ȃ�
	if((bord[movetoy][movetox+1]==abs(turn-3))&&(bord[movetoy][movetox-1]==abs(turn-3)))return -1;	//���܂�Ă���Ƃ���Ɉړ��͂ł��Ȃ�
	
	
	//����щz���Ȃ�����
	if(fromx!=movetox){//���ړ�
		if(movetox-fromx>0){//�E�ړ�
		for(x=1;x<(movetox-fromx);x++){
		if(bord[movetoy][fromx+x]!=0) return -1;
										}
							}
		else if(movetox-fromx<0){//���ړ�
			for(x=-1;x>(movetox-fromx);x--){
			if(bord[movetoy][fromx+x]!=0) return -1;
											}
								}
	} 
	
	else if(fromy-movetoy!=0){//�c�ړ�
			if(movetoy-fromy>0){//���ړ�
		for(x=1;x<(movetoy-fromy);x++){
		
		if(bord[fromy+x][fromx]!=0) return -1;
										}
							}
		else if(movetoy-fromy<0){//��ړ�
			for(x=-1;x>(movetoy-fromy);x--){
			if(bord[fromy+x][fromx]!=0) return -1;
											}
								}
	} 	
	



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
		switch(sosaroop){
		case 1:
		ret = sosa(x-1, y, turn);break;
		case 2:
		ret = sosa(x+1, y, turn);break;
		case 3:
		ret = sosa(x, y+1, turn);break;
		case 4:
		ret = sosa(x, y-1, turn);break;
		default:
			printf("sosa���łُ̈�");break;
		}
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
	int wins=0;
	int wing=0;
	


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
		
	//���������̏��� 
	if(countsente-countgote==3&&wins==0) wins=1;
	else if(countsente>=5||countsente-countgote>3||(countsente-countgote>=3)&&(wins==1)){printf("���̏����ł�\n");
	break;
 		}
 	
 	if(countgote-countsente==3&&wing==0) wing=1;
 	else if(countgote>=5||countgote-countsente>3||(countgote-countsente>=3)&&(wing==1)){printf("���̏����ł�\n");
 		break;
 		}

	mainBord.turnChange();//���̃^�[����
	}
	// ��菈��
	// ��̏���
	return 0;
}