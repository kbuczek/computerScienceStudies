let grid;
let gridColumnsNumber;
let gridRowsNumber;
let gridResolution = 10;

// var ruleset = [0, 1, 0, 1, 1, 0, 1, 0]; //rule 90
var ruleset = [1, 1, 0, 1, 1, 1, 1, 0];  //rule 222
// var ruleset = [1, 0, 1, 1, 1, 1, 0, 0];  //rule 188
// var ruleset = [0, 1, 0, 1, 1, 1, 1, 0];  //rule 94
// var ruleset = [1, 0, 0, 1, 0, 1, 1, 0];  //rule 150
// var ruleset = [0, 0, 0, 1, 1, 1, 1, 0];  //rule 30

let generation;
const canvasHeight = 11500;
const canvasWidth = 1500;
let render;

function setup() {
    createCanvas(canvasWidth, canvasHeight);
    gridColumnsNumber = width / gridResolution;
    gridRowsNumber = height / gridResolution;
    grid = new Array(gridColumnsNumber);
    render = create2DArray(gridColumnsNumber, gridRowsNumber);
    resetGrid();
    grid[Math.floor(grid.length/2)] = 1; //środek
    generation = 0;
}

function draw() {
    background(255);
    frameRate(200);
    let nextGrid = new Array(gridColumnsNumber);

    for(let j = 0; j < grid.length; j++) {
        if(grid[j] === 1)  {
            render[j][generation] = 1;
        }
    }

    for(let i = 0; i < gridColumnsNumber; i++) {
        for(let j = 0; j < gridRowsNumber; j++) {
            let rectX = i * gridResolution;
            let rectY = j * gridResolution;
            if(render[i][j] === 1) {
            fill(0);
            stroke(255);
            rect(rectX, rectY, gridResolution, gridResolution);
            }
        }
    }

    for(let i = 1; i < gridColumnsNumber; i++) {
        let left = grid[i-1];
        let center = grid[i];
        let right = grid[i+1];
        nextGrid[i] = rules(left, center, right); 
    }

    grid = nextGrid;
    generation++;
}

function resetGrid() {
    for (let x = 0; x < gridColumnsNumber; x++) {
        grid[x] = 0;
    }
}

function create2DArray(x, y) {
    let array = new Array(x);
    for(let i = 0; i < array.length; i++) {
        array[i] = new Array(y);
    }
    return array;
}

function rules (a, b, c) {
    if (a == 1 && b == 1 && c == 1) return ruleset[0];
    if (a == 1 && b == 1 && c == 0) return ruleset[1];
    if (a == 1 && b == 0 && c == 1) return ruleset[2];
    if (a == 1 && b == 0 && c == 0) return ruleset[3];
    if (a == 0 && b == 1 && c == 1) return ruleset[4];
    if (a == 0 && b == 1 && c == 0) return ruleset[5];
    if (a == 0 && b == 0 && c == 1) return ruleset[6];
    if (a == 0 && b == 0 && c == 0) return ruleset[7];
    return 0;
}
