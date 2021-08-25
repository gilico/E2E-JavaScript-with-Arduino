const pointsContainer = document.getElementById("points");
const roundContainer = document.getElementById("roundCnt");
const strikesContainer = document.getElementById("strikes");
const titleElement = document.getElementById('title');
const noteElement = document.getElementById('note');
var strikes = 0;
var points = 25;
var roundNum = 0;
pointsContainer.innerText = points;
roundContainer.innerText = roundNum + 1;

var sessionStore = sessionStorage.getItem('missionIndex');
var missionIndex = JSON.parse(sessionStore);

var titles = ["אתגר הדיוק", "אתגר הזיכרון", "אתגר המהירות"];
var notes = [
    "לתחילת האתגר געו עם החישוק במשטח ההתחלה",
    "לתחילת האתגר ליחצו על הכפתור הכחול",
    "לתחילת האתגר ליחצו על הכפתור הכחול"
]


titleElement.innerText = titles[missionIndex];
noteElement.innerText = notes[missionIndex];


addEventListener('keydown', (event) => {
    //if 't' is press from arduino - decrease the points
    if (event.keyCode === 84)
        ShowPoints();
    //if 'r' is press from arduino - 1 round is finished
    if (event.keyCode === 82)
        FinishRound();
    //if 'e' is press from arduino - href to end mission page with the points
    if (event.keyCode === 69)
        closeTab();

})


function ShowPoints() {
    pointsContainer.innerText = "";
    strikes++;
    points--;
    strikesContainer.innerText = strikes;
    pointsContainer.innerText = points;
}

function FinishRound() {
    //points += 5;
    roundNum++;
    //roundContainer.innerText = roundNum+1;
}

var storageNames = ['getPoint3', 'getPoint2', 'getPoint1'];

function closeTab() {
    if (points > 25)
        points = 25;

    localStorage.setItem(storageNames[missionIndex], JSON.stringify(points));

    setTimeout(() => {
        window.close()
    }, 0);
}
