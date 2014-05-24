// func.cpp
// 一桁のxy座標表記をx座標とy座標に分割するやつ
#include "func.h"

int tox(int xy){
	return xy / 10;
}

int toy(int xy) {
	return xy % 10;
}
