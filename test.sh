#!/bin/bash

test_directory_path="test_audios"
compressors=("GZIP" "BZIP2" "LZMA" "ZSTD" "LZ4" "LZO" "SNAPPY")

if [ -d "$test_directory_path" ]; then
  files=()
  for file in "$test_directory_path"/*; do
    # Ensure it is a file before adding it to the array
    if [ -f "$file" ]; then
        echo $file
        echo "Compressors:"
        for compressor in "${compressors[@]}"; do
            echo "$compressor"

            ./bin/shazam -c $compressor -d ./dataset/ -f $file
        done
    fi
  done

else
  echo "Directory does not exist."
fi
