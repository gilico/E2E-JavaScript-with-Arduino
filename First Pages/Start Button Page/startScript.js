var loadGif = document.getElementById("loading");
var gif = document.createElement('div');

function CreateLoadGif() {
    loadGif.innerHTML = '<div id="gif-div"></div>';

    gif.innerHTML = '<img src="https://media.giphy.com/media/3o7bu3XilJ5BOiSGic/giphy.gif" />';

    loadGif.appendChild(gif);

    setTimeout(() => {
        window.open('../../trivia/questionFormat.html');
        gif.innerHTML = '';
    }, 2500);
}

