let grid;
let gridColumnsNumber;
let gridRowsNumber;
let gridResolution = 20;
let fps = 10;
let canvasWidth = 1920;
let canvasHeight = 1080;

function setup() {
    createCanvas(canvasWidth, canvasHeight);
    gridColumnsNumber = width / gridResolution;
    gridRowsNumber = height / gridResolution;

    grid = create2DArray(gridColumnsNumber, gridRowsNumber);
    fill2DArray();
}

function mousePressed() {
    console.log(mouseX, mouseY);
    if((mouseX > 0 && mouseX < canvasWidth) && (mouseY > 0 && mouseY < canvasHeight)) {
        let x = Math.floor(mouseX / gridResolution);
        let y = Math.floor(mouseY / gridResolution);
        grid[x][y] = 1;
        console.log("x: " + x);
                console.log("y: " + x);
    }
}

function draw() {
    background(255);
    frameRate(fps);
    let nextGrid = create2DArray(gridColumnsNumber, gridRowsNumber);
    //narysuj obecny grid
    for (let x = 0; x < gridColumnsNumber; x++) {
        for (let y = 0; y < gridRowsNumber; y++) {
            let rectX = x * gridResolution;
            let rectY = y * gridResolution;
            if(grid[x][y] === 1) {
                fill(0);
                stroke(255);
                rect(rectX, rectY, gridResolution, gridResolution);
            }
        }
    }


    for (let x = 0; x < gridColumnsNumber; x++) {
        for (let y = 0; y < gridRowsNumber; y++) {
            let currentState = grid[x][y];

            let sum = sumOfNeighbours(grid, x, y);

            if(currentState === 0 && sum === 3) { //BIRTH
                nextGrid[x][y] = 1;
            } else if (currentState === 1 && (sum >= 4 || sum <= 1)) { //DEATH
                nextGrid[x][y] = 0;
            } else { //STATIS
                nextGrid[x][y] = currentState;
            }
        }
    }
    grid = nextGrid;
}

function create2DArray(x, y) {
    let array = new Array(x);
    for(let i = 0; i < array.length; i++) {
        array[i] = new Array(y);
    }
    return array;
}

function fill2DArray() {
    for (let x = 0; x < gridColumnsNumber; x++) {
        for (let y = 0; y < gridRowsNumber; y++) {
            grid[x][y] = 0;
        }
    }
    grid[0][4] = 1;
    grid[0][5] = 1;
    grid[1][4] = 1;
    grid[1][5] = 1;

    grid[10][4] = 1;
    grid[10][5] = 1;
    grid[10][6] = 1;
    grid[11][3] = 1;
    grid[11][7] = 1;
    grid[12][2] = 1;
    grid[12][8] = 1;
    grid[13][2] = 1;
    grid[13][8] = 1;
    grid[14][5] = 1;
    grid[15][3] = 1;
    grid[15][7] = 1;
    grid[16][4] = 1;
    grid[16][5] = 1;
    grid[16][6] = 1;
    grid[17][5] = 1;

    grid[20][2] = 1;
    grid[20][3] = 1;
    grid[20][4] = 1;
    grid[21][2] = 1;
    grid[21][3] = 1;
    grid[21][4] = 1;
    grid[22][1] = 1;
    grid[22][5] = 1;
    grid[24][0] = 1;
    grid[24][1] = 1;
    grid[24][5] = 1;
    grid[24][6] = 1;

    grid[34][2] = 1;
    grid[34][3] = 1;
    grid[35][2] = 1;
    grid[35][3] = 1;
}

function sumOfNeighbours(grid, x, y) {
    let sum = 0;
    for (let i = -1; i < 2; i++) {
        for (let j = -1; j < 2; j++) {
            let col = (x + i + gridColumnsNumber) % gridColumnsNumber; //modulo kolumny poza brzegiem == 0
            let row = (y + j + gridRowsNumber) % gridRowsNumber;
            sum += grid[col][row];
        }
    }
    sum -= grid[x][y];
    return sum;
}