const startButton = document.getElementById("start");
const questionContainer = document.getElementById('que-cont');
const questionElement = document.getElementById('question');
const answerElement = document.getElementById('ans-cont');
var questionsPoints = 0;
let shuflleQustions;
let currQuestionIndex = 0;
var loadGif = document.getElementById("loading");
var gif = document.createElement('div');

var ChosenQuestionsArray = [];
function ChosenRandomQuestions(count) {
    //array of the questions arrays
    var questionsLevels = [easyQuestions, mediumQuestions, hardQuestions];
    //ammount questions to each level
    var questiontsCount = [2, 3, 5];

    for (var i = 0; i < questionsLevels.length; i++) {
        for (var k = 0; k < questiontsCount[i]; k++) {
            //get random index from the length if the current array
            var randomNumber = Math.floor(Math.random() * questionsLevels[i].length);
            //position the random question at new varieble
            var randQuestion = questionsLevels[i][randomNumber];
            //push the chosen question to new array
            ChosenQuestionsArray.push(randQuestion);
            //remove the chosen question for the question array
            questionsLevels[i].splice(randomNumber, 1);
        }
    }
    SetNextQuestion();
}

var tempPoints = 0;
function SetNextQuestion() {
    //send the question object at the current index
    ShowQuestion(ChosenQuestionsArray[currQuestionIndex]);
    tempPoints = 2.5;
}

var button;
function ShowQuestion(questionIndex) {
    var batNum = 1;
    //laod the question from the array's index
    questionElement.innerText = questionIndex.question;
    //create button to each answer
    questionIndex.answers.forEach((answer) => {
        button = document.createElement('button');
        answerElement.appendChild(button);
        button.innerText = answer.text;
        button.classList.add('btn');
        button.id = 'btn' + batNum; //give each button an id
        batNum++
        //set the correct button
        if (answer.correct)
            button.dataset.correct = answer.correct
        //create to each button a click event
        button.addEventListener('click', selectAnswer);
    });
}

//global: set keys to click the buttons
addEventListener('keydown', (event) => {
    //press 'a' and btn 1 will click
    if (event.keyCode == 65)
        document.getElementById("btn1").click();
    //press 'b' and btn 2 will click
    if (event.keyCode == 66)
        document.getElementById("btn2").click();
    //press 'c' and btn 3 will click
    if (event.keyCode == 67) 
        document.getElementById("btn3").click();
    //press 'd' and btn 4 will click
    if (event.keyCode == 68)
        document.getElementById("btn4").click();
})

function selectAnswer() { 
    const selectedButton = this;
    const correct = selectedButton.dataset.correct;
    //turn the button to yellow
    if (selectedButton) 
        selectedButton.classList.add('chosen-answer');
     //turn the button to either blue or red
    setTimeout(() => {
        if (correct) { //if the answer is corret: turn blue
            selectedButton.classList.add('correct-answer');
            setTimeout(CorrectAnswer, 1000) //send to function to add point
        } else {
            tempPoints -= 0.5;
            selectedButton.classList.add('wrong-answer');
        }
    }, 1000);
}


var tempPointsElement = document.getElementById('points-cnt');
var totalPointsElement = document.getElementById('total-points');
var prevPoints = 0;
var totalPoints = 0;
function CorrectAnswer() {
    //points erned last question
    tempPointsElement.innerText = tempPoints;
    //total points from questions
    questionsPoints += tempPoints;
    //total points from question and missions
    var sumMissions = 0;
    for (var i = 0; i < allMissionsPoints.length; i++) {
        sumMissions += allMissionsPoints[i];
    }
    totalPoints = questionsPoints + sumMissions;
    totalPointsElement.innerText = totalPoints;
    //only after the question is correct the question will replace//
    currQuestionIndex++;
    BeforeNextQuestion();
    //delete all the buttons and the question
    questionElement.innerText = "";
    while (answerElement.firstChild) {
        answerElement.removeChild(answerElement.firstChild)
    }
    //upload new question
    SetNextQuestion();
}

