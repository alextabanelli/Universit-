//Funzione di fibonacci iterativa

output = [];

function fibonacciIterativa(n) {
    if (n <= 0) return 0;
    if (n === 1) return 1;
    output.push(0);
    output.push(1);

    let a = 0;
    let b = 1;
    let c;

    for (let i = 2; i <= n; i++) {
        c = a + b;
        output.push(c);
        a = b;
        b = c;
    }

    return output;
}

function displayFibonacci(n) {
    var input = document.getElementById("input").value;
    var result = fibonacciIterativa(parseInt(input));
    var output = document.getElementById("output");
    output.innerHTML = result;
}