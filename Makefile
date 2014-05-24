#Makefile 1: #�͍s���܂ł̃R�����g
cc= gcc 
hasami:hasami_main.o func.o         # �^�[�Q�b�g a.out �̈ˑ��t�@�C���� sub1.o, sub2.o
	cc -o hasami hasami_main.o func.o  # a.out �̐����R�}���h

hasami_main.o:hasami_main.cpp       # sub1.o �̈ˑ��t�@�C���� sub1.c
	cc -c hasami_main.cpp -o hasami_main.o

func.o: func.cpp 		             # sub2.o �̈ˑ��t�@�C���� sub2.c
	cc -c func.cpp -o func.o      # sub2.o �̐����R�}���h


# header.h �̓R���p�C������ include �����̂ŁA���ۂɂ͉������Ȃ��Ă悢
hasami_main.cpp: func.h			     # sub1.c �̈ˑ��t�@�C���� header.h
func.cpp: func.h       			      # sub2.c �̈ˑ��t�@�C���� header.h