//create an array of random numbers 1-99
var randNum = [0, 0, 0, 0, 0];
for (var i = 0; i < randNum.length; i++) {
    randNum[i] = Math.floor(Math.random() * (100 - 1) + 1);
}

var index = 0;
var num;
var missionIndex = 0;
var isMissionComplete = false;
var numsContainer = document.getElementById('rand-num-cont');
function BeforeNextQuestion() {
    //every two questions a random num will show with popup
    if (currQuestionIndex % 2 == 0) {
        num = document.createElement('div');
        numsContainer.appendChild(num);
        ShowRandomNum(); //select the random number
        num.innerText = randNum[index];
        index++;
    }
    //every 3 question send to a new mission of *arduino*
    if (currQuestionIndex % 3 == 0) {
        isMissionComplete = false;
        SendToMission();
    }
    //only after the mission is complete the index increase
    if (isMissionComplete) {
        missionIndex++;
        isMissionComplete = false;
    }
    //check if the user finished 10 qeustions
    if (currQuestionIndex == 10) 
        EndOfTrivia();
}

var allMissionsPoints = [0, 0, 0];
//Every 3 correct answers this function will work
function SendToMission() {
    //popup form to insert the mission points
    const formElement = document.getElementById('form');
    formElement.style.visibility = 'visible';

    var keyPassWord = document.getElementById("card-password");
    var randPass = Math.floor(Math.random() * cardReleaseCode.length);
    keyPassWord.innerText = cardReleaseCode[randPass];

    const input = document.getElementById('mission-points');
    //the points will automatically type by the arduino
    //input.focus();


    addEventListener('keydown', (event) => {
        //  When arduino press 'n' : new mission tab wil appear
        if (event.keyCode == 78) {
            window.open(srcMissionPaged[missionIndex], '_blank');
        }
    });

    var storageNames = ['getPoint3', 'getPoint2', 'getPoint3'];

    //when Enter key will be pressed by the arduino
    addEventListener('keydown', event => {
        if (event.keyCode == 13) {
            //get the points from the current arduino mission
            var sessionSt = localStorage.getItem(storageNames[missionIndex]);
            var pointStr = JSON.parse(sessionSt);
            var currMissionPoints = parseInt(pointStr);
            //add the cuurent mission opints to an array
            allMissionsPoints[missionIndex] = currMissionPoints;
            console.log(pointStr);
            //allMissionsPoints[missionIndex] = parseInt(input.value);
            formElement.style.visibility = 'hidden';
        }
    });
    //only after there is points in the array - the mission will end
    if (allMissionsPoints[missionIndex] > 1) {
        isMissionComplete = true;
    }
}


var endContainer = document.getElementById('success');
function ShowRandomNum() {
    endContainer.innerHTML = '<div id="success_pop"></div>';
    var popUp = document.getElementById("success_pop");
    endContainer.style.visibility = 'visible';
    var h3 = document.createElement("h3");
    h3.innerHTML = `הסיפרה הבאה לניטרול היא: ${randNum[index]}`;

    popUp.appendChild(h3);
    endContainer.appendChild(popUp);

    setTimeout(() => {
        endContainer.removeChild(popUp)
        endContainer.style.visibility = 'hidden';
    }, 2500);
}


function EndOfTrivia() {
    endContainer.innerHTML = '<div id="success_pop"></div>';
    var popUp = document.getElementById("success_pop");
    endContainer.style.visibility = 'visible';
    endContainer.style.boxShadow = '0 0 10px 3px blue';
    endContainer.style.height = '35%';
    endContainer.style.backgroundColor = '#456fb3';
    var h3 = document.createElement("h3");
    h3.innerHTML = "הזינו את הספרות שקיבלתם בעמוד הבא";
    
    popUp.appendChild(h3);
    endContainer.appendChild(popUp);
    //after 3 sec the function will execute
    setTimeout(RedirectToNextPage, 3000)
}

