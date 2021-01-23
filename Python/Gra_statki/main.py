def getInputFromPlayer():
    try:
        playerInputX = int(input("Podaj współrzędną x punktu, gdzie chcesz strzelić:\n"))
        playerInputY = int(input("Podaj współrzędną y punktu, gdzie chcesz strzelić:\n"))
    except ValueError:
        print("Błąd. Podane współrzędne muszą być typu int!")
    else:
        return (playerInputX, playerInputY)

def renderBoardRowByRow(boardWidth, boardHeight, shots, battleships):
    shotsSet = set(shots) #zbiór, żeby shots nie zawierał duplikatów + nie zachowuje kolejności listy (działa szybciej)
    print("\n")
    # print(battleships)
    # render top of board
    topOfBoard = "   "
    for i in range(1, boardWidth+1):
        topOfBoard += str(i) + " "
    print(topOfBoard)

    for y in range(1, boardHeight+1):
        # czy nie lepiej jest zrobić listę 2 na 2, bo teraz muszę sprawdzać każdy rząd dwa razy dla statków i strzałów
        row = []

        # render left column of numbers
        if(y < 10):
            row.append(str(y) + " ")
        else:
            row.append(str(y))

        # add '.' to row
        for x in range(1, boardWidth+1):
            row.append(".")

        #  render all battleships
        for x in range(1, boardHeight+1):
            for i in range(len(battleships)): #wybiera statek
                for j in range(len(battleships[i].coordinatesList)): #wybiera krotke
                        if battleships[i].coordinatesList[j][1] == y:
                            # render front and back of the ship
                            if (j == 0 and battleships[i].direction == "UP") or (j == len(battleships[i].coordinatesList)-1 and battleships[i].direction == "DOWN"):
                                row[battleships[i].coordinatesList[j][0]] = "▼"
                            elif (j == 0 and battleships[i].direction == "DOWN") or (j == len(battleships[i].coordinatesList)-1 and battleships[i].direction == "UP"):
                                row[battleships[i].coordinatesList[j][0]] = "▲"
                            elif (j == 0 and battleships[i].direction == "LEFT") or (j == len(battleships[i].coordinatesList)-1 and battleships[i].direction == "RIGHT"):
                                row[battleships[i].coordinatesList[j][0]] = "▶"
                            elif (j == 0 and battleships[i].direction == "RIGHT") or (j == len(battleships[i].coordinatesList)-1 and battleships[i].direction == "LEFT"):
                                row[battleships[i].coordinatesList[j][0]] = "◀"
                            else:
                                row[battleships[i].coordinatesList[j][0]] = "█"

        # render all shots
        for x in range(1, boardWidth+1):
            if(x, y) in shotsSet:
                row[x] = "X"

        print(" ".join(row))

    print("\n")

def renderBoard2DList(boardWidth, boardHeight, shots, battleships):
    boardList = [[' ' for x in range(boardWidth+1)] for y in range(boardHeight+1)]

    # topOfBoard
    for i in range(1, boardWidth+1):
        boardList[0][i] = i

    # column of numbers
    for i in range(1, boardHeight+1):
        boardList[i][0] = i
    
    # add '.' to board
    for y in range (1, boardHeight+1):
        for x in range(1, boardWidth+1):
            boardList[y][x] = "."

    # print boardList
    for y in range(boardHeight+1):
        # print(boardList[y][x], sep=" ", end="")
        # print(" ".join(boardList[y]))
        print(*boardList[y])

        # render left column of numbers
        # if(y < 10):
        #     print(boardList[y][0], sep="  ")
        # else:
        #     print(boardList[y][0], sep=" ")

        


        # print("\n")


class Battleship():
    # coordinatesList = [] #w ten sposób lista jest dzielona pomiedzy wszystkie instacje obiektów battleship...

    def __init__(self, startingPoint, length, direction):
        self.startingPoint = startingPoint
        self.length = length
        self.direction = direction
        self.coordinatesList = []
        self.buildBattleship()

    def buildBattleship(self):
        for i in range(self.length):
            if self.direction == "UP":
                coordinate = (self.startingPoint[0], self.startingPoint[1] - i)
            elif self.direction == "DOWN":
                coordinate = (self.startingPoint[0], self.startingPoint[1] + i)
            elif self.direction == "LEFT":
                coordinate = (self.startingPoint[0] - i, self.startingPoint[1])
            elif self.direction == "RIGHT":
                coordinate = (self.startingPoint[0] + i, self.startingPoint[1])
            
            self.coordinatesList.append(coordinate)



def main():
    # █
    battleships = [
        Battleship((1, 3), 4, "DOWN"),
        Battleship((1, 1), 2, "RIGHT"),
        Battleship((6, 6), 3, "UP"),
        Battleship((10, 10), 5, "LEFT")
    ]
    allShots = []
    # game loop
    while 1:
        myShot = getInputFromPlayer()
        allShots.append(myShot)
        renderBoardRowByRow(10, 10, allShots, battleships)
        # renderBoard2DList(10, 10, allShots, battleships)


if __name__ == "__main__":
    main()
