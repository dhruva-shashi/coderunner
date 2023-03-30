from tkinter import *
import json
import os

# Instance of tkinter frame or window
root = Tk()

# Set the size and title of the window
root.geometry('250x100')
root.title('Coderunner')

DIR_PATH = os.environ.get('HOME')+'/.coderunner/'

# Initialize images to be used in buttons
image_run = PhotoImage(file=DIR_PATH+'images.png')
image_resize = PhotoImage(file=DIR_PATH+'resize.png')

# Initialize interface for entering code file
label_code_file_path = Label(root, text='Path to code file')
text_code_file_path = Text(root, height=1, width=35)

# Initialize interface for entering input file
label_input_file_path = Label(root, text='Path to input file')
text_input_file_path = Text(root, height=1, width=35)

# Initialize interface for entering output file
label_output_file_path = Label(root, text='Path to output file')
text_output_file_path = Text(root, height=1, width=35)

label_time = Label(root, text='Time in seconds')
text_time = Text(root, height=1, width=35)

label_compiler = Label(root, text='Select Compiler')

# Initialize variables for window width and height
ORIGINAL_WIDTH = 250
ORIGINAL_HEIGHT = 100

RESIZED_WIDTH = 600
RESIZED_HEIGHT = 500

f = open(DIR_PATH+'config.json', 'r')
CONFIG = json.load(f)
f.close()

# Initialize the widgets
text_code_file_path.insert(END, CONFIG['CODE_FILE_PATH'])
text_input_file_path.insert(END, CONFIG['INPUT_FILE_PATH'])
text_output_file_path.insert(END, CONFIG['OUTPUT_FILE_PATH'])
text_time.insert(END, CONFIG['TIME_IN_SECONDS'])

def setLanguage(option):
	CONFIG['LANGUAGE'] = default.get()

# Initialize drop down menu for selecting compiler
compilers = ['c', 'cpp', 'java', 'python']
default = StringVar()
default.set(CONFIG['LANGUAGE'])
drop_compiler = OptionMenu(root, default, *compilers, command=setLanguage)


def coderunner():
	'''Runs the coderunner binary'''
	CONFIG['CODE_FILE_PATH'] = text_code_file_path.get('1.0', END).replace('\n', '')
	CONFIG['INPUT_FILE_PATH'] = text_input_file_path.get('1.0', END).replace('\n', '')
	CONFIG['OUTPUT_FILE_PATH'] = text_output_file_path.get('1.0', END).replace('\n', '')
	CONFIG['TIME_IN_SECONDS'] = text_time.get('1.0', END).replace('\n', '')

	# Create a coderunner command with 11 arguments
	COMMAND = 'coderunner'
	COMMAND += ' -l '+CONFIG['LANGUAGE']
	COMMAND += ' -c '+CONFIG['CODE_FILE_PATH']
	COMMAND += ' -i '+CONFIG['INPUT_FILE_PATH']
	COMMAND += ' -o '+CONFIG['OUTPUT_FILE_PATH']
	COMMAND += ' -t '+CONFIG['TIME_IN_SECONDS']

	COMMAND += ' > '+CONFIG['OUTPUT_FILE_PATH']

	os.system(COMMAND)


def resize_window():
	'''Resizes the window when resize button is clicked'''
	x = root.winfo_width()
	y = root.winfo_height()

	if x == ORIGINAL_WIDTH and y == ORIGINAL_HEIGHT:
		# Increase the size of the window and display text fields
		dim = str(RESIZED_WIDTH)+'x'+str(RESIZED_HEIGHT)
		root.geometry(dim)

		label_code_file_path.grid(row=1, column=0, padx=(10, 10), pady=(10, 10))
		text_code_file_path.grid(row=1, column=1, padx=(10, 10), pady=(10, 10))

		label_input_file_path.grid(row=2, column=0, padx=(10, 10), pady=(10, 10))
		text_input_file_path.grid(row=2, column=1, padx=(10, 10), pady=(10, 10))

		label_output_file_path.grid(row=3, column=0, padx=(10, 10), pady=(10, 10))
		text_output_file_path.grid(row=3, column=1, padx=(10, 10), pady=(10, 10))

		label_time.grid(row=4, column=0, padx=(10, 10), pady=(10, 10))
		text_time.grid(row=4, column=1, padx=(10, 10), pady=(10, 10))

		label_compiler.grid(row=5, column=0, padx=(10, 10), pady=(10, 10))
		drop_compiler.grid(row=5, column=1, padx=(10, 10), pady=(10, 10))

		root.mainloop()
	else:
		# Decrease the size of the window and hide text fields
		dim = str(ORIGINAL_WIDTH)+'x'+str(ORIGINAL_HEIGHT)
		root.geometry(dim)

		label_code_file_path.grid_forget()
		text_code_file_path.grid_forget()

		label_input_file_path.grid_forget()
		text_input_file_path.grid_forget()

		label_output_file_path.grid_forget()
		text_output_file_path.grid_forget()

		label_time.grid_forget()
		text_time.grid_forget()

		label_compiler.grid_forget()
		drop_compiler.grid_forget()

		root.mainloop()


# Initlalize buttons
button_run = Button(root, text='Run', image=image_run, compound=LEFT, command=coderunner)
button_resize = Button(root, image=image_resize, command=resize_window, height=40, width=40)

# Pack all the widgets
button_run.grid(row=0, column=0, padx=(20, 20), pady=(20, 20))
button_resize.grid(row=0, column=1, padx=(50, 20), pady=(20, 20))

label_code_file_path.grid_forget()
text_code_file_path.grid_forget()

label_input_file_path.grid_forget()
text_input_file_path.grid_forget()

label_output_file_path.grid_forget()
text_output_file_path.grid_forget()

label_time.grid_forget()
text_time.grid_forget()

drop_compiler.pack_forget()

# Make the window as the topmost window
root.attributes('-topmost', True)

icon = PhotoImage(file=DIR_PATH+'icon.png')
root.iconphoto(False, icon)

root.mainloop()

f = open(DIR_PATH+'config.json', 'w')
json.dump(CONFIG, f, indent=4)
f.close()

