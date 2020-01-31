echo "travFolder"
  flist=`ls $1`
  cd $1
  echo $flist
  for f in $flist
  do
    if test -d $f
    then
      echo "dir:$f"
  #    travFolder $f
    else
      echo "file:$f"
  #    changeName $f
    fi
  done
#  cd ../ 
  for e in `find ./`
  do	
	  echo $e
  done
