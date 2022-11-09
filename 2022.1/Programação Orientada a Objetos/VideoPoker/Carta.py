from re import S
from unicodedata import numeric
import random

#Esta classe representa uma carta das 52 do baralho
class Carta:

    numero = 0
    cartas = ["2♠ ","3♠ ","4♠ ","5♠ ","6♠ ","7♠ ","8♠ ","9♠ ","10♠","J♠ ","Q♠ ","K♠ ","A♠ ",
              "2♦ ","3♦ ","4♦ ","5♦ ","6♦ ","7♦ ","8♦ ","9♦ ","10♦","J♦ ","Q♦ ","K♦ ","A♦ ",
              "2♣ ","3♣ ","4♣ ","5♣ ","6♣ ","7♣ ","8♣ ","9♣ ","10♣","J♣ ","Q♣ ","K♣ ","A♣ ",
              "2♥ ","3♥ ","4♥ ","5♥ ","6♥ ","7♥ ","8♥ ","9♥ ","10♥","J♥ ","Q♥ ","K♥ ","A♥ "]
    #Esse vetor representa cada carta no baralho, o qual o número se repete a cada 13 cartas,
    #indo ao próximo naipe, ou seja, as cartas n % 13 são iguais

    def __init__(self):
        self.numero = 0
    
    def get_carta(self):
        return self.numero

    #sorteia uma carta de 0 a 51
    def sorteia_carta(self):
        self.numero = random.randint(0,51)
        return self.numero
    
    #retorna a representação em string da carta
    def string_carta(self):
        cartaStr = "+-------+|       ||       ||  "
        cartaStr += self.cartas[self.numero]
        cartaStr += "  ||       ||       |+-------+"

        return cartaStr