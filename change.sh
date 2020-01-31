#!/bin/bash
function changeName(){
	#new=`echo $1|sed 's/^/abc/g'`
	new=`echo $1|sed -r 's/abc(.*$)/\1/g'`
	echo changeName old: $1 new: $new
	if [ $1 != $new ];then
		mv $1 $new
	fi
}
 
function travFolder(){
	#echo "travFolder start"
	flist=`ls $1`
	cd $1
	for f in $flist
	do
		#echo traverse do $f
		local old=$f
		if test -d $f
		then
			#echo "traverse dir:${f}"
			if [ $f = $ton ];then
				echo "tommmmmmmmmmmmmmmmmmmmm"
				echo "11_traverse file:$f"
				cd `pwd`
				ls
				mv $old $ton1
				cd -
				travFolder $ton1
			else 	
				travFolder $f
			fi
			#echo "traverse rename dir:${f}"
	#		changeName $old #新加的rename文件夹名字
		else
			echo "traverse file:$f"
#			#if [ $f = $tom ];then
#			pwd
#			ls
			if [ $f = $tom ];then
				pwd
				echo "llllllllllllllllllllll"
				echo "traverse file:$f"
				mv $old $tom1
			fi
#			changeName $f
		fi
	done
	cd ../
}

param=$1
if [ -z "$1" ]
	then
	param="./"
	echo "empty string: $param"
else
	param=$1
fi
tom="试验必看.doc"
tom1="step.doc"
tom2="Wiring_diagram.jpg"
tom3="state.txt"
ton="程序"
ton1="program"
ton2="program1"

travFolder $param
