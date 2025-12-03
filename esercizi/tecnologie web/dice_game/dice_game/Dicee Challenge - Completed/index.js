


let randomNumber1 = Math.floor(Math.random() * 6) + 1;
let randomNumber2 = Math.floor(Math.random() * 6) + 1;

console.log("Giocatore 1: " + randomNumber1);
console.log("Giocatore 2: " + randomNumber2);

let image1path = "images/dice" + randomNumber1 + ".png";
let image2path = "images/dice" + randomNumber2 + ".png";

console.log("Paths: " + image1path + " " + image2path);

let image1 = document.querySelector(".img1");
let image2 = document.querySelector(".img2");


image1.setAttribute("src", image1path);
image2.setAttribute("src", image2path);

let title = document.querySelector("h1");

if (randomNumber1 > randomNumber2) {
    title.innerHTML = "🚩 Giocatore 1 vince!";
} else if (randomNumber1 < randomNumber2) {
    title.innerHTML = "Giocatore 2 vince! 🚩";
} else {
    title.innerHTML = "Pareggio!";
}
