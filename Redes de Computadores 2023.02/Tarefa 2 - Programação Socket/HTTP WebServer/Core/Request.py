class Request:
    RAW: str = ''
    HEADERS: dict = {}
    BODY: dict = {}

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
            self.HEADERS[HEADER] = VALUE
            contador += 1
        
        return contador
