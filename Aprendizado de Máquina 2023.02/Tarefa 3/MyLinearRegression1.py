import numpy as np

def MyLinearRegression(dataframe: np.ndarray[np.ndarray[float]]):
    count_pontos = len(dataframe) # Pontos que devem ser melhor ajustados ao modelo
    count_features = len(dataframe[0]) - 1 # Último elemento é o y
    
    X = np.ones(shape=(count_pontos, count_features + 1))
    Y = np.zeros(shape=(count_pontos, 1), dtype=float)

    for i in range(count_pontos):
        pontos = dataframe[i]
        X[i][1:] = pontos[:count_features]
        Y[i] = pontos[count_features]

    result0 = np.dot(X.T, X)
    result0 = np.linalg.inv(result0)
    result1 = np.dot(X.T, Y)
    result = np.dot(result0, result1)
    return result