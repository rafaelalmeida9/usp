async function foo(){
    return 'hello'
}

foo().then(
    function(value) {console.log(value)}
)

console.log(foo())