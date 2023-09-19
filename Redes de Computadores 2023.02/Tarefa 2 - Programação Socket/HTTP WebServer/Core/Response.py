from typing import Self
import datetime

class Response:
    HEADERS: dict = {}
    BODY: str|None = None
    COOKIES: dict = {}

    def __init__(self) -> None:
        self.HEADERS['PROTOCOL'] = 'HTTP/1.1'
        #self.HEADERS['Connection'] = "close"
        self.HEADERS['Connection'] = "keep-alive"
    
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
        if extension == '.js':
            body = open(filePath, encoding=format).read()
            self.HEADERS['Content-Length'] = str(len(body.encode(format)))
            self.HEADERS['Content-Type'] = 'text/javascript; charset=' + format
        elif extension == '.css':
            body = open(filePath, encoding=format).read()
            self.HEADERS['Content-Length'] = str(len(body.encode(format)))
            self.HEADERS['Content-Type'] = 'text/css; charset=' + format
        elif extension == '.html':
            body = open(filePath, encoding=format).read()
            self.HEADERS['Content-Length'] = str(len(body.encode(format)))
            self.HEADERS['Content-Type'] = 'text/html; charset=' + format
        elif extension == '.svg':
            body = open(filePath, mode='rb').read()
            self.HEADERS['Content-Length'] = str(len(body))
            self.HEADERS['Content-Type'] = 'image/svg+xml; charset=' + format
        elif extension == '.png':
            body = open(filePath, mode='rb').read()
            self.HEADERS['Content-Length'] = str(len(body))
            self.HEADERS['Content-Type'] = 'image/png; charset=' + format
        elif extension == '.jpg':
            body = open(filePath, mode='rb').read()
            self.HEADERS['Content-Length'] = str(len(body))
            self.HEADERS['Content-Type'] = 'image/jpg; charset=' + format
        
        self.BODY = body

        return self
    
    def SetCookie(self, key:str, value:str, ttl:int = 0) -> Self:
        timestamp = datetime.datetime.now() + datetime.timedelta(minutes=ttl)

        self.COOKIES[key] = {
            'key': key,
            'value': value,
            'ttl': str(timestamp.timestamp())
        }

        return self
    