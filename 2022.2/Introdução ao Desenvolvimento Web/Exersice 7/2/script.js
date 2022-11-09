var brown = document.getElementsByClassName("brown")
var green = document.getElementsByClassName("green")
var blue = document.getElementsByClassName("blue")
var yellow = document.getElementsByClassName("yellow")
var random = document.getElementsByClassName("random")

brown[0].addEventListener("mouseover",change)
green[0].addEventListener("mouseover",change)
blue[0].addEventListener("mouseover",change)
yellow[0].addEventListener("mouseover",change)

random[0].style.background = "gray"
random[0].style.display = "inline-block"
random[0].style.width = "50px"
random[0].style.height = "50px"

function change(){
    var color = this.className

    document.getElementsByClassName("selected")[0].innerHTML = color
}

setInterval(() => {
    
}, 500);