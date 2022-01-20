from tkinter import *
import random

# Ohjelmointi 1: Johdanto
# Ohjelma on monelle tuttu hirsipuu, eli sananarvailupeli. Käyttöliittymässä
# on kirjainnappuloita, joita painamalla pelaaja voi yrittää arvata ikkunan
# keskellä olevaa sanaa. Jokainen väärä arvaus rakentaa hirsipuuta yhden palan
# lisää ja pelaaja häviää, kun hirsipuu on valmis. Jos pelaaja arvaa sanan,
# kuvaruutuun ilmestyy pokaali onnistumisen merkiksi. Peli päättyy siis joko
# voittoon tai häviöön, kummassakin tapauksessa pelaaja voi halutessaan
# aloittaa uuden pelin tai lopettaa pelaamisen.

PICS = ["hirsi0.gif", "hirsi1.gif", "hirsi2.gif", "hirsi3.gif", "hirsi4.gif",
        "hirsi5.gif", "hirsi6.gif", "hirsi7.gif", "voitto.gif"]

ALPHABET = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
            "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
            "Å", "Ä", "Ö"]

WORDS = []  # tähän listaan lisätään tiedoston lukemisen yhteydessä sanat


class Hirsipuu:
    def __init__(self):
        """
        Rakentaa pohjan, jonka mukaan ohjelman käyttöliittymä toimii.
        self.__pics: Sisältää ohjelmassa käytettävät kuvat (list)
        self.__word: arpoo sanoja sisältävästä listasta arvattavan sanan
        self.__miss: pitää kirjaa vääristä arvauksista
        self.__hits: pitää kirjaa oikeista arvauksista
        self.__alphabetbuttons: lista kirjainnäppäimistä (list)
        self.__piclabel: ikkunassa näkyvä kuva (Label)
        self.__pick_a_letter: ohjeistava teksti (Label)
        self.__quit: lopettaa ohjelman suorituksen (Button)
        self.__new_game: aloittaa uuden pelin (Button)
        self.__letters: lista ikkunassa näkyvistä arvatuista/arvaamattomista
                        kirjaimista
        """
        self.__main_window = Tk()
        self.__main_window.title("Hirsipuu")
        self.__pics = []
        self.__word = random.choice(WORDS)
        self.__miss = 0
        self.__hits = 0
        self.__alphabetbuttons = []

        for picfile in PICS:
            pic = PhotoImage(file=picfile)
            self.__pics.append(pic)

        for i in range(len(ALPHABET)):
            new_button = Button(self.__main_window, text=ALPHABET[i],
                                background="yellow",
                                command=lambda p=i:
                                self.check_if_letter_in_word(p),
                                state=NORMAL)
            new_button.grid(row=1, column=i+1)
            self.__alphabetbuttons.append(new_button)

        self.__piclabel = Label(self.__main_window, image=self.__pics[0])
        self.__piclabel.grid(row=0, column=len(ALPHABET) + 2)

        self.__pick_a_letter = Label(self.__main_window,
                                     text="Valitse kirjain:")
        self.__pick_a_letter.grid(row=1, column=0)

        self.__quit = Button(self.__main_window, text="Lopeta",
                             background="red", foreground="white",
                             command=self.exit)
        self.__quit.grid(row=5, column=0, sticky=N + W)

        self.__new_game = Button(self.__main_window, text="Uusi peli",
                                 background="green", foreground="white",
                                 command=self.initialize_game)
        self.__new_game.grid(row=4, column=0, sticky=N + W)

        self.__letters = []
        for i in range(len(self.__word)):
            new_label = Label(self.__main_window, text="_ ")
            new_label.grid(row=0, column=2+i)
            self.__letters.append(new_label)

    def start(self):
        """
        Käynnistää mainloopin.
        """
        self.__main_window.mainloop()

    def exit(self):
        """
        Sulkee ohjelman.
        """
        self.__main_window.destroy()

    def initialize_game(self):
        """
        Alustaa pelin arvot, listat ja ikkunan uuden pelin alussa.
        """
        for label in self.__letters:
            label.destroy()
        self.__miss = 0
        self.__hits = 0
        self.__piclabel.configure(image=self.__pics[self.__miss])
        self.__word = random.choice(WORDS)
        self.__letters = []
        for i in range(len(self.__word)):
            new_label = Label(self.__main_window, text="_ ")
            new_label.grid(row=0, column=2 + i)
            self.__letters.append(new_label)
        for button in self.__alphabetbuttons:
            button.configure(state=NORMAL, background="yellow")

    def check_if_letter_in_word(self, i):
        """
        Tarkistaa, onko painettua nappulaa vastaava kirjain arvattavassa
        sanassa ja kutsuu tilanteen mukaista metodia.
        :param i: indeksi, jonka avulla löydetään ALPHABET listasta painettua
                  nappulaa vastaava kirjain.
        """
        if ALPHABET[i] not in self.__word.upper():
            self.wrong_letter(i)
        else:
            self.right_letter(i)

    def wrong_letter(self, i):
        """
        Toiminta painettaessa nappulaa, jota vastaava kirjain ei ole
        arvattavassa sanassa.
        :param i: kirjainta vastaavan nappulan indeksi
        """
        self.__alphabetbuttons[i].configure(state=DISABLED, background="grey")
        self.__miss += 1
        if self.__miss == 7:
            self.lost_game()
        self.__piclabel.configure(image=self.__pics[self.__miss])

    def right_letter(self, i):
        """
        Toiminta painettaessa nappulaa, jota vastaava kirjain on arvattavassa
        sanassa.
        :param i: kirjainta vastaavan nappulan indeksi
        """
        letter = ALPHABET[i].lower()
        self.__alphabetbuttons[i].configure(state=DISABLED, background="grey")
        for i in range(len(self.__word)):
            if self.__word[i] == letter:
                self.__letters[i].configure(text=letter.upper())
                self.__hits += 1
        if self.__hits == len(self.__letters):
            self.game_won()

    def lost_game(self):
        """
        Toiminta kun kaikki arvauskerrat on käytetty eli kun peli hävitään.
        """
        for button in self.__alphabetbuttons:
            button.configure(state=DISABLED, background="grey")
        for i in range(len(self.__word)):
            self.__letters[i].configure(text=self.__word[i].upper() + " ")

    def game_won(self):
        """
        Toiminta kun kaikki sanan kirjaimet on arvattu.
        """
        self.__piclabel.configure(image=self.__pics[-1])
        for button in self.__alphabetbuttons:
            button.configure(state=DISABLED, background="grey")


def read_file():
    """
    Lukee satunnaisia Kielitoimiston sanakirjasta kopioituja sanoja sisältävän
    sanakirja.txt -nimisen tiedoston ja lisää ne WORDS listaan.
    """
    try:
        file = open("sanakirja.txt", 'r')
        for row in file:
            row = row.rstrip()
            WORDS.append(row)
        file.close()
    except OSError:
        print("There was an error reading file sanakirja.txt")


def main():
    read_file()
    ui = Hirsipuu()
    ui.start()


main()
