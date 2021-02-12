import random
battleshipWasHitNumber = 0

def getInputFromPlayer():
    try:
        playerInputX = int(input("Podaj współrzędną x punktu, gdzie chcesz strzelić:\n"))

        playerInputY = int(input("Podaj współrzędną y punktu, gdzie chcesz strzelić:\n"))
        print("\n")
    except ValueError:
        print("Błąd. Podane współrzędne muszą być typu int!")
    else:
        return (playerInputX, playerInputY)

class Battleship():

    def __init__(self, startingPoint, length, direction):
        self.startingPoint = startingPoint
        self.length = length
        self.direction = direction
        self.coordinatesList = []
        self.hitDetetction = [False] * length
        self.createBattleship()

    def createBattleship(self):
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

    def isDestroyed(self):
        for i in self.hitDetetction:
            if not i:
                return False
        return True

# logic and state of the game
class Game():

    def __init__(self, boardWidth, boardHeight):
        self.boardWidth = boardWidth
        self.boardHeight = boardWidth
        self.allShots = {} #słownik - zawiera pary ((lokX, lokY), isHit)
        self.battleships = [];

    def addBattleship(self, battleship):
        for i in battleship.coordinatesList:
            # check range
            if (i[0] < 1) or (i[0] > self.boardWidth):
                return False
            if (i[1] < 1) or (i[1] > self.boardHeight):
                return False
            
            # check collisions with other battleships
            for j in self.battleships:
                for k in j.coordinatesList:
                    if (i[0] == k[0]) and (i[1] == k[1]):
                        return False

        self.battleships.append(battleship)
        return True

    def placeRandomBattleships(self, numOf5=1, numOf4=2, numOf3=3, numOf2=3):
        self.placeRandomBattleshipOfType(numOf5, 5)
        self.placeRandomBattleshipOfType(numOf4, 4)
        self.placeRandomBattleshipOfType(numOf3, 3)
        self.placeRandomBattleshipOfType(numOf2, 2)

    def placeRandomBattleshipOfType(self, numberOfShips, battleshipLength):
        directionsList = ["LEFT", "RIGHT", "DOWN", "UP"]
        battleshipAddSuccess = False

        for i in range(numberOfShips):
            while not battleshipAddSuccess:
                randomStartingPointX = random.randrange(1, self.boardWidth+1)
                randomStartingPointY = random.randrange(1, self.boardHeight+1)
                randomDirection = random.randrange(0, 4)
                randomDirection = directionsList[randomDirection]
                if self.addBattleship(Battleship((randomStartingPointX, randomStartingPointY), battleshipLength, randomDirection)):
                    battleshipAddSuccess = True
            battleshipAddSuccess = False  

    def shotIsCorrect(self, myShot):
        if (myShot[0] < 1) or (myShot[0] > self.boardWidth):
            return False
        if (myShot[1] < 1) or (myShot[1] > self.boardHeight):
            return False
        if myShot in self.allShots:
            return False
        return True

    def shoot(self, myShot):

        isHit = False
        for Battleship in self.battleships:
            if myShot in Battleship.coordinatesList:
                isHit = True
                print("Trafiony!")
                try:
                    myShotIndex = Battleship.coordinatesList.index(myShot)
                except ValueError:
                    print("Nie znaleziono indeksu twojego trafienia w Battleship")
                Battleship.hitDetetction[myShotIndex] = isHit
                if Battleship.isDestroyed():
                    self.battleships.remove(Battleship)
                    print("Trafiony zatopiony!")
                break

        self.allShots[myShot] = isHit
        return isHit

    def isOver(self):
        if self.battleships:
            return False

        # print("Brawo! Wygrałeś grę!")
        return True
            
