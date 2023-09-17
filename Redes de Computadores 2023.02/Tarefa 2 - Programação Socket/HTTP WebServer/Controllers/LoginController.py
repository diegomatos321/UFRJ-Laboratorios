from Core.Request import Request
from Core.Response import Response

class LoginController:
    def __init__(self) -> None:
        pass

    def Submit(self, request: Request) -> Response:
        if request.BODY['nome'] == 'Diego' and request.BODY['senha'] == '123456':
            return Response().Redirect(to='privado.html')
        else:
            return Response().Unauthorized()