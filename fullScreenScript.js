
document.addEventListener("keydown", FullScreen)

function FullScreen(k) {
    if (k.keyCode == 70) {
        document.documentElement.requestFullscreen().catch(console.log);
    }
}

document.addEventListener("fullscreenchange", () => {
    console.log("full screen changed!");
});



