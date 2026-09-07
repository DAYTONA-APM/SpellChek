import ctypes
import os
import tkinter as tk

# 1. Load your compiled C library
lib_path = os.path.abspath("src/libtree.dylib")
c_lib = ctypes.CDLL(lib_path)

# 2. Tell Python what types of arguments the C functions expect
c_lib.py_load_dictionary.argtypes = [ctypes.c_char_p]
c_lib.py_load_dictionary.restype = None

c_lib.py_check_word.argtypes = [ctypes.c_char_p]
c_lib.py_check_word.restype = ctypes.c_int

# 3. Load your dictionary file through C
# Make sure this path points to your actual text file!
dict_path = b"dict_files/alpha_list.txt"
c_lib.py_load_dictionary(dict_path)

# 4. Build the GUI Window
window = tk.Tk()
window.title("C-Powered Spell Checker")
window.geometry("500x400")

label = tk.Label(window, text="Type text below (press Spacebar to check spelling):")
label.pack(pady=10)

# Main text area
text_area = tk.Text(window, font=("Arial", 14), wrap="word")
text_area.pack(expand=True, fill="both", padx=10, pady=10)

# Configure the visual style for misspelled words (red text)
text_area.tag_config("misspelled", foreground="red", underline=True)

def check_spelling(event=None):
    """Triggered every time the user presses Spacebar."""
    # 1. Clear all old red highlight tags before re-checking
    text_area.tag_remove("misspelled", "1.0", "end")

    # 2. Read the text box line by line to keep exact row coordinates
    lines = text_area.get("1.0", "end-1c").split("\n")
    
    for row_index, line in enumerate(lines, start=1):
        # Split the line into individual words while preserving positions
        words = line.split()
        search_start_column = 0
        
        for word in words:
            # Strip trailing punctuation for the C tree checker
            clean_word = word.strip(".,?!:;()\"'")

            #fix: for numbers not being marked as errors
            if clean_word.isdigit() or len(clean_word) == 0:
                continue
            
            # Convert string to bytes for our C compiled engine
            word_bytes = clean_word.encode('utf-8')
            
            # Query your C Binary Search Tree! (0 = FALSE/Typo, 1 = TRUE/Valid)
            is_correct = c_lib.py_check_word(word_bytes)
            
            # Find the exact coordinate of this word on the current line
            start_col = line.find(word, search_start_column)
            
            if is_correct == 0 and len(clean_word) > 0:
                # Convert numbers into Tkinter text coordinates (e.g., "1.5")
                start_pos = f"{row_index}.{start_col}"
                end_pos = f"{row_index}.{start_col + len(word)}"
                
                # Apply the visual red tag
                text_area.tag_add("misspelled", start_pos, end_pos)
            
            # Move our search window forward past this word
            search_start_column = start_col + len(word)


# Bind the spacebar key to trigger our check function instantly
text_area.bind("<space>", check_spelling)

window.mainloop()