function RedirectToNextPage() {
    //sending the 'randNum' array 
    sessionStorage.setItem('randNumArray', JSON.stringify(randNum));
    //sendig the points
    sessionStorage.setItem('total', JSON.stringify(totalPoints))
    //directing to the next page
    window.location.href = '../CODE_INSERT/insert_code_index.html';
}

//----TIMER FUNCTION-----//
setInterval(TimerFun, 1000);
var maxTime = 15;
var timeRemain = maxTime * 60;
var isTimeGood = true;

function TimerFun() {
    var countDown = document.getElementById('timer');
    var minutes = Math.floor(timeRemain / 60);
    var seconds = timeRemain % 60;

    if (seconds < 10) {
        seconds = '0' + seconds;
    }

    if (minutes < 10) {
        countDown.innerHTML = '0' + minutes + ' : ' + seconds;
    } else {
        countDown.innerHTML = minutes + ' : ' + seconds;
    }
    timeRemain--;

    if (timeRemain <= -2) {
        isTimeGood = false;
        countDown.innerHTML = '';
        countDown.style.visibility = "hidden";

        questionElement.innerText = "";
        while (answerElement.firstChild) {
            answerElement.removeChild(answerElement.firstChild)
        }
        timeIsOverPopUp();   
    }
} 

function timeIsOverPopUp() {
    const looserCont = document.getElementById("loose")
    looserCont.innerHTML = '<div id="looser-pop"></div>';
    var popUp = document.getElementById("looser-pop");
    looserCont.style.visibility = 'visible';
    var h3 = document.createElement("h3");
   
    h3.innerText = "הזמן עבר! \nהפצצה התפוצצה ולא הצלחתם להציל את העולם"
    popUp.appendChild(h3);
    looserCont.appendChild(popUp);    

}



var srcMissionPaged = ["../missions-pages/welcome-pages/loop-welcome-page.html", "../missions-pages/welcome-pages/memory-welcome-page.html", "../missions-pages/welcome-pages/speed-welcome-page.html"];

var cardReleaseCode = ['24425','13431','68486'];


