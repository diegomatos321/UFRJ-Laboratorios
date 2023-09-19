import os
import json

class Request:
    RAW: str = ''
    HEADERS: dict = {}
    BODY: dict = {}
    COOKIES: dict = {}

    def __init__(self, parsedMessage: str) -> None:
        self.RAW = parsedMessage

        lines = parsedMessage.split("\r\n")
        endOfHeaders = self.getRequestHeaders(lines)
        
        if endOfHeaders < len(lines):
            # O método GET retorna duas linhas em branco
            # Verificando se a proxima não está em branco
            startOfBody = endOfHeaders + 1
            if lines[startOfBody] != '':
                contents = lines[startOfBody].split('&')

                for content in contents:
                    KEY, VALUE = content.split('=')
                    self.BODY[KEY] = VALUE

    def getRequestHeaders(self, lines: list[str]) -> int:
        METHOD, PATH, PROTOCOL = lines[0].split()

        self.HEADERS['METHOD'] = METHOD
        self.HEADERS['PATH'] = PATH
        self.HEADERS['PROTOCOL'] = PROTOCOL

        contador = 1
        for line in lines[1:]:
            if line == '':
                break
            
            HEADER, VALUE = line.split(': ')

            if HEADER == 'Cookie':
                cookieName, cookieValue = VALUE.split('=')
                self.COOKIES[cookieName] = cookieValue
                contador += 1
                continue

            self.HEADERS[HEADER] = VALUE
            contador += 1
        
        return contador

    def GetSessionKey(self, key: str, default = None):
        if self.COOKIES.get('__session') is None:
            return None

        sessionFile = open(os.path.join('sessions', self.COOKIES['__session']), encoding='UTF-8').read()
        
        if sessionFile == '':
            return default
        
        parsedFile = json.loads(sessionFile)
        
        return parsedFile[key]

    def SetSessionValue(self, key: str, value):
        if self.COOKIES.get('__session') is None:
            return None

        sessionFile = open(os.path.join('sessions', self.COOKIES['__session']), encoding='UTF-8').read()
        if sessionFile == '':
            parsedFile = {}
        else:
            parsedFile = json.loads(sessionFile)

        parsedFile[key] = value
        
        sessionFile = open(os.path.join('sessions', self.COOKIES['__session']), mode='w', encoding='UTF-8')
        sessionFile.write(json.dumps(parsedFile))
        sessionFile.close()