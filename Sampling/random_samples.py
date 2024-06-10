import os
import random
from pydub import AudioSegment
from pydub.utils import make_chunks

def get_random_sample(audio_path, sample_length_ms):
    audio = AudioSegment.from_wav(audio_path)
    audio_length_ms = len(audio)
    
    if audio_length_ms <= sample_length_ms:
        return audio  # Return the whole audio if it's shorter than the sample length

    start_ms = random.randint(0, audio_length_ms - sample_length_ms)
    end_ms = start_ms + sample_length_ms

    return audio[start_ms:end_ms]

def save_audio_sample(audio_segment, output_path):
    audio_segment.export(output_path, format="wav")

def process_audio_files(input_folder, output_folder, sample_length_sec=10):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    sample_length_ms = sample_length_sec * 1000

    for filename in os.listdir(input_folder):
        if filename.endswith(".wav"):
            input_path = os.path.join(input_folder, filename)
            output_path = os.path.join(output_folder, f"sample_{filename}")

            audio_sample = get_random_sample(input_path, sample_length_ms)
            save_audio_sample(audio_sample, output_path)

if __name__ == "__main__":
    input_folder = "input"
    output_folder = "snippets"
    
    process_audio_files(input_folder, output_folder)
