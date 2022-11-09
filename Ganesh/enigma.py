from string import ascii_uppercase

rotor1 = ['J', 'P', 'S', 'X', 'V', 'U', 'T', 'C', 'R', 'Z', 'W', 'O', 'N', 'Y', 'L', 'K', 'A', 'I', 'G', 'H', 'F', 'E', 'D', 'B', 'M', 'Q']

rotor2 = ['Q', 'W', 'E', 'V', 'C', 'X', 'Z', 'L', 'K', 'J', 'H', 'G', 'F', 'D', 'S', 'A', 'P', 'O', 'I', 'U', 'Y', 'T', 'R', 'B', 'N', 'M']

reflector = {'A':'S', 'M':'V', 'J':'Z', 'L':'Q', 'C':'O', 'H':'U', 'G':'W', 'F':'P', 'K':'R', 'I':'N', 'E':'T', 'D':'X', 'B':'Y', 'S':'A', 'V':'M', 'Z':'J', 'Q':'L', 'O':'C', 'U':'H', 'W':'G', 'P':'F', 'R':'K', 'N':'I', 'T':'E', 'X':'D', 'Y':'B'}

def reverse(n_rotor):
    rev_rotor = [None] * len(n_rotor)
    for it in range(len(n_rotor)):
        rev_rotor[ord(n_rotor[it]) - ord('A')] = chr(it + ord('A'))
    return rev_rotor

def turn(rotor):
    rotor.append(rotor[0])
    del(rotor[0])

def encrypt(message, init_pos: tuple):
    ciphered = ''
    n_rotor1 = rotor1[:]
    n_rotor2 = rotor2[:]
    # coloca os rotores na posição inicial
    for pos, rotor in zip(init_pos, (n_rotor1, n_rotor2)):
        assert (type(pos) == int) and (1 <= pos <= 26), "A posição inicial do rotor deve ser entre 1 e 26"
        pos -= 1
        for _ in range(pos):
            turn(rotor)
    rev_rotor1 = reverse(n_rotor1)
    rev_rotor2 = reverse(n_rotor2)
    rot2 = init_pos[1] - 1
    for letter in message:
        if letter in ascii_uppercase:
            pos = ord(letter) - ord('A')
            for rotor in (n_rotor2, n_rotor1):
                pos = ord(rotor[pos]) - ord('A')
            reflect_letter = chr(pos + ord('A'))
            pos = ord(reflector[reflect_letter]) - ord('A')
            pos = ord(rev_rotor1[pos]) - ord('A')
            ciphered += rev_rotor2[pos]
            turn(n_rotor2)
            rev_rotor2 = reverse(n_rotor2)
            rot2 += 1
            if rot2 == 26:
                rot2 = 0
                turn(n_rotor1)
                rev_rotor1 = reverse(n_rotor1)
        else:
            ciphered += letter
    return ciphered

def main():

    ciphertext = "I XKOFEMBS JPLU Y FATF, S CUXAHLXH W LCKT XHDV É (CMOOPTZX G FMUV)"

    for i in range(1,27):
        for j in range(1,27):
            pos1 = i
            pos2 = j
            print("Plaintext:", encrypt(ciphertext, (pos1, pos2)))

    # pos1 = int(input("Posição inicial do primeiro rotor: "))
    # pos2 = int(input("Posição inicial do segundo rotor: "))
    # ciphertext = input("Ciphertext: ").upper()
    # print("Plaintext:", encrypt(ciphertext, (pos1, pos2)))

def mappings():
    letter = 'U'
    print(f"Resultado de encriptar/decriptar a letra {letter} com todas as posições iniciais:")
    print("Rotor 1 | Rotor 2 | Resultado")
    for pos1 in range(1, 27):
        for pos2 in range(1, 27):
            result = encrypt(letter, (pos1, pos2))
            print(str(pos1).center(8), str(pos2).center(9), result.center(10))

if __name__ == '__main__':
    main()
