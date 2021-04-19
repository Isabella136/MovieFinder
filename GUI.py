import _tkinter
import tkinter as tk
import webbrowser as web

#The following resource was used when working with tkinter: https://coderslegacy.com/python/python-gui/

from ctypes import cdll
lib = cdll.LoadLibrary('./libMovie.so')

class Implement(object):
    def __init__(self):
        self.object = lib.Implement_new()
    def filter(self):
        lib.Implement_filter(self.object)

def filterGenre():
    userInput[0] = genres[listGenre.curselection()[0]]

def filterYear():
    userInput[1] = yrLow.get()
    userInput[2] = yrHigh.get()

def filterDur():
    userInput[3] = durLow.get()
    userInput[4] = durHigh.get()

def filterCountry():
    userInput[5] = countries[listCountry.curselection()[0]]
    
def finalStep():
    def openWeb():
        web.open("https://www.imdb.com/title/" + codes[listMovies.curselection()[0]] + "/")
        
    file = open("outputSet.txt")
    titles = [file.readline()]
    codes = [file.readline()]
    s = file.readline()
    while(s != ''):
        titles.append(s)
        codes.append(file.readline())
        s = file.readline()
    file.close()
    
    labelMovies = tk.Label(movies_frame, text = 'List of Movies:')
    labelGenre.pack()

    scrollMovies = tk.Scrollbar(movies_frame)
    scrollMovies.pack(side = tk.RIGHT, fill = tk.Y)

    i = 0
    listMovies = tk.Listbox(movies_frame, yscrollcommand = scrollMovies.set, width = "40")
    while(i < len(titles)):
        listMovies.insert(i+1, titles[i])
        i+=1
    listMovies.pack()

    bttnMovies = tk.Button(movies_frame, text = "Select", command = openWeb)
    bttnMovies.pack()

def filterPrep():
    moviesList = Implement()
    file = open("implemetationTime.txt")
    label1 = tk.Label(lower_frame, text = file.readline())
    label1.pack()
    label2 = tk.Label(lower_frame, text = file.readline())
    label2.pack()
    
    file = open("userInput.txt", "w")
    file.write(userInput[0])
    file.write(userInput[1] + "\n")
    file.write(userInput[2] + "\n")
    file.write(userInput[3] + "\n")
    file.write(userInput[4] + "\n")
    file.write(userInput[5])
    file.close()
    moviesList.filter()

    file = open("implemetationTime.txt")
    label1 = tk.Label(lower_frame, text = file.readline())
    label1.pack()
    label2 = tk.Label(lower_frame, text = file.readline())
    label2.pack()
    finalStep();

file = open("Genres.txt")
genres = [file.readline()]
s = file.readline()
while(s != ''):
    genres.append(s)
    s = file.readline()
file.close()

file = open("Countries.txt")
countries = [file.readline()]
s = file.readline()
while(s != ''):
    countries.append(s)
    s = file.readline()
file.close()

userInput = ["None", "1894", "2020", "41", "808", "All Countries"]

root = tk.Tk()
root.geometry("1200x720")

label = tk.Label(root, text = 'Movie Finder', font = "1")
label.pack(pady = 5)



filter_frame = tk.Frame(root)
filter_frame.pack()


genre = tk.Frame(filter_frame)
genre.pack(side = tk.LEFT)

labelGenre = tk.Label(genre, text = 'Genre:')
labelGenre.pack()

scrollGenre = tk.Scrollbar(genre) 
scrollGenre.pack(side = tk.RIGHT, fill = tk.Y)

i = 0
listGenre = tk.Listbox(genre, yscrollcommand = scrollGenre.set)
while(i < len(genres)):
    listGenre.insert(i+1, genres[i])
    i+=1    
listGenre.pack()

bttnGenre = tk.Button(genre, text = "Update", command = filterGenre)
bttnGenre.pack()


year = tk.Frame(filter_frame)
year.pack(side = tk.LEFT)

labelYear = tk.Label(year, text = 'Year:')
labelYear.pack()

yrLow = tk.Entry(year, width = 5)
yrLow.insert(0, '1894')
yrLow.pack()

yrHigh = tk.Entry(year, width = 5)
yrHigh.insert(0, '2020')
yrHigh.pack()

bttnYear = tk.Button(year, text = "Update", command = filterYear)
bttnYear.pack()


duration = tk.Frame(filter_frame)
duration.pack(side = tk.LEFT)

labelDur = tk.Label(duration, text = 'Duration (in minutes):')
labelDur.pack()

durLow = tk.Entry(duration, width = 5)
durLow.insert(0, '41')
durLow.pack()

durHigh = tk.Entry(duration, width = 5)
durHigh.insert(0, '808')
durHigh.pack()

bttnDur = tk.Button(duration, text = "Update", command = filterDur)
bttnDur.pack()


country = tk.Frame(filter_frame)
country.pack(side = tk.LEFT)

labelCountry = tk.Label(country, text = 'Country:')
labelCountry.pack()

scrollCountry = tk.Scrollbar(country) 
scrollCountry.pack(side = tk.RIGHT, fill = tk.Y)

i = 0
listCountry = tk.Listbox(country, yscrollcommand = scrollCountry.set)
while(i < len(countries)):
    listCountry.insert(i+1, countries[i])
    i+=1    
listCountry.pack()

bttnCountry = tk.Button(country, text = "Update", command = filterCountry)
bttnCountry.pack()



movies_frame = tk.Frame(root)
movies_frame.pack(pady = 20)



lower_frame = tk.Frame(root)
lower_frame.pack(side = tk.BOTTOM)



bttn = tk.Button(filter_frame, text = "Submit", command = filterPrep)
bttn.pack(side = tk.BOTTOM)

root.title("Movie Finder")
root.mainloop()

