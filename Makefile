#Makefile 1: #は行末までのコメント
cc= gcc 
hasami:hasami_main.o func.o         # ターゲット a.out の依存ファイルは sub1.o, sub2.o
	cc -o hasami hasami_main.o func.o  # a.out の生成コマンド

hasami_main.o:hasami_main.cpp       # sub1.o の依存ファイルは sub1.c
	cc -c hasami_main.cpp -o hasami_main.o

func.o: func.cpp 		             # sub2.o の依存ファイルは sub2.c
	cc -c func.cpp -o func.o      # sub2.o の生成コマンド


# header.h はコンパイル時に include されるので、実際には何もしなくてよい
hasami_main.cpp: func.h			     # sub1.c の依存ファイルは header.h
func.cpp: func.h       			      # sub2.c の依存ファイルは header.h