def renderBoardRowByRow(game, showBattleships=True):
    print("\n")

    # render top of board
    topOfBoard = "   "
    for i in range(1, game.boardWidth+1):
        topOfBoard += str(i) + " "
    print(topOfBoard)

    for y in range(1, game.boardHeight+1):
        row = []

        # render left column of numbers
        if(y < 10):
            row.append(str(y) + " ")
        else:
            row.append(str(y))

        # add '.' to row
        for x in range(1, game.boardWidth+1):
            row.append("_")

        #  render all battleships
        if showBattleships:
            for x in range(1, game.boardHeight+1):
                for i in range(len(game.battleships)):  # wybiera statek
                    for j in range(len(game.battleships[i].coordinatesList)): # wybiera krotke
                            if game.battleships[i].coordinatesList[j][1] == y:
                                # render front and back of the ship
                                if (j == 0 and game.battleships[i].direction == "UP") or (j == len(game.battleships[i].coordinatesList)-1 and game.battleships[i].direction == "DOWN"):
                                    row[game.battleships[i].coordinatesList[j][0]] = "v"
                                elif (j == 0 and game.battleships[i].direction == "DOWN") or (j == len(game.battleships[i].coordinatesList)-1 and game.battleships[i].direction == "UP"):
                                    row[game.battleships[i].coordinatesList[j][0]] = "^"
                                elif (j == 0 and game.battleships[i].direction == "LEFT") or (j == len(game.battleships[i].coordinatesList)-1 and game.battleships[i].direction == "RIGHT"):
                                    row[game.battleships[i].coordinatesList[j][0]] = ">"
                                elif (j == 0 and game.battleships[i].direction == "RIGHT") or (j == len(game.battleships[i].coordinatesList)-1 and game.battleships[i].direction == "LEFT"):
                                    row[game.battleships[i].coordinatesList[j][0]] = "<"
                                else:
                                    row[game.battleships[i].coordinatesList[j][0]] = "#"
                                    
        # render all shots
        for x in range(1, game.boardWidth+1):
            if(x, y) in game.allShots:
                if game.allShots.get((x, y)) == False:
                    row[x] = "O"
                else:
                    row[x] = "X"

        print(" ".join(row))

    print("\n")

def getInputFromComputer(battleshipWasHit, computerLastHits, game):
    lastShot = computerLastHits[-1]
    if battleshipWasHit:
        randomDirX, randomDirY = 1000, 1000 #must be bigger than boardWidth and boardHeight
        # shoot close to last hit (+- 1) and check if next shot is inside the board
        while (lastShot[0] + randomDirX < 1) or (lastShot[0] + randomDirX > game.boardWidth) or (lastShot[1] + randomDirY < 1) or (lastShot[1] + randomDirY > game.boardWidth) or ((lastShot[0] + randomDirX, lastShot[1] + randomDirY) in game.allShots):
            randomDirX = random.randrange(-1, 2)
            if randomDirX == 0:
                randomDirY = random.randrange(-1, 2, 2)
            else:
                randomDirY = 0;
        return (lastShot[0] + randomDirX, lastShot[1] + randomDirY)
    else:
        return (random.randrange(1, game.boardWidth+1), random.randrange(1, game.boardWidth+1))


def getInputFromComputer2(battleshipWasHit, computerLastHits, game):
    global battleshipWasHitNumber

    lastShot = computerLastHits[-1]
    print(lastShot)
    # check which battleship was hit
    if battleshipWasHit:
        for Battleship in game.battleships:
            for i in Battleship.hitDetetction:
                if i == True:
                    battleshipWasHitNumber = Battleship
                    break

    print(battleshipWasHitNumber)

    # if the hit battleship wasn't destroyed
    if battleshipWasHitNumber:
        # must be bigger than boardWidth and boardHeight
        randomDirX, randomDirY = 1000, 1000

        sumOfDirectionsHit = 0
        # check if all directions are already shot
        if (lastShot[0] + 1, lastShot[1] + 0) in game.allShots:
            sumOfDirectionsHit += 1
        if (lastShot[0] - 1, lastShot[1] + 0) in game.allShots:
            sumOfDirectionsHit += 1
        if (lastShot[0] + 0, lastShot[1] + 1) in game.allShots:
            sumOfDirectionsHit += 1
        if (lastShot[0] + 0, lastShot[1] - 1) in game.allShots:
            sumOfDirectionsHit += 1

        if sumOfDirectionsHit == 4:
            del computerLastHits[-1]
            lastShot = computerLastHits[-1]
            
        # shoot close to last hit (+- 1) and check if next shot is inside the board
        while (lastShot[0] + randomDirX < 1) or (lastShot[0] + randomDirX > game.boardWidth) or (lastShot[1] + randomDirY < 1) or (lastShot[1] + randomDirY > game.boardWidth) or ((lastShot[0] + randomDirX, lastShot[1] + randomDirY) in game.allShots):
            randomDirX = random.randrange(-1, 2)
            if randomDirX == 0:
                randomDirY = random.randrange(-1, 2, 2)
            else:
                randomDirY = 0
        return (lastShot[0] + randomDirX, lastShot[1] + randomDirY)
    else:
        return (random.randrange(1, game.boardWidth+1), random.randrange(1, game.boardWidth+1))