const easyQuestions = [
    {
        question: 'מהי עיר הבירה של פולין ?',
        answers: [
            { text: 'ורשה', correct: true},
            { text: 'קרקוב', correct: false},
            { text: 'בודפשט', correct: false},
            { text: 'אמסטרדם', correct: false},
        ]
    },
    {
        question: 'מהי המדינה בעלת השטח הגדול ביותר בעולם ?',
        answers: [
            { text: 'ארצות הברית', correct: false },
            { text: 'סין', correct: false },
            { text: 'רוסיה', correct: true },
            { text: 'ברזיל', correct: false },
        ]
    },
    {
        question: 'אילו מדינות גובלות עם ישראל ?',
        answers: [
            { text: 'מצרים, ירדן, לבנון, סוריה', correct: true },
            { text: 'סוריה, מצרים, טורקיה, עיראק', correct: false },
            { text: 'לבנון, ירדון, ערב הסעודית, מצרים', correct: false },
            { text: 'מצרים, ירדן, לבנון', correct: false },
        ]
    },
    {
        question: 'איזו שפה מדברים בארגנטינה?',
        answers: [
            { text: 'ספרדית', correct: true },
            { text: 'ארגנטינאית', correct: false },
            { text: 'אנגלית', correct: false },
            { text: 'איטלקית', correct: false },
        ]
    },
    {
        question: 'מהי עיר הבירה של אגנטינה?',
        answers: [
            { text: 'בואנוס איירס', correct: true },
            {text: "צ'ילה", correct: false },
            { text: 'לאס סיריס', correct: false },
            { text: 'ארגנטינה סיטי', correct: false },
        ]
    },
    {
        question: 'באיזו מדינה נמצא הנהר הארוך ביותר?',
        answers: [
            { text: 'נהר הירדן - ישראל', correct: false },
            { text: 'הנהר הצהוב - סין', correct: false },
            { text: 'נהר מיסיסיפי-מיזורי - ארצות הברית', correct: false },
            { text: 'נהר האמזונס - ברזיל', correct: true },
        ]
    },
    {
        question: 'איזו מדינה היא גם יבשת?',
        answers: [
            { text: 'אוסטרליה', correct: true },
            { text: 'אוסטריה', correct: false },
            { text: 'ארצות הברית של אמריקה', correct: false },
            { text: 'דרום אפריקה', correct: false },
        ]
    },
    {
        question: 'מהי עיר הבירה של אתיופיה?',
        answers: [
            { text: 'קהיר', correct: false },
            { text: 'גונדר', correct: false },
            { text: 'אדיס-אבבה', correct: true },
            { text: 'ניירובי', correct: false },
        ]
    },
    {
        question: 'איזה מדינה מזכירה בשטחה מגף?',
        answers: [
            { text: 'איטליה', correct: true },
            { text: 'יוון', correct: false },
            { text: 'ספרד', correct: false },
            { text: 'צרפת', correct: false },
        ]
    },
    {
        question: 'באילו מהבאות לא מדברים אנגלית?',
        answers: [
            { text: 'ניו-יורק', correct: false },
            { text: 'אמסטרדם', correct: true },
            { text: 'ניו-זילנד', correct: false },
            { text: "צ'לסי", correct: false },
        ]
    },
    {
        question: 'איזו מדינה אינה נמצאת באירופה?',
        answers: [
            { text: 'אלבניה', correct: false },
            { text: 'ישראל', correct: true },
            { text: 'ליטא', correct: false },
            { text: 'אוקראינה', correct: false },
        ]
    },
    {
        question: 'באיזו יבשת אין כלל מדינות?',
        answers: [
            { text: 'אפריקה', correct: false },
            { text: 'אמריקה', correct: false },
            { text: 'אוסטרליה', correct: false },
            { text: 'אנטרנטיקה', correct: true },
        ]
    },
    {
        question: 'איזו יבשת היא המאוכלסת ביותר מבין הבאות?',
        answers: [
            { text: 'אמריקה', correct: false },
            { text: 'אפריקה', correct: false },
            { text: 'אירופה', correct: false },
            { text: 'אסיה', correct: true },
        ]
    },
]

