#!/bin/bash

# Check for the correct number of arguments
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <directory_path> <search_string> <replacement_string>"
  exit 1
fi

DIRECTORY=$1
SEARCH_STRING=$2
REPLACEMENT_STRING=$3

# Verify the directory exists
if [ ! -d "$DIRECTORY" ]; then
  echo "ERROR: $DIRECTORY is not a valid directory"
  exit 1
fi

# Find and replace the string in all files
find "$DIRECTORY" -type f -exec sed -i "s/$SEARCH_STRING/$REPLACEMENT_STRING/g" {} +

echo "Find and replace operation completed in $DIRECTORY"
