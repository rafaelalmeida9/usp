class Pessoa:

    nusp = 0
    nome = ""
    turma = -1
    grupo = -1

    def __init__(self,string,turma):
        dados = string.split(",")
        self.nusp = int(dados[0])
        self.nome = dados[1]
        self.turma = turma

    def get_nusp(self):
        return self.nusp

    def get_nome(self):
        return self.nome

    def get_turma(self):
        return self.turma

    def get_grupo(self):
        return self.grupo

    def set_turma(self,turma):
        self.turma = turma

    def set_grupo(self,grupo):
        self.grupo = grupo
