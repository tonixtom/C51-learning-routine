/*******************************************************************************
*                 
*                 		       普中科技
--------------------------------------------------------------------------------
* 实 验 名		 : 跑马灯实验
* 实验说明       : LED灯做跑马灯左右移动
* 连接方式       : 见接线图
* 注    意		 : 
*******************************************************************************/

	ORG 	0000h
	AJMP	start
	ORG		0030h
start:
	MOV 	A,#0ffh	
	CLR 	C		
	MOV 	R2,#08h	;循环八次。

loop:		
	RLC 	A		;带进位左移。
	MOV 	P0,A	;输出到P1口。
	CALL 	delay	;延时一段时间
	DJNZ 	R2,loop	;反复循环
	MOV 	R2,#07h	;再往回循环。

loop1:	
	RRC 	a		;带进位右移
	MOV 	P0,a	;输出到P1口。
	CALL 	delay	;延时一段时间
	DJNZ 	R2,loop1	;反复循环
	JMP 	start	;重新开始

delay:
	MOV R3,#20	;延时子程序
d1:
	MOV R4,#20
d2:
	MOV R5,#248
	DJNZ R5,$
	DJNZ R4,d2
	DJNZ R3,d1
	RET
END

