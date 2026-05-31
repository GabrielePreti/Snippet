mia_lista = [("banana", 3), ("mela", 5), ("ciliegia", 2)]
mia_lista.append(("albicocca", 4))

lista_ordinata = sorted(mia_lista, key=lambda x: x[1]) 
#modificando key=lambda x: x[value] -> value cambia su cosa ordinare

for i, k in lista_ordinata:
    print(f"{i}, {k}")
