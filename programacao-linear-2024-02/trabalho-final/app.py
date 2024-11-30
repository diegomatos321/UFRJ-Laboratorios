from MastermindSolver import MastermindSolver

solver = MastermindSolver(colorsLen=5)
solver.NewTip([0, 1, 2, 3], 3, 2, 1)
solver.NewTip([0, 1, 3, 4], 4, 1, 3)
solver.NewTip([0, 3, 1, 4], 4, 0, 4)
solver.Run()