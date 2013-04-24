#!/bin/bash

rm -f test_output.txt

for f in tests/*
do
  echo "Processing $f"
  ./knode "$f" >> test_output.txt
done
