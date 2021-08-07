const pointsContainer = document.getElementById("points");
const roundContainer = document.getElementById("roundCnt");
const strikesContainer = document.getElementById("strikes");
var strikes = 0;
var points = 25;
var roundNum = 0;
pointsContainer.innerText = points;
roundContainer.innerText = roundNum + 1;



addEventListener('keydown', (event) => {
    //if 't' is press from arduino - decrease the points
    if (event.keyCode == 84)
        ShowPoints();
    //if '2' is press from arduino - 1 round is finished
    if (event.keyCode == 50)
        FinishRound();
        //if 'm' is press from arduino - href to end mission page with the points
    if (event.keyCode == 77)
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
    points += 5;
    roundNum++;
    roundContainer.innerText = roundNum+1;
}

function closeTab() {
    if (points > 25)
        points = 25;

    localStorage.setItem('getPoint2', JSON.stringify(points));

    setTimeout(() => {
        window.close()
    }, 1000);
}