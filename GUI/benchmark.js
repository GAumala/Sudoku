const spawn = require('child_process').spawn;
const clocks = [
  [3, 1, 3, 1, 2, 3],
  [3, 1, 3, 1, 2, 3],

  [1, 1, 3, 4, 3, 1, 3, 3, 2, 2],
  [1, 1, 3, 4, 3, 1, 3, 3, 2, 2],

  [3, 1, 3, 5, 2, 5, 1, 2, 3, 5],
  [3, 1, 3, 5, 2, 5, 1, 2, 3, 5],

  [6, 5, 1, 4, 2, 1, 6, 4, 2, 1, 5, 2],
  [6, 5, 1, 4, 2, 1, 6, 4, 2, 1, 5, 2],

  [6, 4, 2, 1, 4, 1, 3, 6, 5, 1, 3, 2, 1],
  [6, 4, 2, 1, 4, 1, 3, 6, 5, 1, 3, 2, 1],
]
let i = 0

function runTest(){
    let index = i
    let algorithmName = "brute"
    if(i % 2 === 1){
        algorithmName = "main"
    }
    const startTime = new Date().getTime()
    console.log(`Run test with ${algorithmName} on ${clocks[index]}`)
    const algoritmo = spawn("../" + algorithmName, ["-i"].concat(clocks[index]));


    algoritmo.stdout.on('data', (data) => {
        console.log(data.toString('utf-8'));
    })


    algoritmo.on('close', (code) => {
        const endTime = new Date().getTime()
        const diff = endTime - startTime
        console.log(algorithmName + ":\t" + diff + " ms.")
        i++;

        if(i < clocks.length) runTest()
    })
}

const p1 = spawn("../main");
p1.on('close', (code) => {
    const p2 = spawn("../brute");
    p2.on('close', (code) => {
        runTest()
    })
})
