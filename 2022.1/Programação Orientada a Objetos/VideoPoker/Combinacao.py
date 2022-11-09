#Esta classe recebe as cartas e verifica se ela forma uma combinação do poker
#e retorna o prêmio da aposta, as classes de checar já são auto explicativas.
#Para checar a igualdade entre cartas frequentemente é utilizado o resto da divisão por 13
#já que há 13 cartas por naipe. Muitos métodos também ordenam as cartas para achar uma combinação
class Combinacao:

    def checa_combinacao_royal_straight_flush(self,cartas):
        cartas.sort()
        if(cartas[0] == 8 and cartas[4] == 12):
            return True
        elif(cartas[0] == 21 and cartas[4] == 25):
            return True
        elif(cartas[0] == 34 and cartas[4] == 38):
            return True
        elif(cartas[0] == 47 and cartas[4] == 51):
            return True
        else:
            return False
    
    def checa_combinacao_straight_flush(self,cartas):
        if(self.checa_combinacao_straight(cartas)
           and self.checa_combinacao_flush(cartas)):
           return True
        else:
            return False

    def checa_combinacao_straight(self,cartas):
        cartaMod13 = []

        for i in range(5):
            cartaMod13.append(cartas[i] % 13)

        cartaMod13.sort()

        for i in range(1,5):
            if(cartaMod13[i] != (cartaMod13[i-1] + 1)):
                return False
            
        return True

    def checa_combinacao_flush(self,cartas):
        cartas.sort()

        if (cartas[0] >= 0 and cartas[4] <= 12):
            return True
        elif (cartas[0] >= 13 and cartas[4] <= 25):
            return True
        elif (cartas[0] >= 26 and cartas[4] <= 38):
            return True
        elif (cartas[0] >= 39 and cartas[4] <= 51):
            return True
        else:
            return False

    def checa_combinacao_quadra(self,cartas):
        cartaMod13 = []

        for i in range(5):
            cartaMod13.append(cartas[i] % 13)

        cartaMod13.sort()

        if(cartaMod13[0] == cartaMod13[1] and cartaMod13[1] == cartaMod13[2]
           and cartaMod13[2] == cartaMod13[3]):
            return True
        elif(cartaMod13[1] == cartaMod13[2] and cartaMod13[2] == cartaMod13[3]
           and cartaMod13[3] == cartaMod13[4]):
            return True
        else:
            return False

    def checa_combinacao_full_hand(self,cartas):
        cartaMod13 = []

        for i in range(5):
            cartaMod13.append(cartas[i] % 13)

        cartaMod13.sort()

        if(cartaMod13[0] == cartaMod13[1] and cartaMod13[1] == cartaMod13[2]
           and cartaMod13[3] == cartaMod13[4]):
            return True
        elif(cartaMod13[0] == cartaMod13[1] and cartaMod13[2] == cartaMod13[3]
           and cartaMod13[3] == cartaMod13[4]):
            return True
        else:
            return False

    def checa_combinacao_trinca(self,cartas):
        cartaMod13 = []

        for i in range(5):
            cartaMod13.append(cartas[i] % 13)

        cartaMod13.sort()

        if(cartaMod13[0] == cartaMod13[1] and cartaMod13[1] == cartaMod13[2]):
            return True
        elif(cartaMod13[1] == cartaMod13[2] and cartaMod13[2] == cartaMod13[3]):
            return True
        elif(cartaMod13[2] == cartaMod13[3] and cartaMod13[3] == cartaMod13[4]):
            return True
        else:
            return False

    def checa_combinacao_dois_pares(self,cartas):
        cartaMod13 = []

        for i in range(5):
            cartaMod13.append(cartas[i] % 13)

        cartaMod13.sort()

        if(cartaMod13[0] == cartaMod13[1] and cartaMod13[2] == cartaMod13[3]):
            return True
        elif(cartaMod13[0] == cartaMod13[1] and cartaMod13[3] == cartaMod13[4]):
            return True
        elif(cartaMod13[1] == cartaMod13[2] and cartaMod13[3] == cartaMod13[4]):
            return True
        else:
            return False


    #Este método roda os métodos anteriores hierarquicamente para tentar achar uma combinação
    #e retorna uma mensagem na tela junto com o valor apostado multiplicado.
    def checa_combinacao(self,aposta,cartas):
        if(self.checa_combinacao_royal_straight_flush(cartas)):
            print("Parabéns, você fez um Royal Straight Flush")
            print("Você ganhou {} créditos" .format(aposta*200))
            return aposta*200
        elif(self.checa_combinacao_straight_flush(cartas)):
            print("Parabéns, você fez um Straight Flush")
            print("Você ganhou {} créditos".format(aposta*100))
            return aposta*100
        elif(self.checa_combinacao_quadra(cartas)):
            print("Parabéns, você fez uma Quadra")
            print("Você ganhou {} créditos".format(aposta*50))
            return aposta*50
        elif(self.checa_combinacao_full_hand(cartas)):
            print("Parabéns, você fez um Full Hand")
            print("Você ganhou {} créditos".format(aposta*20))
            return aposta*20
        elif(self.checa_combinacao_flush(cartas)):
            print("Parabéns, você fez um Flush")
            print("Você ganhou {} créditos".format(aposta*10))
            return aposta*10
        elif(self.checa_combinacao_straight(cartas)):
            print("Parabéns, você fez um Straight")
            print("Você ganhou {} créditos".format(aposta*5))
            return aposta*5
        elif(self.checa_combinacao_trinca(cartas)):
            print("Parabéns, você fez uma Trinca")
            print("Você ganhou {} créditos".format(aposta*2))
            return aposta*2
        elif(self.checa_combinacao_dois_pares(cartas)):
            print("Parabéns, você fez um Dois Pares")
            print("Você ganhou {} créditos".format(aposta))
            return aposta
        else:
            print("Que pena, não ganhou nada")
            return 0