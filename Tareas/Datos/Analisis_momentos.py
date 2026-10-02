


def leer():
    user_input = input("Datos en formato [n,..]: ")
    nums = user_input[1:-1].split(',')
    return [int(n) for n in nums]

def media(nums : list[int]):
    return( sum(nums)/len(nums))

def varianza(nums : list[int]):
    promedio = media(nums)
    return sum((x - promedio) ** 2 for x in nums) / (len(nums) - 1)

def probabilidades(nums : list[int]):
    dic = {}
    for n in nums:
        if dic.get(n): 
            dic[n]+=1
        else:
            dic[n] = 1
    tot = len(nums)
    for key in dic.keys():
        dic[key] = dic[key] / tot
    return dic

def momento(nums: list[int], orden: int):
    promedio = media(nums)
    return sum((x - promedio) ** orden for x in nums) / len(nums)

def main():
    nums = leer()
    print(" Probabilidades  ")
    print(probabilidades(nums))
    print(" Momento estadistico 1  ")
    print(momento(nums,1))
    print(" Momento estadistico 2  ")
    print(momento(nums,3))
    print(" Varianza  ")
    print(varianza(nums))
    print(" Momento estadistico 3  ")
    print(momento(nums,2))
    print(" Momento estadistico 4  ")
    print(momento(nums,4))
    #print(" Media  ")
    #print(media(nums))
    #print(" Momento estadistico 0  ")
    #print(momento(nums,0))
main()


"""
Momento 0: siempre es igual a 1 y está relacionado con el hecho de que la suma de todas las probabilidades de una distribución debe ser igual a 1.
Momento 1: corresponde al valor esperado o media, e indica el valor alrededor del cual se concentran los datos.
Momento 2: permite obtener información sobre la dispersión de los datos y se utiliza para calcular la varianza.
Momento 3: está relacionado con la asimetría, es decir, permite analizar si una distribución presenta mayor concentración hacia alguno de sus lados.
Momento 4: está relacionado con la curtosis, la cual permite estudiar qué tan concentrada o aplanada es una distribución y el comportamiento de sus colas.
"""
