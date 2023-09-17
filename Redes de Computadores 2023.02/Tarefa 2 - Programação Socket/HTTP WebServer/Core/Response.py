from typing import Self

class Response:
    HEADERS: dict = {}
    BODY: str|None = None

    def __init__(self) -> None:
        self.HEADERS['PROTOCOL'] = 'HTTP/1.1'
        self.HEADERS['Connection'] = "close"
    
    def Succesfull(self) -> Self:
        self.HEADERS['STATUS_CODE'] = '200'
        self.HEADERS['STATUS_MESSAGE'] = 'OK'

        return self

    def NotFound(self) -> Self:
        self.HEADERS['STATUS_CODE'] = '404'
        self.HEADERS['STATUS_MESSAGE'] = 'Not Found'

        return self
    
    def Unauthorized(self) -> Self:
        self.HEADERS['STATUS_CODE'] = '401'
        self.HEADERS['STATUS_MESSAGE'] = 'Unauthorized'

        return self

    def Redirect(self, to: str) -> Self:
        self.HEADERS['STATUS_CODE'] = '301'
        self.HEADERS['STATUS_MESSAGE'] = 'Moved Permanently'
        self.HEADERS['Location'] = to

        return self

    def Content(self, filePath: str, extension: str, format: str) -> Self:
        body = open(filePath, encoding=format).read()

        self.HEADERS['Content-Length'] = str(len(body.encode(format)))

        if extension == '.js':
            self.HEADERS['Content-Type'] = 'text/javascript; charset=' + format
        elif extension == '.css':
            self.HEADERS['Content-Type'] = 'text/css; charset=' + format
        elif extension == '.html':
            self.HEADERS['Content-Type'] = 'text/html; charset=' + format
        
        self.BODY = body

        return self
    