const mediumQuestions = [
    {
        question: 'מהי עיר הבירה של פורטוגל?',
        answers: [
            { text: 'ליסבון', correct: true },
            { text: 'פורטו', correct: false },
            { text: 'רומא', correct: false },
            { text: 'מדריד', correct: false },
        ]
    },
    {
        question: 'מהי עיר הבירה של מרוקו?',
        answers: [
            { text: 'מרקש', correct: false },
            { text: 'קזבלנקה', correct: false },
            { text: 'פז', correct: false },
            { text: 'רבאט', correct: true },
        ]
    },
    {
        question: 'מהי המדינה השנייה בגדולה באוכלוסייה?',
        answers: [
            { text: 'הודו', correct: true },
            { text: 'סין', correct: false },
            { text: 'אינדונזיה', correct: false },
            { text: 'ארצות הברית', correct: false },
        ]
    },
    {
        question: 'מהי הדת המרכזית בהודו?',
        answers: [
            { text: 'בודהיזם', correct: false },
            { text: 'איסלאם', correct: false },
            { text: 'הינדואיזם', correct: true },
            { text: 'נצרות', correct: false },
        ]
    },
    {
        question: 'הביניין הגדול בעולם נמצא ב - ',
        answers: [
            { text: 'שנגחאי - מגדל שנגחאי', correct: false },
            { text: "דובאי - בורג' ח'ליפה", correct: true },
            { text: 'ארה"ב - אמפייר סטייט בילדינג', correct: false },
            { text: 'ארה"ב - מגדל וויליס', correct: false },
        ]
    },
    {
        question: 'באיזה עוד שם נקראת השפה הסינית?',
        answers: [
            { text: 'מנדרינית', correct: true },
            { text: 'תפוסינית', correct: false },
            { text: 'קלמנסינית', correct: false },
            { text: 'אפרסקית', correct: false },
        ]
    },
    {
        question: 'איפה חובשים סומבררו?',
        answers: [
            { text: 'גואטמלה', correct: false },
            { text: 'מקסיקו', correct: true },
            { text: 'תאילנד', correct: false },
            { text: 'ברזיל', correct: false },
        ]
    },
    {
        question: 'איזו מדינה נמצאת על שתי יבשות?',
        answers: [
            { text: 'ישראל', correct: false },
            { text: 'תורכיה', correct: true },
            { text: 'רוסיה', correct: false },
            { text: 'סוריה', correct: false },
        ]
    },
    {
        question: 'לאיזו מדינה מבין הבאות יש את השטח הכי קטן',
        answers: [
            { text: 'יוון', correct: false },
            { text: 'ישראל', correct: false },
            { text: 'לבנון', correct: true },
            { text: 'הולנד', correct: false },
        ]
    },
    {
        question: 'מהי עיר הבירה של יפן?',
        answers: [
            { text: 'טוקיו', correct: true },
            { text: "בייג'ינג", correct: false },
            { text: 'שנגחאי', correct: false },
            { text: 'בנגקוק', correct: false },
        ]
    },
    {
        question: 'מקור השניצל הוא מהמדינה?',
        answers: [
            { text: 'ישראל', correct: false },
            { text: 'אוסטריה', correct: true },
            { text: 'צרפת', correct: false },
            { text: 'גרמניה', correct: false },
        ]
    },
    {
        question: 'איזו יבשת היא השנייה בגודלה בעולם?',
        answers: [
            { text: 'אסיה', correct: false },
            { text: 'אמריקה', correct: false },
            { text: 'אוסטרליה', correct: false },
            { text: 'אפריקה', correct: true },
        ]
    },
    {
        question: 'באיזו מדינה יש הכי פחות הרים?',
        answers: [
            { text: 'הולנד', correct: true },
            { text: 'רוסיה', correct: false },
            { text: 'איטליה', correct: false },
            { text: 'מרוקו', correct: false },
        ]
    },
    {
        question: 'איפה נמצאת טנזניה ומה מייחד אותה?',
        answers: [
            { text: 'אסיה - הייטק', correct: false },
            { text: 'דרום אמריקה - סיגרים', correct: false },
            { text: 'אפריקה - ספארי', correct: true },
            { text: 'אפריקה - מדברים', correct: false },
        ]
    },
    {
        question: 'איזו מדינה מכרה לארה"ב את אלסקה?',
        answers: [
            { text: 'בריטניה', correct: false },
            { text: 'רוסיה', correct: true },
            { text: 'יפן', correct: false },
            { text: 'קנדה', correct: false },
        ]
    },
    {
        question: 'באיזו מדינה יש הכי הרבה אגמים?',
        answers: [
            { text: 'צרפת', correct: false },
            { text: 'קנדה', correct: true },
            { text: 'ברזיל', correct: false },
            { text: 'הודו', correct: false },
        ]
    },
    {
        question: 'איזו מדינה מייצרת הכי הרבה קפה?',
        answers: [
            { text: 'איטליה', correct: false },
            { text: 'קובה', correct: false },
            { text: 'כויית', correct: false },
            { text: 'ברזיל', correct: true },
        ]
    },
    {
        question: 'איזו מדינה בעלת השטח הקטן ביותר בעולם?',
        answers: [
            { text: 'קריית הותיקן', correct: true },
            { text: 'סינגפור', correct: false },
            { text: 'ישראל', correct: false },
            { text: 'לבנון', correct: false },
        ]
    },
    {
        question: 'איפה נמצאת לפלנד?',
        answers: [
            { text: 'תאילנד', correct: false },
            { text: 'יוון', correct: false },
            { text: 'צפון אירופה', correct: true },
            { text: 'אפריקה', correct: false },
        ]
    }
]

