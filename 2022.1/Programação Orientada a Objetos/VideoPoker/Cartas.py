from operator import truediv
from Carta import Carta

#Esta classe representa 5 cartas de baralho
class Cartas:
    carta = [Carta(),Carta(),Carta(),Carta(),Carta()]
    estaDisponivel = [True]*52 #este vetor representa quais cartas estão disponíveis

    #Este método sorteia 5 cartas aleatórias de inicio
    def __init__(self):
        i = 0
        while(i != 5):
            cartaSorteada = self.carta[i].sorteia_carta()
            if(self.estaDisponivel[cartaSorteada]):
                i += 1
                self.estaDisponivel[cartaSorteada] = False

    #Este método reseta as cartas, todas ficam disponíveis
    def clear_cartas(self):
        for i in range(52):
            self.estaDisponivel[i] = True
    
    #Retorna um vetor com o número de todas as cartas
    def get_cartas(self):
        numeroCarta = [self.carta[0].get_carta()]
        numeroCarta.append(self.carta[1].get_carta())
        numeroCarta.append(self.carta[2].get_carta())
        numeroCarta.append(self.carta[3].get_carta())
        numeroCarta.append(self.carta[4].get_carta())

        return numeroCarta

    #Este método recebe uma string com o números das cartas que devem ser mudadas
    #Ele automaticamente aloca as novas cartas para o baralho
    def troca_cartas(self, cartasTroca):
        if(len(cartasTroca) == 0):
            return
        cartasTrocaList = cartasTroca.split(" ")
        
        for i in cartasTrocaList:
            x = int(i)
            if(x >= 1 and x <= 5):
                while(True):
                    cartaSorteada = self.carta[x-1].sorteia_carta()
                    if(self.estaDisponivel[cartaSorteada]):
                        self.estaDisponivel[cartaSorteada] = False
                        break

    #Representa as cartas na saída padrão
    def mostra_cartas(self):

        stringTotal = ""

        for i in range(7):
            for j in range(5):
                stringTotal += self.carta[j].string_carta()[i*9:(i*9)+9]
                stringTotal += " "
            stringTotal += "\n"

        print(stringTotal)