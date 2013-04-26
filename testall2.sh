#!/bin/sh

#  testall2.sh
#  
#
#  Created by Ruby Robinson on 4/25/13.
#

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

#this is the way you declare a function
Usage() {
echo "Usage: testall2.sh [options] [.kn files]"
echo "-k    Keep intermediate files"
echo "-h    Print this help"
exit 1
}

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

# Compare <outfile> <reffile> <difffile>
# Compares the outfile with reffile.  Differences, if any, written to difffile
# $3 third file
Compare() {
generatedfiles="$generatedfiles $3"
#checks to see if there are any differences between the files
#1 standard output, 2 standard error
#says send standard output to standard error
echo diff -b $1 $2 ">" $3 1>&2
diff -b "$1" "$2" > "$3" 2>&1 || {
SignalError "$1 differs"
echo "FAILED $1 differs from $2" 1>&2
}
}

# Run <args>
# Report the command, run it, and report any errors
Run() {
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
    reffile=`echo $1 | sed 's/.kn$//'`
    basedir="`echo $1 | sed 's/\/[^\/]*$//'`/."

    echo -n "$basename..."

    echo 1>&2
    echo "###### Testing $basename" 1>&2

    
    Run "$KNODE" "$1" > "$1.out"

    # Report the status and clean up the generated files

    if [ $error -eq 0 ] ; then
	if [ $keep -eq 0 ] ; then
	    rm -f $generatedfiles
	fi
	echo "OK"
	echo "###### SUCCESS" 1>&2
    else
	echo "###### FAILED" 1>&2
	globalerror=$error
    fi
}


while getopts kdpsh c; do
case $c in
k) # Keep intermediate files
keep=1
;;
h) # Help
Usage
;;
esac
done

shift `expr $OPTIND - 1`

if [ $# -ge 1 ]
then
files=$@
else
files="tests/fail-*.kn tests/test-*.kn"
fi

for file in $files
do
case $file in
*test-*)
Check $file 2>> $globallog
;;
*fail-*)
CheckFail $file 2>> $globallog
;;
*)
echo "unknown file type $file"
globalerror=1
;;
esac
done

exit $globalerror