const hardQuestions = [
    {
        question: 'פורטו ריקו היא...?',
        answers: [
            { text: 'מדינה עצמאית', correct: false },
            { text: 'טריטוריה של ארה"ב שאינה מדינה', correct: true },
            { text: 'אחת מ- 50 המדינות של ארה"ב', correct: false },
            { text: 'עיר במקסיקו', correct: false },
        ]
    },
    {
        question: 'מה היא קונגו?',
        answers: [
            { text: 'מדינה באפריקה', correct: false },
            { text: 'מקום בו מייצרים את פטיש הקונגו', correct: false },
            { text: 'שתי מדינות באפריקה', correct: true },
            { text: 'מדינה בדרום אמריקה', correct: false },
        ]
    },
    {
        question: 'צפון אירלנד שייכת ל..?',
        answers: [
            { text: 'זו מדינה עצמאית', correct: false },
            { text: 'דרום אירלנד', correct: false },
            { text: 'אירלנד', correct: false },
            { text: 'בריטניה', correct: true },
        ]
    },
    {
        question: 'מהי המדינה הצפופה בעולם?',
        answers: [
            { text: 'ישראל', correct: false },
            { text: 'מונקו', correct: true },
            { text: 'עזה', correct: false },
            { text: 'סין', correct: false },
        ]
    },
    {
        question: 'מהי עיר הבירה של אריתריה?',
        answers: [
            { text: 'אסמרה', correct: true },
            { text: 'אסאב', correct: false },
            { text: 'דקר', correct: false },
            { text: 'קהיר', correct: false },
        ]
    },
    {
        question: 'המדינה הגדולה בשטחה בארצות הברית היא?',
        answers: [
            { text: 'אלסקה', correct: true },
            { text: 'ניו מקסיקו', correct: false },
            { text: 'טקסס', correct: false },
            { text: 'קליפורניה', correct: false },
        ]
    },
    {
        question: 'המדינה הגדולה באוכלוסייה בארה"ב היא?',
        answers: [
            { text: 'ניו מקסיקו', correct: false },
            { text: 'טקסס', correct: false },
            { text: 'אלסקה', correct: false },
            { text: 'קליפורניה', correct: true },
        ]
    },
    {
        question: 'איזו שפה מדברים בקוריאה הצפונית?',
        answers: [
            { text: 'מנדרינית', correct: false },
            { text: 'יפנית', correct: false },
            { text: 'קוריאנית', correct: true },
            { text: 'קוריאנית צפונית', correct: false },
        ]
    },
    {
        question: 'איזו מדינה מכונה "ארץ הקרח והאש"?',
        answers: [
            { text: 'איסלנד', correct: true },
            { text: 'בריטניה', correct: false },
            { text: 'יפן', correct: false },
            { text: 'קנדה', correct: false },
        ]
    },
    {
        question: 'באיזו יבשת שוכנת המדינה אסטוניה?',
        answers: [
            { text: 'אסיה', correct: false },
            { text: 'אפריקה', correct: false },
            { text: 'אמריקה', correct: false },
            { text: 'אירופה', correct: true },
        ]
    },
    {
        question: 'איזו מדינה מכונה "מדינת השמש העולה"?',
        answers: [
            { text: 'ארגנטינה', correct: false },
            { text: 'אורוגווי', correct: false },
            { text: 'יפן', correct: true },
            { text: 'סין', correct: false },
        ]
    },
    {
        question: 'באיזו יבשת נמצאת איסטנבול?',
        answers: [
            { text: 'אסיה ואירופה', correct: true },
            { text: 'אסיה', correct: false },
            { text: 'אירופה', correct: false },
            { text: 'אפריקה', correct: false },
        ]
    },
    {
        question: 'כמה מדינות יש בעולם?',
        answers: [
            { text: '105', correct: false },
            { text: '192', correct: true },
            { text: '352', correct: false },
            { text: '420', correct: false },
        ]
    },
    {
        question: 'לאיזו מדינה הכינוי "מדינת החופשיים"?',
        answers: [
            { text: 'ארצות הברית', correct: false },
            { text: 'ישראל', correct: false },
            { text: 'צרפת', correct: false },
            { text: 'תאילנד', correct: true },
        ]
    }
]