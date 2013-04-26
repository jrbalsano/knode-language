#!/bin/bash
KNODE="./knode"

# Set time limit for all operations
ulimit -t 30
# Log file, file that contains a list of events which have been "logged" by a computer

globallog=testall.log
#remove file globallog , -f is for whether there is a file or not
rm -f $globallog
#errors
error=0
globalerror=0

keep=0

#error handling
#always end if then else construct with a fi
# $1 means first argument on command line
SignalError() {
if [ $error -eq 0 ] ; then
echo "FAILED"
error=1
fi
echo "  $1"
}

# Run <args>
# Report the command, run it, and report any errors
Run() {
#report into log if one faile or had an error
echo $* 1>&2
eval $* || {
SignalError "$1 failed on $*"
return 1
}
}

Check() {
    error=0
    basename=`echo $1 | sed 's/.*\\///
                             s/.kn//'`
							 
    basedir="`echo $1 | sed 's/\/[^\/]*$//'`/."

    echo -n "$basename..."

    echo 1>&2
    echo "###### Testing $basename" 1>&2
	
	Run "$KNODE" "$1" > "$1.out"
	
	if [ "$?" != "0" ]; then
	SignalError "$1 has error"
	fi

    # Report the status and clean up the generated files

    if [ $error -eq 0 ] ; then
	if [ $keep -eq 0 ] ; then
	    echo "Done testing"
	fi
	echo "OK"
	echo "###### SUCCESS" 1>&2
    else
	echo "###### FAILED" 1>&2
	globalerror=$error
    fi
}
#Get all of the test scripts and store their names in $files
files="tests/test-*.kn"

#for each file in files, run them and print them to .out files
for f in $files
do
  Check $f 2>> $globallog
done