def playerVsPlayer():
    boardWidth, boardHeight = 10, 10
    computerLastHit = (0, 0)

    game1 = Game(boardWidth, boardHeight)
    game1.placeRandomBattleships()

    game2 = Game(boardWidth, boardHeight)
    game2.placeRandomBattleships()

    while 1:
        game1IsHit, game2IsHit = True, True
        game1IsOver, game2IsOver = False, False

        print("KOLEJ GRACZA 1")
        while game1IsHit and not game1IsOver:
            myShot1 = getInputFromPlayer()

            if not game1.shotIsCorrect(myShot1):
                print("Nieprawidłowy strzał. Powtórz ruch!")
                game1IsHit = True
            else:
                game1IsHit = game1.shoot(myShot1)

            if not game1IsHit:
                print("Pudło!")

            renderBoardRowByRow(game1, False)
            game1IsOver = game1.isOver()

        if game1IsOver:
            print("Brawo! Gracz 1 wygrał grę.")
            break

        print("KOLEJ GRACZA 2")
        while game2IsHit and not game2IsOver:
            myShot2 = getInputFromPlayer()

            if not game1.shotIsCorrect(myShot1):
                print("Nieprawidłowy strzał. Powtórz ruch!")
                game1IsHit=True
            else:
                game1IsHit = game1.shoot(myShot1)

            if not game2IsHit:
                print("Pudło!")

            renderBoardRowByRow(game2, False)
            game2IsOver = game2.isOver()

        if game2IsOver:
            print("Brawo! Gracz 2 wygrał grę.")
            break

def playerVsComputer():
    boardWidth, boardHeight = 10, 10
    computerLastHits = []
    computerLastHits.append((0,0))

    game1 = Game(boardWidth, boardHeight)
    game1.placeRandomBattleships()
    # game1.addBattleship(Battleship((1, 1), 2, "RIGHT"))

    game2 = Game(boardWidth, boardHeight)
    game2.placeRandomBattleships()
    # game2.addBattleship(Battleship((1, 1), 1, "RIGHT"))

    while 1:
        game1IsHit, game2IsHit = True, False
        game1IsOver, game2IsOver = False, False
        doWhileCondition = True

        print("KOLEJ GRACZA")
        while game1IsHit and not game1IsOver:
            myShot1 = getInputFromPlayer()

            if not game1.shotIsCorrect(myShot1):
                print("Nieprawidłowy strzał. Powtórz ruch!")
                game1IsHit=True
            else:
                game1IsHit = game1.shoot(myShot1)

            if not game1IsHit:
                print("Pudło!")

            renderBoardRowByRow(game1, False)
            game1IsOver = game1.isOver()

        if game1IsOver:
            print("Brawo! Wygrałeś grę!")
            break

        print("KOMPUTER ROBI RUCH")
        while doWhileCondition and not game2IsOver:
            myShot2 = getInputFromComputer(game2IsHit, computerLastHits, game2)
            game2IsHit = game2.shoot(myShot2)
            if game2IsHit:
                computerLastHits.append(myShot2)
            if not game2IsHit:
                print("Pudło!")
            renderBoardRowByRow(game2, True)
            game2IsOver = game2.isOver()
            doWhileCondition = game2IsHit

        if game2IsOver:
            print("Przegana :( Komputer wygrał grę!")
            break

def main():
    print("\nWitaj w grze battleships!")
    print("\'_\' oznacza puste miejsce")
    print("\'O\' oznacza puste pudło")
    print("\'X\' oznacza puste trafiony")
    print("\'#\', \'>\', \'<\', \'^\', \'v\' oznaczają twoje statki\n")

    playerVsComputer()
    # playerVsPlayer()

if __name__ == "__main__":
    main()
