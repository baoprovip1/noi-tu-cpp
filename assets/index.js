const pieces = document.getElementById("pieces");

let currentWord = "";
let history = [];
let score = 0;
let timer = null;
let timeBonus = 0;
let joinWord = null;

function startGame() {
  history = [];

  currentWord = words[Math.floor(Math.random() * words.length)].split(" ")[0];

  pieces.innerHTML = `
    <div class="piece">
      <input disabled value="${currentWord}">
      <p id="counter">0</p>
    </div>
  `;

  addPiece();
  startTimer();
}

function startTimer() {
  clearInterval(timer);
  timeBonus = 5000;

  timer = setInterval(function () {
    timeBonus -= 1;

    if (timeBonus <= 1000) clearInterval(timer);
  }, 1);
}

function addPiece() {
  const counter = history.length + 1;

  pieces.innerHTML += `
    <div class="piece">
      <input autocomplete="off" onkeyup="checkWord(event)">
      <p id="counter">${counter}</p>
    </div>
  `;

  joinWord = document.querySelector(".piece:last-child input");
  joinWord.focus();
}

function checkWord(event) {
  if (event.keyCode !== 13) {
    // TODO
    return;
  }

  event.preventDefault();

  const joinWordFormated = joinWord.value.toLowerCase().trim();
  const fullWord = currentWord + " " + joinWordFormated;

  if (! words.includes(fullWord)) { /* TODO */ return }
  if (history.includes(fullWord)) { /* TODO */ return }

  history.push(fullWord);
  currentWord = joinWordFormated;

  document.querySelector(".piece input"   ).setAttribute("style", "animation: disappear 250ms");
  document.querySelector(".piece #counter").outerHTML = null;
  setTimeout(function() {
    document.querySelector(".piece").outerHTML = null;
  }, 250);

  joinWord.setAttribute("value", joinWordFormated);
  joinWord.disabled = true;
  joinWord.setAttribute("style", "animation: none");
  addPiece();

  score += timeBonus;
  document.getElementById("score").innerHTML = score;
  startTimer();
}


startGame();
