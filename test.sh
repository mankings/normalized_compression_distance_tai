#!/bin/bash

WAV_DIR="lib/noise"
FREQ_DIR="test_audios"

# Loop through each .wav file in the WAV_DIR
for wav_file in "$WAV_DIR"/*.wav; do
    # Extract the base name without the directory and file extension
    base_name=$(basename "$wav_file" .wav)
    
    # Construct the frequency file path
    freq_file="$FREQ_DIR/$base_name.freqs"
    
    # Execute the GetMaxFreqs command
    ./GetMaxFreqs/bin/GetMaxFreqs -w "$freq_file" "$wav_file"
done

test_directory_path="test_audios"
compressors=("GZIP" "BZIP2" "LZMA" "ZSTD" "LZ4" "LZO" "SNAPPY")
output_csv="compression_results.csv"

# Create or clear the output CSV file
echo "Sample Name,Noise Type,Noise Intensity,Compressor,Result,Distance" > $output_csv

if [ -d "$test_directory_path" ]; then
  files=()
  for file in "$test_directory_path"/*; do
    # Ensure it is a file before adding it to the array
    if [ -f "$file" ]; then
        # Extract parts of the filename
        filename=$(basename -- "$file")
        sample_name=$(echo "$filename" | cut -d'_' -f2)
        noise_type=$(echo "$filename" | cut -d'_' -f3)
        noise_intensity=$(echo "$filename" | cut -d'_' -f5 | sed 's/.wav$//')

        for compressor in "${compressors[@]}"; do
            # Capture the result of the command
            result=$(./bin/shazam -c $compressor -d ./dataset/ -f $file)

            # Append the result to the CSV file
            echo "$sample_name,$noise_type,$noise_intensity,$compressor,$result" >> $output_csv
        done
    fi
  done
else
  echo "Directory does not exist."
fi
