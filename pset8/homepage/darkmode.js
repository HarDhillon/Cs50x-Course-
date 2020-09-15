let body = document.querySelector('body');
let navbar = document.querySelector('body');

document.querySelector('#dark').onclick = function()
{
    document.getElementById('navbar').className = "navbar navbar-expand-xl navbar-dark bg-dark sticky-top"
    body.style.backgroundColor = 'black';
    body.style.color = 'white';
}

document.querySelector('#light').onclick = function()
{
    document.getElementById('navbar').className = "navbar navbar-expand-xl navbar-light bg-light sticky-top"
    body.style.backgroundColor = 'white';
    body.style.color = 'black';
}