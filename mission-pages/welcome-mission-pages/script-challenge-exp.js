const titleElement = document.getElementById('title');
const explanation = document.getElementById("mission-detail");
var sessionStore = sessionStorage.getItem('missionIndex');
var missionIndex = JSON.parse(sessionStore);

var titles = ["הגעתם למשימת הדיוק", "הגעתם למשימת הזיכרון", "הגעתם למשימת הזריזות"];
//insert the title the current index title from the array that came from 'questionScript.js'
titleElement.innerText = titles[missionIndex];

var speed = 50;
var i = 0;
function typeWriter() {
    if (i < expText[missionIndex].length) {
        explanation.innerHTML += expText[missionIndex].charAt(i);
        i++;
        setTimeout(typeWriter, speed);
    } else
        direct();
}

function direct() {
    document.addEventListener('keydown', event => {
        if (event.keyCode === 32) {
            //open the 'active-mission' page at the current index
            window.location.href = "../active-missions-pages/active-challenge.html";
        }
    })
}





var expText = [
    "באתגר זה עליכם להיות מדוייקים ככל הניתן. משימתכם היא להעביר את החישוק לאורך חוט הנחושת. כדי להתחיל את האתגר עליכם לגעת עם החישוק בחלק השמאלי הכסוף - 'התחלה', כדי להשלימו עליכם להגיע עם הלולאה אל נקודת הסיום. בכל פעם שתגעו עם החישוק בחוט תצברו פסילה. בצעו את האתגר בדיוק מירבי עם כמה שפחות פסילות. בסיום האתגר, המשיכו בהוראות הניתנות לכם. להמשך ליחצו על הכפתור הלבן. ",

    "באתגר זה עליכם ללחוץ על הכפתור התואם לצבע שנדלק לפי הרצף. תחילה יוצג אור ראשון, וככל שתצליחו ללחוץ על הכפתור התואם האור הבא ברצף יידלק. כדי להצליח במשימה עליכם לזכור וללחוץ על רצף הכפתורים לפי האורות. הרצף מורכב מ 7 נורות. בסיום האתגר, המשיכו בהוראות הניתנות לכם. להמשך לחצו על הכפתור הלבן. בהצלחה!",

    "באתגר זה עליכם ללחוץ מהר ככל שניתן על הכפתור הדולק. ככל שתקפידו לבצע זאת בזמן תצברו נקודות. כדי להשלים את המשימה יהיה עליכם ללחוץ 15 לחיצות נכונות. בסיום האתגר, המשיכו בהוראות הניתנות לכם. להמשך לחצו על הכפתור הלבן. בהצלחה!"
]