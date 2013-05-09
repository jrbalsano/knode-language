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
isTestingPass=0
keep=0

#error handling
#always end if then else construct with a fi
# $1 means first argument on command line
SignalError() {
if [ $error -eq 0 ] ; then
error=1
fi
echo "$1" >> $globallog
}

# Run <args>
# Report the command, run it, and report any errors
Run() {
#report into log if one faile or had an error
echo $* >> $globallog
#if the first command succeeds the second will not be evaluated
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
echo >> $globallog
echo "###### Testing $basename" >> $globallog
rm -f "$1.out"
Run "$KNODE" "$1" > "$1.out"
# Report the status and clean up the generated files
echo "Done testing"
if [ $isTestingPass -eq 0 ] ; then
  if [ $error -eq 0 ] ; then
    echo -e "\033[32mOK\033[0m"
    echo "###### SUCCESS" >> $globallog
  else
    echo -e "\033[31mFAILED\033[0m"
    echo "###### FAILED" >> $globallog
    globalerror=$error
  fi
else
  if [ $error -eq 0 ] ; then
    echo -e "\033[31mFAILED\033[0m"
    echo "###### FAILED" >> $globallog
  else
    echo -e "\033[32mOK\033[0m"
    echo "###### SUCCESS" >> $globallog
    globalerror=$error
  fi
fi
}
#Get all of the test scripts and store their names in $files
passFiles="testPass/test-*.kn"
failFiles="testFail/test-*.kn"

#for each file in files, run them and print them to .out files
echo -e "\033[36mNOW TESTING PASS FILES\033[0m"
for f in $passFiles
do
Check $f
done
isTestingPass=$(( $isTestingPass + 1 ))
echo -e "\033[36mNOW TESTING FAIL FILES\033[0m"
for f in $failFiles
do
Check $f
done


