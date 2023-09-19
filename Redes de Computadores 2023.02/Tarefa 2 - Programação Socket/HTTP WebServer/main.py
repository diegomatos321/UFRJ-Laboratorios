'''
    Tarefa 02 - Disciplina Redes de Computadores 2023.02
    Professora: Carolina Gil Marcelino
    Alunos: 
        Diego Vasconcelos Schardosim de Matos - 120098723
        Gabriel Trindade Corrêa               - 120019606
'''

from Core.Kernel import MyServer as HTTPWebServer

server = HTTPWebServer()
server.Listen(8080)