var p = document.getElementsByTagName('p')
var text = p[0].innerHTML

var words = 1

for(var i=0;i<text.length;i++){
    if(text[i] == ' ') words++
}

var a = document.createElement('a')
a.innerHTML = 'Home'
a.href = './index.html'

var numberWords = document.createElement('p')
numberWords.innerHTML = words

var text2 = ""

var i = 0

while(i<text.length){
    if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')){
        var k = 0
        var word = ""

        while((text[i+k] >= 'a' && text[i+k] <= 'z') || (text[i+k] >= 'A' && text[i+k] <= 'Z')){
            word += text[i+k]
            k++;
        }
    
        i += k
    
        if(k == 4 || k == 5){
            text2 += "<span style=\"color:blue\">"
            text2 += word
            text2 += "</span>"
        }
        else if(k == 6){
            text2 += "<span style=\"color:purple\">"
            text2 += word
            text2 += "</span>"    
        }
        else if(k > 8){
            text2 += "<span style=\"color:pink\">"
            text2 += word
            text2 += "</span>"
        }
        else{
            text2 += word
        }
    }
    else{
        text2 += text[i]

        if(text[i] == '.' || text[i] == '?' || text[i] == '!'){
            text2 += "<br>"
        }

        i++
    }
}

body = document.querySelector('body')
body.appendChild(a)
body.insertBefore(numberWords,body.firstChild)
p[1].innerHTML = text2