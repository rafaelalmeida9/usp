from Pessoa import Pessoa

gruposPath = ['Alcino Salviano Cavalcanti_15646577_assignsubmission_file_grupoPoo.csv',
'Antonio Lucas Sales Cavalcante Barbosa_15648885_assignsubmission_file_grupo.csv',
'Arthur Vergacas Daher Martins_15648862_assignsubmission_file_grupo.csv',
'Bernardo Maia Coelho_15646610_assignsubmission_file_grupo_poo.csv',
'Carlos Filipe de Castro Lemos_15646579_assignsubmission_file_grupopoo.csv',
'Daniel Henrique Lelis de Almeida_15646599_assignsubmission_file_grupo.csv',
'Danielle Modesti_15646569_assignsubmission_file_grupo_projeto_poo.csv',
'Davi Fagundes Ferreira da Silva_15646606_assignsubmission_file_dela.csv',
'Eric Rodrigues das Chagas_15646561_assignsubmission_file_Grupo_POO.csv',
'Felipe Seiji Momma Valente_15648866_assignsubmission_file_GrupoPOO.csv',
'Fernando Rosalini Calaza_15648896_assignsubmission_file_grupo.csv',
'Gabriel Natal Coutinho_15646559_assignsubmission_file_grupoPOO.csv',
'Gabriel Tavares Brayn Rosati_15646558_assignsubmission_file_grupoPOO.csv',
'Gustavo Sampaio Lima_15648891_assignsubmission_file_grupo.csv',
'Hélio Nogueira Cardoso_15646601_assignsubmission_file_grupoPOO.csv',
'Joao Pedro Matos de Deus_15646566_assignsubmission_file_nomes.csv',
'Kaito Hayashi_15646608_assignsubmission_file_Nomes.csv',
'Kenzo Yves Yamashita Nobre_15648855_assignsubmission_file_grupoPOO.csv',
'Maria Júlia Soares De Grandi_15648883_assignsubmission_file_grupo.csv',
'Rafael Sartori Vantin_15646581_assignsubmission_file_Planilha sem título - Página1.csv',
'Rafael Zimmer_15648875_assignsubmission_file_integrantes.csv',
'Raphael David Philippe Leveque_15646570_assignsubmission_file_grupo.csv',
'Samuel Figueiredo Veronez_15648861_assignsubmission_file_grupo.csv',
'Theo da Mota dos Santos_15648880_assignsubmission_file_grupos.csv']

arquivoTurma1 = open('turma1/ListadeApoioaoDocente-SSC01032022101.csv','r')
arquivoTurma2 = open('turma2/ListadeApoioaoDocente-SSC01032022102.csv','r')

turma1String = arquivoTurma1.read()
turma2String = arquivoTurma2.read()

listTurma1 = turma1String.split("\n")
listTurma2 = turma2String.split("\n")

pessoas = []

for x in listTurma1:
    if(x == ''):
        break
    pessoas.append(Pessoa(x,1))

for x in listTurma2:
    if(x == ''):
        break
    pessoas.append(Pessoa(x,2))

arquivoTurma1.close()
arquivoTurma2.close()

print("************Arquivos com problemas:************")

i = 1

for nomeArquivo in gruposPath:
    arquivoGrupo = open('grupos/'+nomeArquivo,'r')
    try:
        stringGrupo = arquivoGrupo.read()
        
        listGrupo = stringGrupo.split("\n")
        for x in listGrupo:
            if(x == ''):
                break
            membro = Pessoa(x,-1)
            for y in pessoas:
                if(membro.get_nusp() == y.get_nusp()):
                    y.set_grupo(i)
    except:
        print(nomeArquivo)
    i += 1

print()

print("************Grupos da turma 1:************")

for i in range(1,25):
    tamanho = 0
    for x in pessoas:
        if(x.get_grupo() == i and x.get_turma() == 1):
            print("Nome: {}, Nusp: {}".format(x.get_nome(),x.get_nusp()))
            tamanho += 1
    if(tamanho != 4 and tamanho != 0):
        print("************número de pessoas diferente de 4************")
    print()

print("************Grupos da turma 2:************")

for i in range(1,25):
    tamanho = 0
    for x in pessoas:
        if(x.get_grupo() == i and x.get_turma() == 2):
            print("Nome: {}, Nusp: {}".format(x.get_nome(),x.get_nusp()))
            tamanho += 1
    if(tamanho != 4 and tamanho != 0):
        print("************número de pessoas diferente de 4************")
    print()

print("************Pessoas sem grupo:************")

for x in pessoas:
    if(x.get_grupo() == -1):
        print("Nome: {}, Nusp: {}, Turma: {}".format(x.get_nome(),x.get_nusp(),x.get_turma()))