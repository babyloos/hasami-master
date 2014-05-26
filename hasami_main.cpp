// Q[?C[v
// hasami_main.cpp

#include <stdio.h>
#include "func.h"
#include <stdlib.h>

// 1先手の駒、2後手の駒、０空のマス
#define aki 0
#define sente 1 //先手
#define gote 2//後手
class Bord {
	char bord[9][9]; // ??1???2 0
	int turn;		// ターン変数　先手１　後手２
	int countsente;	//先手駒の取得枚数
	int countgote;	//後手駒の取得枚数
	int sosaroop;		//捜査での変数
public:
	Bord();
	void show_bord();
	int move(int movefrom, int moveto);
	int sosa(int x, int y, int turn);
	int show_turn();
	void turnChange();

};


Bord::Bord() {
	// 盤の初期化
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

	turn = 1;		// ターン初期化
	countsente=0;	//先手の駒の取得枚数初期化
	countgote=0;	//後手の駒の取得枚数初期化
}

// 盤の表示
void Bord::show_bord() {
	printf(" 0  1  2  3  4  5  6  7  8\n");
	for(int i=0; i<9; i++) {
		printf(" ＿ ＿ ＿ ＿ ＿ ＿ ＿ ＿ ＿ \n");	
		for(int j=0; j<9; j++) {
			printf("|");
			if(bord[i][j] == sente) printf("歩");
			else if(bord[i][j] == gote) printf("と");
			else printf("　");
			
		}
		printf("|");
		printf("\n ー ー ー ー ー ー ー ー ー %d\n", i);
	}

}

int Bord::move(int movefrom, int moveto) {
	// char thisTurn;
	/*
if (turn == 1) thisTurn = 1;
	else if (turn == 2) thisTurn = 2;
	
	else {
		printf("エラーが発生しました。Bord.move()\n");
	}
	 */

	int fromx = movefrom / 10;
	int fromy = movefrom % 10;

	int movetox = moveto / 10;
	int movetoy = moveto % 10;

	if((fromx!=movetox)&(fromy!=movetoy)) return -1;	// マスは縦横にしか移動できない
	
	if((bord[movetoy+1][movetox]==abs(turn-3))&&(bord[movetoy-1][movetox]==abs(turn-3)))return -1;	//挟まれているところに移動はできない
	if((bord[movetoy][movetox+1]==abs(turn-3))&&(bord[movetoy][movetox-1]==abs(turn-3)))return -1;	//挟まれているところに移動はできない



	if((bord[fromy][fromx]==turn)&(bord[movetoy][movetox] == aki)){   // 自分の駒で移動先が空の場合だけ移動処理をする
			bord[movetoy][movetox] = bord[fromy][fromx];
			bord[fromy][fromx] = aki;
	}else {
		return -1;
	}
	sosaroop=1;
	sosa(movetox-1, movetoy,turn); //左捜査へ
	sosaroop=2;
	sosa(movetox+1, movetoy,turn); //右捜査へ
	sosaroop=3;
	sosa(movetox, movetoy+1,turn); //上捜査へ
	sosaroop=4;
	sosa(movetox, movetoy-1,turn); //下捜査へ
	sosaroop=0;
	return 0;
}

// 上下左右に操作していく
int Bord::sosa(int x, int y, int turn) {
	int ret;
	int teki = abs(turn - 3);
	// 自分の駒を見つけたら、１を返して終了する。
	if(bord[y][x] == turn) {
		return 1;

	// 敵の駒を見つけたら、座標を1つずらして、sosaを呼び出す。
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
			printf("sosa内での異常");break;
		}
		// １が帰ってきたら今の座標を自分の駒に置き換える
		if(ret == 1){
		 bord[y][x] = 0;
		 if(turn==sente){countsente+=1;
		 				printf("\n先手の駒取得数%d枚\n",countsente);}
		 else if(turn==gote){countgote+=1;
						printf("\n後手の駒取得数%d枚\n",countgote);}
		}
		return ret;

	// 空の座標を見つけるか、盤の外に出てしまったら-1を返して終了する。
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
	printf("最新のファイルです。\n");
	// ?
	int movefrom, moveto;
	int movetox;
	int movetoy;


	while(1) {
		while(1) {
			mainBord.show_bord();
			if(mainBord.show_turn() == sente ) printf("先手の番です。駒の移動（移動元の駒の座標、移動先の駒の座標）turn:%d :", mainBord.show_turn());
			else if(mainBord.show_turn()== gote) printf("後手の番です。駒の移動（移動元の駒の座標、移動先の駒の座標）turn%d:",mainBord.show_turn());
			else { 
				printf("エラーが発生しました。main()内\n");
				return -1;
			}
			scanf("%d %d", &movefrom, &moveto);
			if(mainBord.move(movefrom, moveto)) printf("移動できません　指しなおしてください。\n");
			else break;
		}
		// 駒の処理
	movetox = moveto / 10;
	movetoy = moveto % 10;
	

	mainBord.turnChange();//次のターンへ
	}
	// 後手処理
	// 駒の処理
	return 0;
}