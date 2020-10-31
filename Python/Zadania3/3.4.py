while True:
    x = input("Podaj liczbę rzeczywistą: ")
    try:
        if float(x):
            x = float(x)
        print(f"{x} {x**3}\n")
    except ValueError:
        print("To nie jest liczba typu float!")
        if x == "stop":
            break
        else:
            continue


