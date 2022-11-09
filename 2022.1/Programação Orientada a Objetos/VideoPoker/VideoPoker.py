import os
from Cartas import Cartas
from Combinacao import Combinacao

#Este é o método principal do programa, ele roda um loop infinito até acabarem
#os créditos do usuário limpando a tela ao longo do programa
#e sorteando e mostrando as cartas com a classe "Cartas"
#e ao fim de 2 trocas de carta ele verifica as combinações de carta com a classe "Combinacao"

combinacao = Combinacao()
creditos = 200
aposta = 0

while creditos >= 0:
    print("Créditos atuais:", creditos)

    cartas = Cartas()

    aposta = int(input("Digite o valor a ser apostado:"))
    os.system('clear')

    if aposta > creditos:
        aposta = creditos
        creditos = 0
    else:
        creditos -= aposta

    print("1         2         3         4         5")
    cartas.mostra_cartas()

    cartaTroca = input("Digite os numeros da(s) carta(s) que deseja trocar, para trocar nada aperte enter:\n")
    os.system('clear')

    cartas.troca_cartas(cartaTroca)

    print("1         2         3         4         5")
    cartas.mostra_cartas()

    cartaTroca = input("Digite outra vez os numeros da(s) carta(s) que deseja trocar, para trocar nada aperte enter:\n")
    os.system('clear')

    cartas.troca_cartas(cartaTroca)

    print("1         2         3         4         5")
    cartas.mostra_cartas()

    arrayCartas = cartas.get_cartas()

    creditos += combinacao.checa_combinacao(aposta,arrayCartas)
    print("Créditos atuais:", creditos)

    if(creditos <= 0):
        break

    stringVazia = input("\npressione enter para ir a próxima rodada")
    os.system('clear')

    cartas.clear_cartas()

print("Acabaram seus créditos, fim de jogo")