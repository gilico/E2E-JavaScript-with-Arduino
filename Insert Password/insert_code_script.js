var sessionString = sessionStorage.getItem('randNumArray');
var randNum = JSON.parse(sessionString);

var txt = "";
for (var i = 0; i < randNum.length; i++) {
    txt += randNum[i];
    if (i < (randNum.length-1)) {
        txt += "  &nbsp, &nbsp "
    }
}
console.log(randNum);

document.getElementById("random").innerHTML = txt;;

var loadGif = document.getElementById("loading");
var gif = document.createElement('div');

function CreateLoadGif() {
    loadGif.innerHTML = '<div id="gif-div"></div>';

    gif.innerHTML = '<img src="https://media.giphy.com/media/3o7bu3XilJ5BOiSGic/giphy.gif" />';

    loadGif.appendChild(gif);

    setTimeout(getInputNum, 2500);
}



function getInputNum() {
    var inputArr = document.getElementsByName('inArr');
    console.log(inputArr);
    var a = 0;
    for (var i = 0; i < inputArr.length; i++) {
        a = inputArr[i];
        inputArr[i] = a.value;
    }

    var checkWrong = "הקוד שהכנסת לא נכון! נסו שוב";
    var isNumGood = true;

    for (var i = 0; i < inputArr.length; i++) {

        if (inputArr[i].valueAsNumber != randNum[i]) {
            isNumGood = false;
            break;
        }
    }

    var btnAns = document.getElementById("ans");
    var btncolor = document.getElementById("btn");
    loading.style.background = 'url()';

    if (isNumGood) {
        SuccessAlert();
    } else {
        btnAns.innerHTML = checkWrong;
        btnAns.style.border = '1px dotted red';
        btncolor.style.backgroundColor = 'red';
        document.getElementById('formCode').reset();
        document.getElementById('inp').focus();
    }
    gif.innerHTML = '<img src="" />';
    loadGif.appendChild(gif);
}

function SuccessAlert() {
    var winCode = document.getElementById('success');
    winCode.innerHTML = '<div id="success_pop"></div>';
    var popUp = document.getElementById("success_pop");
    winCode.style.boxShadow = '0 0 10px 3px blue';
    winCode.style.visibility = 'visible';
    var h3 = document.createElement("h3");
    h3.innerHTML = "הקוד נכון</br> !ניטרלתם את הפצצה";

    popUp.appendChild(h3);
    winCode.appendChild(popUp);
}

