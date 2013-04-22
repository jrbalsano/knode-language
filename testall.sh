#!/bin/bash

for f in tests/*
do
  echo "Processing $f"
  ./knode "$f" &>test_output.txt
done
