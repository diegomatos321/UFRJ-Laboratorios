import pulp

class MastermindSolver:
    problem: pulp.LpProblem
    x: list[list[pulp.LpVariable]]
    tips: int = 0
    positions: range # Posições da senha
    colors: range # Cores possíveis
    colorMap: dict[int, str] = {
        0: "Vermelho",
        1: "Azul",
        2: "Amarelo",
        3: "Verde",
        4: "Rosa"    
    }

    def __init__(self, positionsLen: int = 4, colorsLen: int = 5) -> None:
        self.problem = pulp.LpProblem("Mastermind_Solver", pulp.LpMinimize)
        self.positions = range(positionsLen)
        self.colors = range(colorsLen)

        # Variáveis de decisão: x[i][j] = 1 se a posição i tem a cor j, 0 caso contrário
        self.x = [[pulp.LpVariable(f"x_{i}_{j}", cat="Binary") for j in self.colors] for i in self.positions]
        
        # Restrição 1: Cada posição tem exatamente uma cor
        for i in self.positions:
            self.problem += pulp.lpSum(self.x[i][j] for j in self.colors) == 1, f"One_Color_Per_Position_{i}"

        # Restrição 2: Cada cor aparece no máximo uma vez na senha
        for j in self.colors:
            self.problem += pulp.lpSum(self.x[i][j] for i in self.positions) <= 1, f"Unique_Color_{j}"

    def NewTip(self, guess: list[int], rightColors: int, blacks: int, whites: int) -> None:
        self.problem +=(
            pulp.lpSum(
                self.x[i][j] 
                for i in self.positions
                for j in guess
            ) == rightColors
        )

        self.problem += (
            pulp.lpSum(self.x[i][guess[i]] for i in self.positions) == blacks,
            f"Feedback_Black_{self.tips}",
        )

        self.problem += (
            pulp.lpSum(
                self.x[i][j]
                for i in self.positions
                for j in self.colors
                if j in guess and j != guess[i]
            )
            == whites,
            f"Feedback_White_{self.tips}",
        )

        self.tips += 1

    def Run(self) -> None:
        # Função objetivo arbitrária (queremos apenas satisfazer as restrições)
        self.problem += 0, "Objective"

        # Resolver o problema
        self.problem.solve()

        # Mostrar os resultados
        if pulp.LpStatus[self.problem.status] == "Optimal":
            solution = [[int(self.x[i][j].varValue) for j in self.colors] for i in self.positions]
            senha = [self.colorMap[self.colors.index(row.index(1))] for row in solution]
            print("Solução encontrada (índices das cores):", senha)
        else:
            print("Nenhuma solução encontrada.")
