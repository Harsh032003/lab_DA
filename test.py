import sys
sys.path.append(r"C:\Users\14har\AppData\Roaming\Python\Python312\site-packages")
from moviepy.editor import VideoFileClip


def get_video_length(file_path):
    try:
        with VideoFileClip(file_path) as video:
            return video.duration
    except Exception as e:
        print(f"Error processing file {file_path}: {e}")
        return 0

def find_video_lengths(parent_folder):
    total_duration = 0
    video_durations = {}

    for root, _, files in os.walk(parent_folder):
        for file in files:
            if file.lower().endswith((".mp4", ".mkv", ".avi", ".mov", ".flv", ".wmv")):
                file_path = os.path.join(root, file)
                duration = get_video_length(file_path)
                total_duration += duration
                video_durations[file_path] = duration

    return video_durations, total_duration

def format_duration(seconds):
    hours = int(seconds // 3600)
    minutes = int((seconds % 3600) // 60)
    seconds = int(seconds % 60)
    return f"{hours}h {minutes}m {seconds}s"

if __name__ == "__main__":
    parent_folder = input("Enter the path to the parent folder: ")
    video_durations, total_duration = find_video_lengths(parent_folder)

    print("\nVideo Durations:")
    for video, duration in video_durations.items():
        print(f"{video}: {format_duration(duration)}")

    print("\nTotal Duration:")
    print(format_duration(total_duration))
