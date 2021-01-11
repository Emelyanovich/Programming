from tkinter import *
from tkinter.font import BOLD
import requests


def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		cache = json.loads(response)

		desc.config(text=str(cache["description"]))
		temp.config(text=str(cache["temp"]) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.pack_propagate()
root.bind("<Button-1>", reload_data)



top_frame =    Frame(root, bg="coral")
middle_frame = Frame(root, bg="ghost white")
bottom_frame = Frame(root, bg="coral", width=200, height=50)

top_frame.pack(side=TOP, fill=X)
middle_frame.pack(expand=True, fill=BOTH)
bottom_frame.pack(side=BOTTOM, fill=X)

city = Label(top_frame, font=("Times New Roman", 14), text="Симферополь", bg="coral")
desc = Label(top_frame, font=("Times New Roman", 14), bg="coral")
temp = Label(middle_frame, font=("Times New Roman", 48), bg="ghost white")

city.pack(pady=0)
desc.pack(pady=0)
temp.pack(expand=True)


root.mainloop()
