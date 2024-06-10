import os
import numpy as np
from pydub import AudioSegment
from scipy.signal import lfilter

def generate_noise(noise_type, length):
    if noise_type == 'white':
        return np.random.normal(0, 1, length)
    elif noise_type == 'pink':
        # Using Voss-McCartney algorithm to generate pink noise
        b = [0.049922035, -0.095993537, 0.050612699, -0.004408786]
        a = [1, -2.494956002, 2.017265875, -0.522189400]
        white = np.random.randn(length)
        return lfilter(b, a, white)
    elif noise_type == 'brown':
        brown = np.cumsum(np.random.normal(0, 1, length))
        brown = brown / max(abs(brown))  # Normalize to ensure the signal stays within a usable range
        return brown

def add_noise(audio_segment, noise_type, intensity):
    audio_data = np.array(audio_segment.get_array_of_samples())
    noise = generate_noise(noise_type, len(audio_data))
    noisy_audio = audio_data + intensity * noise
    noisy_audio = noisy_audio / max(abs(noisy_audio)) * max(abs(audio_data))  # Normalize to original amplitude
    return audio_segment._spawn(noisy_audio.astype(audio_data.dtype).tobytes())

def process_snippets(input_folder, output_folder):
    noise_types = ['white', 'pink', 'brown']
    intensities = [0.05, 0.1, 0.15, 0.2, 0.25]

    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for filename in os.listdir(input_folder):
        print("Processing file: ", filename)
        if filename.endswith(".wav"):
            input_path = os.path.join(input_folder, filename)
            audio_segment = AudioSegment.from_wav(input_path)
            
            for noise_type in noise_types:
                for intensity in intensities:
                    noisy_audio = add_noise(audio_segment, noise_type, intensity)
                    output_filename = f"{os.path.splitext(filename)[0]}_{noise_type}_intensity_{intensity}.wav"
                    output_path = os.path.join(output_folder, output_filename)
                    noisy_audio.export(output_path, format="wav", parameters=["-ar", "44100"])

if __name__ == "__main__":
    input_folder = "snippets"
    output_folder = "noise"
    
    process_snippets(input_folder, output_folder)
