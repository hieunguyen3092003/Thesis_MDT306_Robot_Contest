// Open link in new tab without triggering popup
document.getElementById("bkit").onclick = function (event) {
    event.preventDefault(); // Prevent default navigation behavior
    window.removeEventListener('beforeunload', beforeUnloadHandler); // Temporarily remove the beforeunload event
    window.open('https://example.com', '_blank'); // newtab
};

// Open link in new tab without triggering popup
document.getElementById("guide").onclick = function (event) {
    event.preventDefault(); // Prevent default navigation behavior
    window.removeEventListener('beforeunload', beforeUnloadHandler);
    window.open('https://example.com/guide', '_blank');
};

// Beforeunload handler function to re-add event after click
function beforeUnloadHandler(event) {
    event.preventDefault();
    event.returnValue = ''; // Request the browser to display popup
}